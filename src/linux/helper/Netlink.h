#ifndef CANSOCKET_NETLINK_H
#define CANSOCKET_NETLINK_H

#include <linux/rtnetlink.h>
#include <net/if.h>

#include <string>
#include <cstdint>

namespace CanSocket 
{

class Netlink
{
public:
	struct Data {
		int		index;
		unsigned int	flags;
		unsigned short	type;
		char		name[IFNAMSIZ];
		struct rtattr*  tb[IFLA_MAX+1];
	};
  
public:
	Netlink();
	~Netlink();
	
	int open();
	int close();
	
	static int index_from_name(const std::string& name);
	Data* getDeviceInformation(const std::string& name);

private:
	int request(int family, int type);
	Data* dump_filter(int idx);
	static int parse_rtattr(struct rtattr *tb[], int max, struct rtattr *rta, int len);

private:
	int fd;
	uint32_t seq;
	uint32_t dump;
	struct sockaddr_nl local;
};

} /* namespace CanSocket */

#endif // CANSOCKET_NETLINK_H
