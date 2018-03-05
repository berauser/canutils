#ifndef NETLINK_NETLINKHELPER_H_
#define NETLINK_NETLINKHELPER_H_

#include <string>
#include <linux/rtnetlink.h>

namespace Netlink
{
namespace Helper
{

int index_from_name(const std::string& name);
int parse_rtattr(struct rtattr *tb[], int max, struct rtattr *rta, int len);
int parse_rtattr_nested( struct rtattr *tb[], int max, struct rtattr *rta);
int free_rtattr(struct rtattr *tb[], int max);

} /* namespace Helper */
} /* namespace Netlink */

#endif /* NETLINK_NETLINKHELPER_H_ */
