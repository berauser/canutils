
#include "NetlinkHelper.h"

#include <cstring>
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

int parse_rtattr(struct rtattr *tb[], int max, struct rtattr *rta, int len)
{
	memset(tb, 0, sizeof(struct rtattr *) * (max + 1));
	while (RTA_OK(rta, len)) {
		if ((rta->rta_type <= max) && (!tb[rta->rta_type]))
		{
			// deep copy of rta
			tb[rta->rta_type] = (rtattr*)malloc(rta->rta_len);
			memcpy(tb[rta->rta_type], rta, rta->rta_len);
		}
		rta = RTA_NEXT(rta,len);
	}
	if (len)
		return -1;
	return 0;
}

int parse_rtattr_nested(struct rtattr *tb[], int max, struct rtattr* rta)
{
	return parse_rtattr(tb, max, (struct rtattr*)RTA_DATA(rta), RTA_PAYLOAD(rta));
}

int free_rtattr(rtattr* tb[], int max)
{
	for( int i = 0; i <= max; ++i )
	{
		if( tb[i] )
		{
			free(tb[i]);
			tb[i] = nullptr;
		}
	}
	return 0;
}

} /* namespace Helper */
} /* namespace Netlink */
