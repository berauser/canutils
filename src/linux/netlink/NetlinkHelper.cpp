
#include "NetlinkHelper.h"

#include <cstdio>
#include <net/if.h>

namespace Netlink
{
namespace Helper
{

int index_from_name(const std::string&  name)
{
	int idx;
	if (name.size() == 0)
		return -1;
	idx = if_nametoindex(name.c_str());
	if (idx == 0)
		sscanf(name.c_str(), "if%u", &idx);
	return idx;
}

} /* namespace Helper */
} /* namespace Netlink */