
#include "NetlinkParser.h"

#include <cstring>
#include <stdexcept>

#include <sys/types.h>
#include <sys/socket.h>

#include <linux/if.h>

namespace Netlink
{

NetlinkParser::NetlinkParser() 
{
}

NetlinkParser::~NetlinkParser()
{
}

NetlinkParser::DeviceDetailsPtr NetlinkParser::parseDetails(Netlink::DataPtr data)
{
	if( data == nullptr )
	{
		throw std::invalid_argument("Netlink::Data is nullptr");
	}
	
	DeviceDetailsPtr details(new DeviceDetails);
	if( details == nullptr )
	{
		throw std::bad_alloc();
	}

	details->ifindex = data->index;
	details->ifname  = data->name;
	details->iftype  = Netlink::typeToString(data->type);
	
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
	
	parseDeviceFlags( data, details );
	
	return details;
}
  
NetlinkParser::DeviceStatisticsPtr NetlinkParser::parseStatistics(Netlink::DataPtr data)
{
	DeviceStatisticsPtr stats(new DeviceStatistics);
	if( stats == nullptr )
	{
		throw std::bad_alloc();
	}
// 	memset( stats, 0, sizeof(DeviceStatistics) );
	
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
	switch( static_cast<unsigned int>(state) )
	{
	case static_cast<unsigned int>(DeviceState::NOTPRESENT):     return "NOT_PRESENT";
	case static_cast<unsigned int>(DeviceState::DOWN):           return "DOWN";
	case static_cast<unsigned int>(DeviceState::LOWERLAYERDOWN): return "LOWER_LAYER_DOWN";
	case static_cast<unsigned int>(DeviceState::TESTING):        return "TESTING";
	case static_cast<unsigned int>(DeviceState::DORMANT):        return "DORMANT";
	case static_cast<unsigned int>(DeviceState::UP):             return "UP";
	case static_cast<unsigned int>(DeviceState::STATE_SIZE):     return "STATE_SIZE";
	case static_cast<unsigned int>(DeviceState::UNKNOWN):
	default: return "UNKNOWN";
	}
}

std::string NetlinkParser::deviceFlagsToString(const NetlinkParser::DeviceFlags& flags)
{
	switch( static_cast<unsigned int>(flags) )
	{
	  case static_cast<unsigned int>(DeviceFlags::UP):          return "UP";
	  case static_cast<unsigned int>(DeviceFlags::BROADCAST):   return "BROADCAST";
	  case static_cast<unsigned int>(DeviceFlags::DEBUG):       return "DEBUG";
	  case static_cast<unsigned int>(DeviceFlags::LOOPBACK):    return "LOOPBACK";
	  case static_cast<unsigned int>(DeviceFlags::POINTOPOINT): return "POINT_O_POINT";
	  case static_cast<unsigned int>(DeviceFlags::NOTRAILERS):  return "NO_TRAILERS";
	  case static_cast<unsigned int>(DeviceFlags::RUNNING):     return "RUNNING";
	  case static_cast<unsigned int>(DeviceFlags::NOARP):       return "NO_ARP";
	  case static_cast<unsigned int>(DeviceFlags::PROMISC):     return "PRMISC";
	  case static_cast<unsigned int>(DeviceFlags::ALLMULTI):    return "ALL_MULTI";
	  case static_cast<unsigned int>(DeviceFlags::MASTER):      return "MASTER";
	  case static_cast<unsigned int>(DeviceFlags::SLAVE):       return "SLAVE";
	  case static_cast<unsigned int>(DeviceFlags::MULTICAST):   return "MULTICAST";
	  case static_cast<unsigned int>(DeviceFlags::PORTSEL):     return "PORTSEL";
	  case static_cast<unsigned int>(DeviceFlags::AUTOMEDIA):   return "AUTOMEDIA";
	  case static_cast<unsigned int>(DeviceFlags::DYNAMIC):     return "DYNAMIC";
	  case static_cast<unsigned int>(DeviceFlags::LOWERUP):     return "LOWER_UP";
	  case static_cast<unsigned int>(DeviceFlags::DORMANT):     return "DORMANT";
	  case static_cast<unsigned int>(DeviceFlags::ECHO):        return "ECHO";
	  default:                                                  return "UNKNOWN";
	}
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

int NetlinkParser::parseDeviceFlags(Netlink::DataPtr data, NetlinkParser::DeviceDetailsPtr details)
{
	if( ! data->flags ) return 0;
	
	for( unsigned int i = 0; i < (sizeof(data->flags)*8); ++i )
	{
		switch( (data->flags & (1<<i)) )
		{
		  case IFF_UP:          details->flags.push_back(DeviceFlags::UP);          break;
		  case IFF_BROADCAST:   details->flags.push_back(DeviceFlags::BROADCAST);   break;
		  case IFF_DEBUG:       details->flags.push_back(DeviceFlags::DEBUG);       break;
		  case IFF_LOOPBACK:    details->flags.push_back(DeviceFlags::LOOPBACK);    break;
		  case IFF_POINTOPOINT: details->flags.push_back(DeviceFlags::POINTOPOINT); break;
		  case IFF_NOTRAILERS:  details->flags.push_back(DeviceFlags::NOTRAILERS);  break;
		  case IFF_RUNNING:     details->flags.push_back(DeviceFlags::RUNNING);     break;
		  case IFF_NOARP:       details->flags.push_back(DeviceFlags::NOARP);       break;
		  case IFF_PROMISC:     details->flags.push_back(DeviceFlags::PROMISC);     break;
		  case IFF_ALLMULTI:    details->flags.push_back(DeviceFlags::ALLMULTI);    break;
		  case IFF_MASTER:      details->flags.push_back(DeviceFlags::MASTER);      break;
		  case IFF_SLAVE:       details->flags.push_back(DeviceFlags::SLAVE);       break;
		  case IFF_MULTICAST:   details->flags.push_back(DeviceFlags::MULTICAST);   break;
		  case IFF_PORTSEL:     details->flags.push_back(DeviceFlags::PORTSEL);     break;
		  case IFF_AUTOMEDIA:   details->flags.push_back(DeviceFlags::AUTOMEDIA);   break;
		  case IFF_DYNAMIC:     details->flags.push_back(DeviceFlags::DYNAMIC);     break;
		  case IFF_LOWER_UP:    details->flags.push_back(DeviceFlags::LOWERUP);     break;
		  case IFF_DORMANT:     details->flags.push_back(DeviceFlags::DORMANT);     break;
		  case IFF_ECHO:        details->flags.push_back(DeviceFlags::ECHO);        break;
		  default:              continue;                                           break;
		};
	}
	
	return 0;
}

int NetlinkParser::parseStatistics32(Netlink::DataPtr data, NetlinkParser::DeviceStatisticsPtr stats)
{
	struct rtnl_link_stats *s;
	s = static_cast<struct rtnl_link_stats*>(RTA_DATA( data->tb[IFLA_STATS]));
	
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


int NetlinkParser::parseStatistics64(Netlink::DataPtr data, NetlinkParser::DeviceStatisticsPtr stats)
{
	struct rtnl_link_stats64* s;
	s = static_cast<struct rtnl_link_stats64*>(RTA_DATA(data->tb[IFLA_STATS64]));
	
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



} /* namespace Netlink */