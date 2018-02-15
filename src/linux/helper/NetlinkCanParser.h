#ifndef CANSOCKET_NETLINKCANPARSER_H
#define CANSOCKET_NETLINKCANPARSER_H

#include "Netlink.h"
#include "NetlinkParser.h"



namespace CanSocket 
{

class NetlinkCanParser : public NetlinkParser
{

  
public:
	NetlinkCanParser();
	~NetlinkCanParser();
	
protected:
	
};

} /* namespace CanSocket */

#endif // CANSOCKET_NETLINKCANPARSER_H
