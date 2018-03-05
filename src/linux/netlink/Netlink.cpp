
#include "Netlink.h"
#include "NetlinkHelper.h"

#include <cstring>
#include <cstdint>
#include <cstdio>
#include <ctime>
 
#include <unistd.h>
#include <sys/socket.h>

#include <linux/if.h>
#include <linux/if_arp.h>

namespace Netlink
{

Netlink::Data::Data()
{
	this->index = 0;
	this->type  = 0;
	this->flags = 0;
	this->name  = "";
	memset(this->tb, 0, sizeof(this->tb));
}

Netlink::Data::~Data()
{
	// clear rtattr tb
	for( int i = 0; i < (IFLA_MAX+1); ++i )
	{
		if( this->tb[i] ) 
		{
			free(this->tb[i]);
			this->tb[i] = nullptr;
		}
	}
	
	// clear all attributes
	this->index = 0;
	this->type  = 0;
	this->flags = 0;
	this->name  = "";
	memset(this->tb, 0, sizeof(this->tb));
}

Netlink::Netlink() : fd(-1)
{
  seq = ::time(NULL);
}

Netlink::~Netlink() noexcept(false)
{
}

int Netlink::open()
{
	socklen_t addr_len;
	struct sockaddr_nl local;
	int rcvbuf = 1024 * 1024;
	int sndbuf = 32768;

	fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	if (fd < 0) {
		perror("Cannot open netlink socket");
		return -1;
	}

	if (setsockopt(fd,SOL_SOCKET,SO_SNDBUF,&sndbuf,sizeof(sndbuf)) < 0) {
		perror("SO_SNDBUF");
		return -1;
	}

	if (setsockopt(fd,SOL_SOCKET,SO_RCVBUF,&rcvbuf,sizeof(rcvbuf)) < 0) {
		perror("SO_RCVBUF");
		return -1;
	}

	memset(&local, 0, sizeof(local));
	local.nl_family = AF_NETLINK;
	local.nl_groups = 0;

	if (bind(fd, (struct sockaddr*)&local, sizeof(local)) < 0) {
		perror("Cannot bind netlink socket");
		return -1;
	}
	addr_len = sizeof(local);
	if (getsockname(fd, (struct sockaddr*)&local, &addr_len) < 0) {
		perror("Cannot getsockname");
		return -1;
	}
	if (addr_len != sizeof(local)) {
		fprintf(stderr, "Wrong address length %d\n", addr_len);
		return -1;
	}
	if (local.nl_family != AF_NETLINK) {
		fprintf(stderr, "Wrong address family %d\n", local.nl_family);
		return -1;
	}
	
	return 0;
}

int Netlink::close()
{
	if (fd >= 0) {
		::close(fd);
		fd = -1;
	}
	return 0;
}

void Netlink::destroy(Netlink::Data* data)
{
	if( data == nullptr ) return;
	
	Helper::free_rtattr( data->tb, IFLA_MAX );
	
	// delete object
	delete data;
	
	data = nullptr;
}

std::string Netlink::typeToString(unsigned int type)
{
	switch( type )
	{
	case ARPHRD_ETHER:    return "ether";
	case ARPHRD_EETHER:   return "eether";
	case ARPHRD_CAN:      return "can";
	case ARPHRD_LOOPBACK: return "loopback";
	default:              return "UNKNOWN";
	}
}

int Netlink::request(int family, int type)
{
	struct {
		struct nlmsghdr nlh;
		struct rtgenmsg g;
	} req;
	
	memset(&req, 0, sizeof(req));
	req.nlh.nlmsg_len = sizeof(req);
	req.nlh.nlmsg_type = type;
	req.nlh.nlmsg_flags = NLM_F_ROOT|NLM_F_MATCH|NLM_F_REQUEST;
	req.nlh.nlmsg_pid = 0;
	req.nlh.nlmsg_seq = dump = ++seq;
	req.g.rtgen_family = family;
	
	return send(fd, (void*)&req, sizeof(req), 0);
}

Netlink::DataPtr Netlink::dump_filter(int idx)
{
	struct sockaddr_nl nladdr;
	struct iovec iov;
	struct msghdr msg = {
		.msg_name = &nladdr,
		.msg_namelen = sizeof(nladdr),
		.msg_iov = &iov,
		.msg_iovlen = 1,
		.msg_control = NULL,
		.msg_controllen = 0,
		.msg_flags = 0,
	};
	
	char buf[16384];
	
	iov.iov_base = buf;
	struct ifinfomsg *ifi =  nullptr;
	while (1) {
		int status;
		int done = 0;
		int msglen = 0;
		
		
		iov.iov_len = sizeof(buf);
		status = recvmsg(fd, &msg, 0);
	
		if (status < 0) {
			if (errno == EINTR || errno == EAGAIN)
				continue;
			fprintf(stderr, "netlink receive error %s (%d)\n",
				strerror(errno), errno);
			return nullptr;
		}
	
		if (status == 0) {
			fprintf(stderr, "EOF on netlink\n");
			return nullptr;
		}
		
		struct nlmsghdr *h = (struct nlmsghdr*)buf;
		msglen = status;
		
		while (NLMSG_OK(h, msglen)) {
			if( nladdr.nl_pid == 0 && 
			  h->nlmsg_pid == static_cast<uint32_t>(getpid()) &&
			  h->nlmsg_seq == dump )
			{
				if (h->nlmsg_type == NLMSG_DONE) {
					done = 1;
					break; /* process next filter */
				}
				if (h->nlmsg_type == NLMSG_ERROR) {
					struct nlmsgerr *err = (struct nlmsgerr*)NLMSG_DATA(h);
					if (h->nlmsg_len < NLMSG_LENGTH(sizeof(struct nlmsgerr))) {
						fprintf(stderr,
							"ERROR truncated\n");
					} else {
						errno = -err->error;
						perror("RTNETLINK answers");
					}
					return nullptr;
				}
				ifi = static_cast<ifinfomsg*>(NLMSG_DATA(h));
				if ( ifi->ifi_index == idx )
				{
					DataPtr t(new struct Data);
					
					t->index = ifi->ifi_index;
					t->type  = ifi->ifi_type;
					t->flags = ifi->ifi_flags;
					
					Helper::parse_rtattr(t->tb, IFLA_MAX, IFLA_RTA(ifi), IFLA_PAYLOAD(h));
					
					if ( t->tb[IFLA_IFNAME] )
						t->name = (char*)RTA_DATA(t->tb[IFLA_IFNAME]);
					
					return t;
				}
			}
			h = NLMSG_NEXT(h, msglen);
		}
	
		if( done )
			return nullptr;
		
		if (msg.msg_flags & MSG_TRUNC) {
			fprintf(stderr, "Message truncated\n");
			continue;
		}
		if (msglen) {
			fprintf(stderr, "!!!Remnant of size %d\n", msglen);
			exit(1);
		}
		
	}
}

Netlink::DataPtr Netlink::getDeviceInformation(const std::string&  name)
{
	if(request(AF_PACKET, RTM_GETLINK) < 0)
	{
		perror("netlink.wilddump_request()");
		return nullptr;
	}
	
	int ifindex = Helper::index_from_name(name);
	if( ifindex <= 0 )
	{
		fprintf( stdout, "Device does not exists\n");
		return nullptr;
	}	
	return dump_filter(ifindex);
}

} /* namespace Netlink */
