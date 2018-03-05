#include "NetlinkCanParser.h"
#include "NetlinkHelper.h"

#include <string>
#include <cstring>

#include <sys/socket.h>

#include <linux/if.h>
#include <linux/can/netlink.h>

namespace Netlink
{

NetlinkCanParser::NetlinkCanParser()
{

}

NetlinkCanParser::~NetlinkCanParser()
{
}

NetlinkCanParser::CanDeviceDetailsPtr NetlinkCanParser::parseCanDetails(Netlink::DataPtr data)
{
	if( data->tb[IFLA_LINKINFO] )
	{
		struct rtattr *linkinfo[IFLA_INFO_MAX+1];
		
		Helper::parse_rtattr_nested( linkinfo, IFLA_INFO_MAX, data->tb[IFLA_LINKINFO]);
		if( ! linkinfo[IFLA_INFO_KIND] ) return 0;
		
		char* kind = (char*)RTA_DATA( linkinfo[IFLA_INFO_KIND] );
		(void) kind;
		
		CanDeviceDetailsPtr details(new CanDeviceDetails);
		if( linkinfo[IFLA_INFO_DATA] )
		{
			struct rtattr *attr[IFLA_CAN_MAX+1];
			Helper::parse_rtattr_nested(attr, IFLA_CAN_MAX, linkinfo[IFLA_INFO_DATA]);
			
			if( attr[IFLA_CAN_CTRLMODE] )
				parseControlMode( attr[IFLA_CAN_CTRLMODE], details );
			if( attr[IFLA_CAN_STATE] )
				parseCanState( attr[IFLA_CAN_STATE], details );
			if( attr[IFLA_CAN_BERR_COUNTER] )
				parseBerrCounter( attr[IFLA_CAN_BERR_COUNTER], details );
			if( attr[IFLA_CAN_BITTIMING] )
				parseCanBittiming( attr[IFLA_CAN_BITTIMING], details );
			if( attr[IFLA_CAN_BITTIMING_CONST] )
				parseCanBittimingConst( attr[IFLA_CAN_BITTIMING_CONST], details);
			if( attr[IFLA_CAN_CLOCK] )
				parseCanClock( attr[IFLA_CAN_CLOCK], details );
			if( attr[IFLA_CAN_RESTART_MS] )
				details->restart_ms = *(uint32_t*)RTA_DATA(attr[IFLA_CAN_RESTART_MS]);
		}
		if( linkinfo[IFLA_INFO_XSTATS] )
		{
			if( linkinfo[IFLA_INFO_XSTATS] )
				parseCanDeviceStatistics( linkinfo[IFLA_INFO_XSTATS], details );
		}
		return details;
	}
	
// 	memset( details, 0, sizeof(CanDeviceDetails) )
	
	return nullptr;
}

std::string NetlinkCanParser::canStateToString(NetlinkCanParser::CanState state)
{
	switch( static_cast<unsigned int>(state) )
	{
	case static_cast<unsigned int>(CanState::ERROR_ACTIVE):  return "ERROR_ACTIVE";
	case static_cast<unsigned int>(CanState::ERROR_PASSIV):  return "ERROR_PASSIV";
	case static_cast<unsigned int>(CanState::ERROR_WARNING): return "ERROR_WARNING";
	case static_cast<unsigned int>(CanState::BUS_OFF):       return "BUS_OFF";
	case static_cast<unsigned int>(CanState::SLEEPING):      return "SLEEPING";
	case static_cast<unsigned int>(CanState::STOPPED):       return "STOPPED";
	default: return "UNKNOWN";
	}
}

std::string NetlinkCanParser::controlModeToString(NetlinkCanParser::ControlMode mode)
{
	switch( static_cast<unsigned int>(mode) )
	{
	case static_cast<unsigned int>(ControlMode::LOOPBACK):        return "LOOPBACK";
	case static_cast<unsigned int>(ControlMode::LISTEN_ONLY):     return "LISTEN_ONLY";
	case static_cast<unsigned int>(ControlMode::TRIPLE_SAMPLING): return "TRIPLE_SAMPLING";
	case static_cast<unsigned int>(ControlMode::ONE_SHOT):        return "ONE_SHOT";
	case static_cast<unsigned int>(ControlMode::BERR_REPORTING):  return "BERR_REPORTING";
	case static_cast<unsigned int>(ControlMode::FD):              return "FD";
	case static_cast<unsigned int>(ControlMode::PRESUME_ACK):     return "PRESUME_ACK";
	case static_cast<unsigned int>(ControlMode::FD_NON_ISO):      return "FD_NON_ISO";
	default:                                                      return "UNKNOWN";
	}
}

NetlinkCanParser::CanState NetlinkCanParser::canState(unsigned int data)
{
	if( data >= CAN_STATE_MAX )
	{
		return CanState::UNKNOWN;
	}
	
	switch( data )
	{
	case CAN_STATE_ERROR_ACTIVE:  return CanState::ERROR_ACTIVE;
	case CAN_STATE_ERROR_PASSIVE: return CanState::ERROR_PASSIV;
	case CAN_STATE_ERROR_WARNING: return CanState::ERROR_WARNING;
	case CAN_STATE_BUS_OFF:       return CanState::BUS_OFF;
	case CAN_STATE_SLEEPING:      return CanState::SLEEPING;
	case CAN_STATE_STOPPED:       return CanState::STOPPED;
	default: return CanState::UNKNOWN;
	}
}

int NetlinkCanParser::parseCanClock(struct rtattr* data, NetlinkCanParser::CanDeviceDetailsPtr details)
{
	struct can_clock *clock = static_cast<can_clock*>(RTA_DATA(data));
	details->clock_freq = clock->freq;
	return 0;
}

int NetlinkCanParser::parseCanState (struct rtattr* data, CanDeviceDetailsPtr details)
{
	details->state = canState( *(unsigned int*)RTA_DATA(data) );
	return 0;
}

int NetlinkCanParser::parseControlMode(struct rtattr* data, NetlinkCanParser::CanDeviceDetailsPtr details)
{
	struct can_ctrlmode *cm = static_cast<struct can_ctrlmode*>(RTA_DATA(data));
	for( unsigned int i = 0; i < sizeof(cm->flags)*8; i++ )
	{
		switch( cm->flags & (1 << i) )
		{
		case CAN_CTRLMODE_LOOPBACK:       details->mode.push_back( ControlMode::LOOPBACK );        break;
		case CAN_CTRLMODE_LISTENONLY:     details->mode.push_back( ControlMode::LISTEN_ONLY );     break;
		case CAN_CTRLMODE_3_SAMPLES:      details->mode.push_back( ControlMode::TRIPLE_SAMPLING ); break;
		case CAN_CTRLMODE_ONE_SHOT:       details->mode.push_back( ControlMode::ONE_SHOT );        break;
		case CAN_CTRLMODE_BERR_REPORTING: details->mode.push_back( ControlMode::BERR_REPORTING );  break;
		case CAN_CTRLMODE_FD:             details->mode.push_back( ControlMode::FD );              break;
		case CAN_CTRLMODE_PRESUME_ACK:    details->mode.push_back( ControlMode::PRESUME_ACK );     break;
		case CAN_CTRLMODE_FD_NON_ISO:     details->mode.push_back( ControlMode::FD_NON_ISO );      break;
		default: continue;
		}
	}
	return 0;
}

int NetlinkCanParser::parseBerrCounter(struct rtattr* data, NetlinkCanParser::CanDeviceDetailsPtr details)
{
	struct can_berr_counter *bc = static_cast<struct can_berr_counter*>(RTA_DATA(data));
	details->berr.tx_error = bc->txerr;
	details->berr.rx_error = bc->rxerr;
	return 0;
}

int NetlinkCanParser::parseCanBittiming(struct rtattr* data, NetlinkCanParser::CanDeviceDetailsPtr details)
{
	struct can_bittiming *bt = static_cast<struct can_bittiming*>(RTA_DATA(data));
	details->bittiming.bitrate      = bt->bitrate;
	details->bittiming.sample_point = bt->sample_point;
	details->bittiming.tq           = bt->tq;
	details->bittiming.prop_seg     = bt->prop_seg;
	details->bittiming.phase_seg1   = bt->phase_seg1;
	details->bittiming.phase_seg2   = bt->phase_seg2;
	details->bittiming.sjw          = bt->sjw;
	details->bittiming.brp          = bt->brp;
	return 0;
}

int NetlinkCanParser::parseCanBittimingConst(struct rtattr* data, NetlinkCanParser::CanDeviceDetailsPtr details)
{
	struct can_bittiming_const *btc = static_cast<struct can_bittiming_const*>(RTA_DATA(data));
	details->const_bittiming.name      = btc->name;
	details->const_bittiming.tseg1_min = btc->tseg1_min;
	details->const_bittiming.tseg1_max = btc->tseg1_max;
	details->const_bittiming.tseg2_min = btc->tseg2_min;
	details->const_bittiming.tseg2_max = btc->tseg2_max;
	details->const_bittiming.sjw_max   = btc->sjw_max;
	details->const_bittiming.brp_min   = btc->brp_min;
	details->const_bittiming.brp_max   = btc->brp_max;
	details->const_bittiming.brp_inc   = btc->brp_inc;
	return 0;
}

int NetlinkCanParser::parseCanDeviceStatistics(struct rtattr* data, CanDeviceDetailsPtr details)
{
	struct can_device_stats *stats = static_cast<struct can_device_stats*>(RTA_DATA(data));
	(void) stats;
	(void) details;
	return 0;
}

} /* namespace Netlink */
