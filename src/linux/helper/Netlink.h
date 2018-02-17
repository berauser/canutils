#ifndef NETLINK_NETLINK_H
#define NETLINK_NETLINK_H

#include <linux/rtnetlink.h>
#include <net/if.h>

#include <string>
#include <cstdint>

namespace Netlink 
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
	
	static void destroy(Data* data);
	
private:
	int request(int family, int type);
	Data* dump_filter(int idx);
	static int parse_rtattr(struct rtattr *tb[], int max, struct rtattr *rta, int len);

private:
	int fd;
	std::uint32_t seq;
	std::uint32_t dump;
	struct sockaddr_nl local;
};

} /* namespace Netlink */

#endif // NETLINK_NETLINK_H
