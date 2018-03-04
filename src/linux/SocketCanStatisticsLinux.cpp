
#include "SocketCanStatisticsLinux.h"

#include <cstring>

#include "netlink/Netlink.h"
#include "netlink/NetlinkCanParser.h"

#include "logger.h"

namespace CanUtils
{
  
SocketCanStatisticsLinux::SocketCanStatisticsLinux(const std::string& device_arg): SocketCanStatisticsImpl(device_arg), device(device_arg), netlink(nullptr)
{
	static_assert( sizeof( CanUtils::CANStatistics ) == sizeof( Netlink::NetlinkParser::DeviceStatistics ), "CANStatistics and DeviceStatistics has not the same size" ); 
}

SocketCanStatisticsLinux::~SocketCanStatisticsLinux()
{
	if ( deviceIsOpen() )
	{
		throw std::logic_error("Device is not closed while it is being destroyed"); 
	}
}

int SocketCanStatisticsLinux::openDevice()
{
	if( deviceIsOpen() )
	{
		throw std::logic_error("Device is already opened");
	}
	
	netlink = Netlink::NetlinkPtr(new Netlink::Netlink);
	if( netlink == nullptr )
	{
		throw std::runtime_error("Could not allocate memory");
	}
	
	if( netlink->open() != 0 )
	{
		throw std::runtime_error("Could not create netlink socket");
	}
	return 0;
}

int SocketCanStatisticsLinux::closeDevice()
{
	if( !deviceIsOpen() )
	{
		throw std::logic_error("Device is already closed");
	}
	
	netlink.reset();
	return 0;
}

bool SocketCanStatisticsLinux::deviceIsOpen()
{
	return ( netlink != nullptr );
}

CANStatisticsPtr SocketCanStatisticsLinux::readDevice()
{
	CANStatisticsPtr stats(new struct CANStatistics);
	
	if( stats == nullptr )
	{
		throw std::bad_alloc();
	}
	
	Netlink::Netlink::DataPtr data = netlink->getDeviceInformation( device );
	if( data == nullptr )
	{
		throw std::bad_alloc();
	}
	
	Netlink::NetlinkParser::DeviceStatisticsPtr nstats = Netlink::NetlinkCanParser::parseStatistics( data );
	if ( nstats == nullptr )
	{
		throw std::runtime_error("Netlink returns a nullptr");
	}
	copyStatistics( stats, nstats );
	return stats;
}

int SocketCanStatisticsLinux::resetStatistics()
{
	return -1;
}

int SocketCanStatisticsLinux::copyStatistics(CANStatisticsPtr stats, Netlink::NetlinkParser::DeviceStatisticsPtr nstats)
{
	// Receive stats
	stats->rx_bytes   = nstats->rx_bytes;
	stats->rx_packets = nstats->rx_packets;
	stats->rx_errors  = nstats->rx_errors;
	stats->rx_dropped = nstats->rx_dropped;
	stats->rx_overrun_errors = nstats->rx_overrun_errors;
	stats->rx_multicast      = nstats->rx_multicast;
	stats->rx_compressed     = nstats->rx_compressed;
	stats->rx_length_errors  = nstats->rx_length_errors;
	stats->rx_crc_errors     = nstats->rx_crc_errors;
	stats->rx_frame_errors   = nstats->rx_frame_errors;
	stats->rx_fifo_errors    = nstats->rx_fifo_errors;
	stats->rx_missed_errors = nstats->rx_missed_errors;
	
	// Transmit
	stats->tx_bytes   = nstats->tx_bytes;
	stats->tx_packets = nstats->tx_packets;
	stats->tx_errors  = nstats->tx_errors;
	stats->tx_dropped = nstats->tx_dropped;
	stats->tx_carrier_errors   = nstats->tx_carrier_errors;
	stats->tx_collisions       = nstats->tx_collisions;
	stats->tx_compressed       = nstats->tx_compressed;
	stats->tx_aborted_errors   = nstats->tx_aborted_errors;
	stats->tx_fifo_errors      = nstats->tx_fifo_errors;
	stats->tx_window_errors    = nstats->tx_window_errors;
	stats->tx_heartbeat_errors = nstats->tx_heartbeat_errors;
	
	return 0;
}


} /* namespace CanUtils */
