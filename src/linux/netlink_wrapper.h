
#ifndef SRC_LINUX_NELTINK_WRAPPER_H_
#define SRC_LINUX_NELTINK_WRAPPER_H_

#include <net/if.h>

#include <netlink/netlink.h>
#include <netlink/route/link.h>
#include <netlink/route/link/can.h>

#include <string>
#include <memory>

namespace Netlink
{

class NetlinkWrapper
{
public:
	NetlinkWrapper();
	~NetlinkWrapper();
	
	int open();
	void close();
	bool isOpen();
	
	bool device_exists(const std::string& device);
	
	struct rtnl_link* link_get(const std::string& device);
	void link_put(struct rtnl_link* link);
	
private:
	struct nl_sock *socket = nullptr;
};
typedef std::shared_ptr<NetlinkWrapper> NetlinkWrapperPtr;

} /* namespace Netlink */

#endif /* SRC_LINUX_NELTINK_WRAPPER_H_ */
