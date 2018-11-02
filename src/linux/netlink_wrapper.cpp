
#include "netlink_wrapper.h"

namespace Netlink
{

NetlinkWrapper::NetlinkWrapper()
{
}

NetlinkWrapper::~NetlinkWrapper()
{
	close();
}

int NetlinkWrapper::open()
{
	socket = nl_socket_alloc();
	if (socket == nullptr)
	{
		perror("nl_socket_alloc");
		return 1;
	}
	
	int err = nl_connect(socket, NETLINK_ROUTE);
	if (err < 0)
	{
		nl_perror(err, "nl_connect");
		close();
		return err;
	}
	
	return 0;
}

void NetlinkWrapper::close()
{
	if( socket != nullptr )
	{
		nl_close(socket);
		nl_socket_free(socket);
		socket = nullptr;
	}
}

bool NetlinkWrapper::isOpen()
{
	return (socket != nullptr);
}

bool NetlinkWrapper::device_exists(const std::string& device)
{
	struct rtnl_link* link = link_get(device);
	if( link != nullptr )
	{
		link_put(link);
		return true;
	}
	return false;
}

struct rtnl_link * NetlinkWrapper::link_get(const std::string& device)
{
	struct rtnl_link *link;
	if (rtnl_link_get_kernel(socket, 0, device.c_str(), &link) < 0)
	{
		return nullptr;
	}
	return link;
}

void NetlinkWrapper::link_put(struct rtnl_link* link)
{
	rtnl_link_put(link);
}

} /* namespace Netlink */
