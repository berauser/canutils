
#include "NetlinkParser.h"

#include <cstring>
#include <stdexcept>

namespace CanSocket
{

NetlinkParser::NetlinkParser() 
{
}

NetlinkParser::~NetlinkParser()
{
}

NetlinkParser::DeviceDetails* NetlinkParser::parseDetails(Netlink::Data* data)
{
	if( data == nullptr )
	{
		throw std::invalid_argument("Netlink::Data is nullptr");
	}
	
	DeviceDetails* details = new DeviceDetails;
	if( details == nullptr )
	{
		throw std::bad_alloc();
	}
	memset( details, 0, sizeof(DeviceDetails) );
	
	details->ifindex = data->index;
	details->ifname  = data->name;
	details->iftype  = data->type;
	
	if ( data->tb[IFLA_MTU]       )
		details->mtu   = *(int*)RTA_DATA(data->tb[IFLA_MTU]);
	if ( data->tb[IFLA_QDISC]     ) 
		details->qdisc = (char*)RTA_DATA(data->tb[IFLA_QDISC]);
	if ( data->tb[IFLA_OPERSTATE] ) 
		details->state = operationState ( *(unsigned int*)(data->tb[IFLA_OPERSTATE]) );
// 	if ( data->tb[IFLA_MASTER]    )
// 		;
	if ( data->tb[IFLA_TXQLEN]    )
		details->tx_qlen = *(int*)RTA_DATA(data->tb[IFLA_TXQLEN]);
// 	if ( data->tb[IFLA_ADDRESS]   )
// 		;
// 	if ( data->tb[IFLA_BROADCAST] )
// 		;
	if ( data->tb[IFLA_IFALIAS]   )
		details->ifalias = (const char*)RTA_DATA(data->tb[IFLA_IFALIAS]);
		
	return nullptr;
}
  
NetlinkParser::DeviceStatistics* NetlinkParser::parseStatistics(Netlink::Data* data)
{
	DeviceStatistics *stats = new DeviceStatistics;
	if( stats == nullptr )
	{
		throw std::bad_alloc();
	}
	memset( stats, 0, sizeof(DeviceStatistics) );
	
	if ( data->tb[IFLA_STATS64] )
	{
		// 64bit statistics
		parseStatistics64( data, stats );
	}
	else if ( data->tb[IFLA_STATS] )
	{
		// 32bit statistics
		parseStatistics32( data, stats );
	}
	else
	{
		// no statistics return;
		return stats;
	}
	
	return stats;
}

std::string NetlinkParser::deviceStateToString(const NetlinkParser::DeviceState& state)
{
	(void)state;
	return "";
}

std::string NetlinkParser::deviceFlagsToString(const NetlinkParser::DeviceFlags& flags)
{
	(void)flags;
	return "";
}

NetlinkParser::DeviceState NetlinkParser::operationState(unsigned int state)
{
	switch( state )
	{
	case 0x01:	return DeviceState::NOTPRESENT;
	case 0x02:	return DeviceState::DOWN;
	case 0x03:	return DeviceState::LOWERLAYERDOWN;
	case 0x04:	return DeviceState::TESTING;
	case 0x05:	return DeviceState::DORMANT;
	case 0x06:	return DeviceState::UP;
	case 0x07:	return DeviceState::STATE_SIZE;
	case 0x00:
	default:	return DeviceState::UNKNOWN;
	}
}

int NetlinkParser::parseStatistics32(Netlink::Data* data, NetlinkParser::DeviceStatistics* stats)
{
  	struct rtnl_link_stats *s;
	s = static_cast<struct rtnl_link_stats*>(RTA_DATA( data->tb[IFLA_STATS]));
	
	// FIXME: Here we have many valgrind warnings. How to prevent?
	//        Invalid read of size 8: XXXX bytes below stack pointer
	
	// Receive stats
	stats->rx_bytes   = s->rx_bytes;
	stats->rx_packets = s->rx_packets;
	stats->rx_errors  = s->rx_errors;
	stats->rx_dropped = s->rx_dropped;
	stats->rx_overrun_errors = s->rx_over_errors;
	stats->rx_multicast      = s->multicast;
	stats->rx_compressed     = s->rx_compressed;
	stats->rx_length_errors  = s->rx_length_errors;
	stats->rx_crc_errors     = s->rx_crc_errors;
	stats->rx_frame_errors   = s->rx_frame_errors;
	stats->rx_fifo_errors    = s->rx_fifo_errors;
	stats->rx_missed_errors = s->rx_missed_errors;
	
	// Transmit
	stats->tx_bytes   = s->tx_bytes;
	stats->tx_packets = s->tx_packets;
	stats->tx_errors  = s->tx_errors;
	stats->tx_dropped = s->tx_dropped;
	stats->tx_carrier_errors   = s->tx_carrier_errors;
	stats->tx_collisions       = s->collisions;
	stats->tx_compressed       = s->tx_compressed;
	stats->tx_aborted_errors   = s->tx_aborted_errors;
	stats->tx_fifo_errors      = s->tx_fifo_errors;
	stats->tx_window_errors    = s->tx_window_errors;
	stats->tx_heartbeat_errors = s->tx_heartbeat_errors;
	
	return 0;
}


int NetlinkParser::parseStatistics64(Netlink::Data* data, NetlinkParser::DeviceStatistics* stats)
{
	struct rtnl_link_stats64* s;
	s = static_cast<struct rtnl_link_stats64*>(RTA_DATA(data->tb[IFLA_STATS64]));
	
	// FIXME: Here we have many valgrind warnings. How to prevent?
	//        Invalid read of size 8: XXXX bytes below stack pointer
	
	// Receive stats
	stats->rx_bytes   = s->rx_bytes;
	stats->rx_packets = s->rx_packets;
	stats->rx_errors  = s->rx_errors;
	stats->rx_dropped = s->rx_dropped;
	stats->rx_overrun_errors = s->rx_over_errors;
	stats->rx_multicast      = s->multicast;
	stats->rx_compressed     = s->rx_compressed;
	stats->rx_length_errors  = s->rx_length_errors;
	stats->rx_crc_errors     = s->rx_crc_errors;
	stats->rx_frame_errors   = s->rx_frame_errors;
	stats->rx_fifo_errors    = s->rx_fifo_errors;
	stats->rx_missed_errors = s->rx_missed_errors;
	
	// Transmit
	stats->tx_bytes   = s->tx_bytes;
	stats->tx_packets = s->tx_packets;
	stats->tx_errors  = s->tx_errors;
	stats->tx_dropped = s->tx_dropped;
	stats->tx_carrier_errors   = s->tx_carrier_errors;
	stats->tx_collisions       = s->collisions;
	stats->tx_compressed       = s->tx_compressed;
	stats->tx_aborted_errors   = s->tx_aborted_errors;
	stats->tx_fifo_errors      = s->tx_fifo_errors;
	stats->tx_window_errors    = s->tx_window_errors;
	stats->tx_heartbeat_errors = s->tx_heartbeat_errors;
	
	return 0;
}



} /* namespace CanSocket */