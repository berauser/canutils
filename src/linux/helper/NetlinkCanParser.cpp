#include "NetlinkCanParser.h"

#include <cstdio>
#include <cstring>

namespace CanSocket
{
  
NetlinkCanParser::NetlinkCanParser()
{

}

NetlinkCanParser::~NetlinkCanParser()
{

}

// NetlinkCanParser::DeviceDetails* NetlinkCanParser::parseDetails(Netlink::Data* data)
// {
// 	if( !(data->flags&IFF_UP) )
// 	{
// 		fprintf( stdout, "interface is not up\n");
// 		return 0;
// 	}
// 	
// 	// check if type is can
// 	
// 	DeviceDetails* details = new DeviceDetails;
// 	memset( details, 0, sizeof(DeviceDetails) );
// 	
// 	details->ifindex = data->index;
// 	details->ifname  = data->name;
// 	details->iftype  = data->type;
// 	
// 	if ( data->tb[IFLA_QDISC]     ) 
// 		details->qdisc = (char*)RTA_DATA(data->tb[IFLA_QDISC]      );
// 	if ( data->tb[IFLA_OPERSTATE] ) 
// 		details->state = operationState ( *(uint8_t*)(data->tb[IFLA_OPERSTATE]) );
// 	
// 	
// 	
// 	return nullptr;
// }
//   
// NetlinkCanParser::DeviceStatistics* NetlinkCanParser::parseStatistics(Netlink::Data* data)
// {
// 	if( !(data->flags&IFF_UP) )
// 	{
// 		fprintf( stdout, "interface is not up\n");
// 		return 0;
// 	}
// 	
// 	// check if type is can
// 	
// 	DeviceStatistics *stats = new DeviceStatistics;
// 	memset( stats, 0, sizeof(DeviceStatistics) );
// 	
// 	struct rtnl_link_stats64 *s;
// 	if ( data->tb[IFLA_STATS64] )
// 	{
// 		// 64bit statistics
// 	  
// 	} else if ( data->tb[IFLA_STATS] )
// 	{
// 		// 32bit statistics
// 	} else
// 	{
// 		// no statistics return;
// 		return stats;
// 	}
// 	  
// 	  
// 	struct rtnl_link_stats64 slocal;
// 	s = static_cast<struct rtnl_link_stats64*>(RTA_DATA( data->tb[IFLA_STATS64]));
// 	
// 	// Receive stats
// 	stats->rx_bytes   = s->rx_bytes;
// 	stats->rx_packets = s->rx_packets;
// 	stats->rx_errors  = s->rx_errors;
// 	stats->rx_dropped = s->rx_dropped;
// 	stats->rx_overrun_errors = s->rx_over_errors;
// 	stats->rx_multicast      = s->multicast;
// 	stats->rx_compressed     = s->rx_compressed;
// 	stats->rx_length_errors  = s->rx_length_errors;
// 	stats->rx_crc_errors     = s->rx_crc_errors;
// 	stats->rx_frame_errors   = s->rx_frame_errors;
// 	stats->rx_fifo_errors    = s->rx_fifo_errors;
// 	stats->rx_misssed_errors = s->rx_missed_errors;
// 	
// 	// Transmit
// 	
// 	
// 	return nullptr;
// }
// 
// NetlinkCanParser::DeviceState NetlinkCanParser::operationState(uint8_t state)
// {
// 	if ( state >= static_cast<uint8_t>(DeviceState::STATE_SIZE) )
// 		return DeviceState::UNKNOWN;
// 	else
// 		return static_cast<DeviceState>(state);
// }


} /* namespace CanSocket */
