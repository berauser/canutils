
#include "SocketCanInfoLinux.h"

#include <cstring>

#include "helper/Netlink.h"
#include "helper/NetlinkCanParser.h"

#include "type_helper.h"
#include "logger.h"

namespace CanSocket
{
  
SocketCanInfoLinux::SocketCanInfoLinux(const std::string& device_arg): SocketCanInfoImpl(device_arg), device(device_arg), netlink(nullptr)
{
// 	static_assert( sizeof( CanSocket::CANStatistics ) == sizeof( Netlink::NetlinkParser::DeviceStatistics ), "CANStatistics and DeviceStatistics has not the same size" ); 
}

SocketCanInfoLinux::~SocketCanInfoLinux()
{
	if ( deviceIsOpen() )
	{
		throw std::logic_error("Device is not closed while it is being destroyed"); 
	}
}

int SocketCanInfoLinux::openDevice()
{
	if( deviceIsOpen() )
	{
		throw std::logic_error("Device is already opened");
	}
	
	netlink = new Netlink::Netlink;
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

int SocketCanInfoLinux::closeDevice()
{
	if( !deviceIsOpen() )
	{
		throw std::logic_error("Device is already closed");
	}
	
	delete netlink;
	netlink = nullptr;
	return 0;
}

bool SocketCanInfoLinux::deviceIsOpen()
{
	return ( netlink != nullptr );
}

CANDeviceInfoPtr SocketCanInfoLinux::readDevice()
{
	CANDeviceInfoPtr info(new struct CANDeviceInfo);
	if( info == nullptr )
	{
		throw std::bad_alloc();
	}
	
	Netlink::Netlink::DataPtr data = netlink->getDeviceInformation( device );
	if( data == nullptr )
	{
		throw std::bad_alloc();
	}
	
	Netlink::NetlinkParser::DeviceDetailsPtr device_details = Netlink::NetlinkParser::parseDetails( data );
	if ( device_details == nullptr )
	{
		throw std::bad_alloc();
	}
	copyDetails( info, device_details );
	
	Netlink::NetlinkCanParser::CanDeviceDetailsPtr can_device_details = Netlink::NetlinkCanParser::parseCanDetails( data );
	if ( device_details == nullptr )
	{
		throw std::bad_alloc();
	}
	copyCanDetails( info, can_device_details );
	
	return info;
}

int SocketCanInfoLinux::copyDetails(CANDeviceInfoPtr info, Netlink::NetlinkParser::DeviceDetailsPtr dev)
{
	if( info == nullptr || dev == nullptr )
	{
		return -1;
	}
  
	info->device_details.ifindex = dev->ifindex;
	info->device_details.ifname  = dev->ifname;
	info->device_details.iftype  = dev->iftype;
	info->device_details.ifalias = dev->ifalias;
	info->device_details.flags   = copyDeviceFlags(dev->flags);
	info->device_details.mtu     = dev->mtu;
	info->device_details.tx_qlen = dev->tx_qlen;
	info->device_details.qdisc   = dev->qdisc;
	info->device_details.state   = DeviceState(dev->state);
	return 0;
}

int SocketCanInfoLinux::copyCanDetails(CANDeviceInfoPtr info, Netlink::NetlinkCanParser::CanDeviceDetailsPtr cdev)
{
	if( info == nullptr || cdev == nullptr )
	{
		return -1;
	}
	
	info->can_device_details.state      = CanState(cdev->state);
	info->can_device_details.clock_freq = cdev->clock_freq;
	info->can_device_details.restart_ms = cdev->restart_ms;
	info->can_device_details.mode       = copyControlMode(cdev->mode);
	
	info->berr_counter.tx_error         = cdev->berr.tx_error;
	info->berr_counter.rx_error         = cdev->berr.tx_error;
	
	info->bittiming.bitrate             = cdev->bittiming.bitrate;
	info->bittiming.sample_point        = cdev->bittiming.sample_point;
	info->bittiming.tq                  = cdev->bittiming.tq;
	info->bittiming.prop_seg            = cdev->bittiming.prop_seg;
	info->bittiming.phase_seg1          = cdev->bittiming.phase_seg1;
	info->bittiming.phase_seg2          = cdev->bittiming.phase_seg2;
	info->bittiming.sjw                 = cdev->bittiming.sjw;
	info->bittiming.brp                 = cdev->bittiming.brp;
	
	info->bittiming_const.name          = cdev->const_bittiming.name;
	info->bittiming_const.tseg1_min     = cdev->const_bittiming.tseg1_min;
	info->bittiming_const.tseg1_max     = cdev->const_bittiming.tseg1_max;
	info->bittiming_const.tseg2_min     = cdev->const_bittiming.tseg2_min;
	info->bittiming_const.tseg2_max     = cdev->const_bittiming.tseg2_max;
	info->bittiming_const.sjw_max       = cdev->const_bittiming.sjw_max;
	info->bittiming_const.brp_min       = cdev->const_bittiming.brp_min;
	info->bittiming_const.brp_max       = cdev->const_bittiming.brp_max;
	info->bittiming_const.brp_inc       = cdev->const_bittiming.brp_inc;
	return 0;
}

std::vector< DeviceFlags > SocketCanInfoLinux::copyDeviceFlags(std::vector< Netlink::NetlinkParser::DeviceFlags >& vec)
{
	std::vector< DeviceFlags > flags;
	for( Netlink::NetlinkParser::DeviceFlags flag : vec )
	{
		flags.push_back( DeviceFlags(flag) );
	}
	return flags;
}

std::vector< ControlMode > SocketCanInfoLinux::copyControlMode(std::vector< Netlink::NetlinkCanParser::ControlMode >& vec)
{
	std::vector< ControlMode > modes;
	for( Netlink::NetlinkCanParser::ControlMode mode : vec )
	{
		modes.push_back( ControlMode(mode) );
	}
	return modes;
}

} /* namespace CanSocket */