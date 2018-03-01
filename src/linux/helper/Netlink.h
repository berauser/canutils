#ifndef NETLINK_NETLINK_H_
#define NETLINK_NETLINK_H_

#include <linux/rtnetlink.h>

#include <string>
#include <memory>
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
		std::string	name;
		struct rtattr*  tb[IFLA_MAX+1];
		struct rtattr*  kind[IFLA_INFO_MAX+1];
		Data();
		~Data();
	};
	typedef std::shared_ptr<Data> DataPtr;
	
public:
	Netlink();
	~Netlink();
	
	int open();
	int close();
	
	DataPtr getDeviceInformation(const std::string& name);
	
	static void destroy(Data* data);
	
	static std::string typeToString( unsigned int type );
	
private:
	int request(int family, int type);
	DataPtr dump_filter(int idx);
	static int deep_copy(DataPtr data, struct rtattr *rta, int len);
	static int parse_rtattr(struct rtattr *tb[], int max, struct rtattr *rta, int len);
	static int free_rtattr(struct rtattr *tb[], int max);
	
private:
	int fd;
	std::uint32_t seq;
	std::uint32_t dump;
};

} /* namespace Netlink */

#endif /* NETLINK_NETLINK_H_ */
