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
		Data();
		~Data();
	};
	typedef std::shared_ptr<Data> DataPtr;
	
public:
	Netlink();
	~Netlink() noexcept(false);
	
	int open();
	int close();
	
	DataPtr getDeviceInformation(const std::string& name);
	
	static void destroy(Data* data);
	
	static std::string typeToString( unsigned int type );
	
private:
	int request(int family, int type);
	DataPtr dump_filter(int idx);
	
private:
	int fd;
	std::uint32_t seq;
	std::uint32_t dump;
};
typedef std::shared_ptr<Netlink> NetlinkPtr;

} /* namespace Netlink */

#endif /* NETLINK_NETLINK_H_ */
