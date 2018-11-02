
#include "SocketCanStatisticsLinux.h"

#include <cstring>

#include "logger.h"

namespace CanUtils
{

SocketCanStatisticsLinux::SocketCanStatisticsLinux(const std::string& device_arg): SocketCanStatisticsImpl(device_arg), device(device_arg), netlink(Netlink::NetlinkWrapperPtr(new Netlink::NetlinkWrapper))
{
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
	
	if( netlink->open() < 0 )
	{
		throw std::runtime_error("Could not open netlink");
	}
	
	return 0;
}

int SocketCanStatisticsLinux::closeDevice()
{
	if( !deviceIsOpen() )
	{
		throw std::logic_error("Device is already closed");
	}
	netlink->close();
	return 0;
}

bool SocketCanStatisticsLinux::deviceIsOpen()
{
	return netlink->isOpen();
}

CANStatisticsPtr SocketCanStatisticsLinux::readDevice()
{
	CANStatisticsPtr stats(new struct CANStatistics);
	struct rtnl_link* link =  netlink->link_get(device.c_str());
	if(link == nullptr)
	{
		return nullptr; // FIXME
	}
	    
	// Receive stats
	stats->rx_bytes   = rtnl_link_get_stat(link, RTNL_LINK_RX_BYTES);
	stats->rx_packets = rtnl_link_get_stat(link, RTNL_LINK_RX_PACKETS);
	stats->rx_errors  = rtnl_link_get_stat(link, RTNL_LINK_RX_ERRORS);
	stats->rx_dropped = rtnl_link_get_stat(link, RTNL_LINK_RX_DROPPED);
	stats->rx_overrun_errors = rtnl_link_get_stat(link, RTNL_LINK_RX_OVER_ERR);
	stats->rx_multicast      = rtnl_link_get_stat(link, RTNL_LINK_MULTICAST);
	stats->rx_compressed     = rtnl_link_get_stat(link, RTNL_LINK_RX_COMPRESSED);
	stats->rx_length_errors  = rtnl_link_get_stat(link, RTNL_LINK_RX_LEN_ERR);
	stats->rx_crc_errors     = rtnl_link_get_stat(link, RTNL_LINK_RX_CRC_ERR);
	stats->rx_frame_errors   = rtnl_link_get_stat(link, RTNL_LINK_RX_FRAME_ERR);
	stats->rx_fifo_errors    = rtnl_link_get_stat(link, RTNL_LINK_RX_FIFO_ERR);
	stats->rx_missed_errors = rtnl_link_get_stat(link, RTNL_LINK_RX_MISSED_ERR);
	
	// Transmit
	stats->tx_bytes   = rtnl_link_get_stat(link, RTNL_LINK_TX_BYTES);
	stats->tx_packets = rtnl_link_get_stat(link, RTNL_LINK_TX_PACKETS);
	stats->tx_errors  = rtnl_link_get_stat(link, RTNL_LINK_TX_ERRORS);
	stats->tx_dropped = rtnl_link_get_stat(link, RTNL_LINK_TX_DROPPED);
	stats->tx_carrier_errors   = rtnl_link_get_stat(link, RTNL_LINK_TX_CARRIER_ERR);
	stats->tx_collisions       = rtnl_link_get_stat(link, RTNL_LINK_COLLISIONS);
	stats->tx_compressed       = rtnl_link_get_stat(link, RTNL_LINK_TX_COMPRESSED);
	stats->tx_aborted_errors   = rtnl_link_get_stat(link, RTNL_LINK_TX_ABORT_ERR);
	stats->tx_fifo_errors      = rtnl_link_get_stat(link, RTNL_LINK_TX_FIFO_ERR);
	stats->tx_window_errors    = rtnl_link_get_stat(link, RTNL_LINK_TX_WIN_ERR);
	stats->tx_heartbeat_errors = rtnl_link_get_stat(link, RTNL_LINK_TX_HBEAT_ERR);
	
	netlink->link_put(link);
	return stats;
}

int SocketCanStatisticsLinux::resetStatistics()
{
	// not possible
	return -1;
}


} /* namespace CanUtils */
