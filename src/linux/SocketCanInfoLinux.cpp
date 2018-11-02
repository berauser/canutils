
#include "SocketCanInfoLinux.h"

#include <cstring>

#include "logger.h"

#include <linux/if.h>

namespace CanUtils
{

SocketCanInfoLinux::SocketCanInfoLinux(const std::string& device_arg): SocketCanInfoImpl(device_arg), device(device_arg), netlink(Netlink::NetlinkWrapperPtr(new Netlink::NetlinkWrapper))
{
    // assert device if empty
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
	
	if( netlink->open() < 0 )
	{
		throw std::runtime_error("Could not open netlink");
	}
	
	return 0;
}

int SocketCanInfoLinux::closeDevice()
{
	if( !deviceIsOpen() )
	{
		throw std::logic_error("Device is already closed");
	}
	
	netlink->close();
	return 0;
}

bool SocketCanInfoLinux::deviceIsOpen()
{
	return netlink->isOpen();
}

CANDeviceInfoPtr SocketCanInfoLinux::readDevice()
{
	CANDeviceInfoPtr info(new struct CANDeviceInfo);
	if( info == nullptr )
	{
		throw std::bad_alloc();
	}
	
    struct rtnl_link* link = netlink->link_get(device);

#define CHECK_NULL(x) (((x)==nullptr)?"":(x))    
	info->device_details.ifindex = rtnl_link_get_ifindex(link);
	info->device_details.ifname  = CHECK_NULL(rtnl_link_get_name(link));
	info->device_details.iftype  = CHECK_NULL(rtnl_link_get_type(link));
	info->device_details.ifalias = CHECK_NULL(rtnl_link_get_ifalias(link));
	info->device_details.flags   = getDeviceFlags(link);
	info->device_details.mtu     = rtnl_link_get_mtu(link);
	info->device_details.tx_qlen = rtnl_link_get_txqlen(link);
	info->device_details.qdisc   = CHECK_NULL(rtnl_link_get_qdisc(link));
	info->device_details.state   = DeviceState(rtnl_link_get_operstate(link));
#undef CHECK_NULL

	if(  isCanDevice(link) ) 
	{
		info->can_device_details.state      = getCanState(link);
		info->can_device_details.clock_freq = getClockFrequency(link);
		info->can_device_details.restart_ms = getRestartMS(link);
		info->can_device_details.mode       = getControlMode(link);
		info->berr_counter.tx_error         = getBerrCountTxErr(link);
		info->berr_counter.rx_error         = getBerrCountRxErr(link);

		getBittiming(link, &info->bittiming);
		getBittimingConst(link, &info->bittiming_const);
	}

	netlink->link_put(link);
	return info;
}

CanState SocketCanInfoLinux::getCanState(struct rtnl_link* link)
{
	uint32_t can_state = 0;
	if( rtnl_link_can_state(link, &can_state) < 0 )
	{
		can_state = CAN_STATE_MAX;
	}

	CanState return_can_state;
	switch(can_state)
	{
		case CAN_STATE_ERROR_ACTIVE:
			return_can_state = CanState::ERROR_ACTIVE;
			break;
		case CAN_STATE_ERROR_WARNING:
			return_can_state = CanState::ERROR_WARNING;
			break;
		case CAN_STATE_ERROR_PASSIVE:
			return_can_state = CanState::ERROR_PASSIV;
			break;
		case CAN_STATE_BUS_OFF:
			return_can_state = CanState::BUS_OFF;
			break;
		case CAN_STATE_STOPPED:
			return_can_state = CanState::STOPPED;
			break;
		case CAN_STATE_SLEEPING:
			return_can_state = CanState::SLEEPING;
			break;
		case CAN_STATE_MAX:
		default:
			return_can_state = CanState::UNKNOWN;
			break;
	}

	return return_can_state;
}

bool SocketCanInfoLinux::isCanDevice(struct rtnl_link* link)
{
	return (rtnl_link_is_can (link) == 1);
}

uint32_t SocketCanInfoLinux::getClockFrequency(struct rtnl_link* link)
{
	uint32_t clock_freq = 0;
	if( rtnl_link_can_freq(link, &clock_freq) == 0 )
	{
		return clock_freq;
	}
	return 0;
}

uint32_t SocketCanInfoLinux::getRestartMS(struct rtnl_link* link)
{
	uint32_t restart_ms = 0;
	if( rtnl_link_can_get_restart_ms(link, &restart_ms) == 0 )
	{
		return restart_ms;
	}
	return 0;
}

uint16_t SocketCanInfoLinux::getBerrCountTxErr(struct rtnl_link* link)
{
	int berr_tx = rtnl_link_can_berr_tx(link);
	if( berr_tx < 0 )
	{
		berr_tx = 0;
	}
	return berr_tx;
}

uint16_t SocketCanInfoLinux::getBerrCountRxErr(struct rtnl_link* link)
{
	int berr_rx = rtnl_link_can_berr_tx(link);
	if( berr_rx < 0 )
	{
		berr_rx = 0;
	}
	return berr_rx;
}

void SocketCanInfoLinux::getBittiming(struct rtnl_link* link, CanBittiming* bittiming)
{
	struct can_bittiming cb;
	if( rtnl_link_can_get_bittiming(link, &cb) < 0 )
	{
		memset(&cb, 0, sizeof(struct can_bittiming));
	}

	bittiming->bitrate      = cb.bitrate;
	bittiming->sample_point = cb.sample_point;
	bittiming->tq           = cb.tq;
	bittiming->prop_seg     = cb.prop_seg;
	bittiming->phase_seg1   = cb.phase_seg1;
	bittiming->phase_seg2   = cb.phase_seg2;
	bittiming->sjw          = cb.sjw;
	bittiming->brp          = cb.brp;
}

void SocketCanInfoLinux::getBittimingConst(struct rtnl_link* link, CanBittimingConst* bittiming_const)
{
	struct can_bittiming_const cbc;
	if( rtnl_link_can_get_bt_const(link, &cbc) < 0 )
	{
		memset(&cbc, 0, sizeof(struct can_bittiming_const));
		memset(&cbc.name, '\0', sizeof(cbc.name));
	}
	
	bittiming_const->name      = cbc.name;
	bittiming_const->tseg1_min = cbc.tseg1_min;
	bittiming_const->tseg1_max = cbc.tseg1_max;
	bittiming_const->tseg2_min = cbc.tseg2_min;
	bittiming_const->tseg2_max = cbc.tseg2_max;
	bittiming_const->sjw_max   = cbc.sjw_max;
	bittiming_const->brp_min   = cbc.brp_min;
	bittiming_const->brp_max   = cbc.brp_max;
	bittiming_const->brp_inc   = cbc.brp_inc;
}

std::vector< DeviceFlags > SocketCanInfoLinux::getDeviceFlags(struct rtnl_link* link)
{
	unsigned int flags = rtnl_link_get_flags(link);
	
	std::vector< DeviceFlags > device_flags;
	for( unsigned int i = 0; i < (sizeof(flags)*8); ++i )
	{
		switch( (flags & (1<<i)) )
		{
		  case IFF_UP:          device_flags.push_back(DeviceFlags::UP);          break;
		  case IFF_BROADCAST:   device_flags.push_back(DeviceFlags::BROADCAST);   break;
		  case IFF_DEBUG:       device_flags.push_back(DeviceFlags::DEBUG);       break;
		  case IFF_LOOPBACK:    device_flags.push_back(DeviceFlags::LOOPBACK);    break;
		  case IFF_POINTOPOINT: device_flags.push_back(DeviceFlags::POINTOPOINT); break;
		  case IFF_NOTRAILERS:  device_flags.push_back(DeviceFlags::NOTRAILERS);  break;
		  case IFF_RUNNING:     device_flags.push_back(DeviceFlags::RUNNING);     break;
		  case IFF_NOARP:       device_flags.push_back(DeviceFlags::NOARP);       break;
		  case IFF_PROMISC:     device_flags.push_back(DeviceFlags::PROMISC);     break;
		  case IFF_ALLMULTI:    device_flags.push_back(DeviceFlags::ALLMULTI);    break;
		  case IFF_MASTER:      device_flags.push_back(DeviceFlags::MASTER);      break;
		  case IFF_SLAVE:       device_flags.push_back(DeviceFlags::SLAVE);       break;
		  case IFF_MULTICAST:   device_flags.push_back(DeviceFlags::MULTICAST);   break;
		  case IFF_PORTSEL:     device_flags.push_back(DeviceFlags::PORTSEL);     break;
		  case IFF_AUTOMEDIA:   device_flags.push_back(DeviceFlags::AUTOMEDIA);   break;
		  case IFF_DYNAMIC:     device_flags.push_back(DeviceFlags::DYNAMIC);     break;
		  case IFF_LOWER_UP:    device_flags.push_back(DeviceFlags::LOWERUP);     break;
		  case IFF_DORMANT:     device_flags.push_back(DeviceFlags::DORMANT);     break;
		  case IFF_ECHO:        device_flags.push_back(DeviceFlags::ECHO);        break;
		  default:              continue;                                         break;
		};
	}
	return device_flags;
}

std::vector<ControlMode> SocketCanInfoLinux::getControlMode(struct rtnl_link* link)
{
	uint32_t mode = 0;
	if( rtnl_link_can_get_ctrlmode(link, &mode) < 0 )
	{
		mode = 0;
	}
	
	std::vector<ControlMode> modes;
	for( unsigned int i = 0; i < sizeof(mode)*8; i++ )
	{
		switch( mode & (1 << i) )
		{
		case CAN_CTRLMODE_LOOPBACK:       modes.push_back( ControlMode::LOOPBACK );        break;
		case CAN_CTRLMODE_LISTENONLY:     modes.push_back( ControlMode::LISTEN_ONLY );     break;
		case CAN_CTRLMODE_3_SAMPLES:      modes.push_back( ControlMode::TRIPLE_SAMPLING ); break;
		case CAN_CTRLMODE_ONE_SHOT:       modes.push_back( ControlMode::ONE_SHOT );        break;
		case CAN_CTRLMODE_BERR_REPORTING: modes.push_back( ControlMode::BERR_REPORTING );  break;
		case CAN_CTRLMODE_FD:             modes.push_back( ControlMode::FD );              break;
		case CAN_CTRLMODE_PRESUME_ACK:    modes.push_back( ControlMode::PRESUME_ACK );     break;
		case CAN_CTRLMODE_FD_NON_ISO:     modes.push_back( ControlMode::FD_NON_ISO );      break;
		default: continue;
		}
	}
	return modes;
}

} /* namespace CanUtils */
