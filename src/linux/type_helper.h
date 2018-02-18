
#ifndef SRC_TYPEHELPER_H_
#define SRC_TYPEHELPER_H_

#include "CANDeviceInfo.h"
#include "helper/NetlinkParser.h"
#include "helper/NetlinkCanParser.h"

#include <exception>

namespace CanSocket
{

struct type_helper {
	DeviceFlags operator=(const Netlink::NetlinkParser::DeviceFlags& f)
	{
		using namespace Netlink;
		switch( static_cast<unsigned int>(f) )
		{
// 		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::NOCARRIER):   return DeviceFlags::NOCARRIER; 
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::LOOPBACK):    return DeviceFlags::LOOPBACK; 
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::BROADCAST):   return DeviceFlags::BROADCAST; 
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::POINTOPOINT): return DeviceFlags::POINTOPOINT; 
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::MULTICAST):   return DeviceFlags::MULTICAST; 
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::NOARP):       return DeviceFlags::NOARP; 
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::ALLMULTI):    return DeviceFlags::ALLMULTI; 
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::PROMISC):     return DeviceFlags::PROMISC;
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::MASTER):      return DeviceFlags::MASTER; 
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::SLAVE):       return DeviceFlags::SLAVE; 
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::DEBUG):       return DeviceFlags::DEBUG; 
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::DYNAMIC):     return DeviceFlags::DYNAMIC;
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::AUTOMEDIA):   return DeviceFlags::AUTOMEDIA; 
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::PORTSEL):     return DeviceFlags::PORTSEL; 
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::NOTRAILERS):  return DeviceFlags::NOTRAILERS; 
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::UP):          return DeviceFlags::UP; 
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::LOWERUP):     return DeviceFlags::LOWERUP; 
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::DORMANT):     return DeviceFlags::DORMANT;
		case static_cast<unsigned int>(NetlinkParser::DeviceFlags::ECHO):        return DeviceFlags::ECHO;
		default: throw std::out_of_range("Unknown convertion to DeviceFLags");   return DeviceFlags::UNKNOWN;
		}
	}
	
	Netlink::NetlinkParser::DeviceFlags operator=(const DeviceFlags& f)
	{
		using namespace Netlink;
		switch( static_cast<unsigned int>(f) )
		{
// 		case static_cast<unsigned int>(DeviceFlags::NOCARRIER):   return NetlinkParser::DeviceFlags::NOCARRIER; 
		case static_cast<unsigned int>(DeviceFlags::LOOPBACK):    return NetlinkParser::DeviceFlags::LOOPBACK; 
		case static_cast<unsigned int>(DeviceFlags::BROADCAST):   return NetlinkParser::DeviceFlags::BROADCAST; 
		case static_cast<unsigned int>(DeviceFlags::POINTOPOINT): return NetlinkParser::DeviceFlags::POINTOPOINT; 
		case static_cast<unsigned int>(DeviceFlags::MULTICAST):   return NetlinkParser::DeviceFlags::MULTICAST; 
		case static_cast<unsigned int>(DeviceFlags::NOARP):       return NetlinkParser::DeviceFlags::NOARP; 
		case static_cast<unsigned int>(DeviceFlags::ALLMULTI):    return NetlinkParser::DeviceFlags::ALLMULTI; 
		case static_cast<unsigned int>(DeviceFlags::PROMISC):     return NetlinkParser::DeviceFlags::PROMISC;
		case static_cast<unsigned int>(DeviceFlags::MASTER):      return NetlinkParser::DeviceFlags::MASTER; 
		case static_cast<unsigned int>(DeviceFlags::SLAVE):       return NetlinkParser::DeviceFlags::SLAVE; 
		case static_cast<unsigned int>(DeviceFlags::DEBUG):       return NetlinkParser::DeviceFlags::DEBUG; 
		case static_cast<unsigned int>(DeviceFlags::DYNAMIC):     return NetlinkParser::DeviceFlags::DYNAMIC;
		case static_cast<unsigned int>(DeviceFlags::AUTOMEDIA):   return NetlinkParser::DeviceFlags::AUTOMEDIA; 
		case static_cast<unsigned int>(DeviceFlags::PORTSEL):     return NetlinkParser::DeviceFlags::PORTSEL; 
		case static_cast<unsigned int>(DeviceFlags::NOTRAILERS):  return NetlinkParser::DeviceFlags::NOTRAILERS; 
		case static_cast<unsigned int>(DeviceFlags::UP):          return NetlinkParser::DeviceFlags::UP; 
		case static_cast<unsigned int>(DeviceFlags::LOWERUP):     return NetlinkParser::DeviceFlags::LOWERUP; 
		case static_cast<unsigned int>(DeviceFlags::DORMANT):     return NetlinkParser::DeviceFlags::DORMANT;
		case static_cast<unsigned int>(DeviceFlags::ECHO):        return NetlinkParser::DeviceFlags::ECHO;
		default: throw std::out_of_range("Unknown convertion to NetlinkParser::DeviceFLags");   return NetlinkParser::DeviceFlags::UNKNOWN;
		}
	}
	
	DeviceState operator=(const Netlink::NetlinkParser::DeviceState& s)
	{
		using namespace Netlink;
		switch( static_cast<unsigned int>(s) )
		{
		case static_cast<unsigned int>(NetlinkParser::DeviceState::UNKNOWN):        return DeviceState::UNKNOWN;
		case static_cast<unsigned int>(NetlinkParser::DeviceState::NOTPRESENT):     return DeviceState::NOTPRESENT;
		case static_cast<unsigned int>(NetlinkParser::DeviceState::DOWN):           return DeviceState::DOWN;
		case static_cast<unsigned int>(NetlinkParser::DeviceState::LOWERLAYERDOWN): return DeviceState::LOWERLAYERDOWN;
		case static_cast<unsigned int>(NetlinkParser::DeviceState::TESTING):        return DeviceState::TESTING;
		case static_cast<unsigned int>(NetlinkParser::DeviceState::DORMANT):        return DeviceState::DORMANT;
		case static_cast<unsigned int>(NetlinkParser::DeviceState::UP):             return DeviceState::UP;
		case static_cast<unsigned int>(NetlinkParser::DeviceState::STATE_SIZE):     return DeviceState::STATE_SIZE;
		default: throw std::out_of_range("Unknown convertion to DeviceState");      return DeviceState::UNKNOWN;
		};
	}
	
	Netlink::NetlinkParser::DeviceState operator=(const DeviceState& s)
	{
		using namespace Netlink;
		switch( static_cast<unsigned int>(s) )
		{
		case static_cast<unsigned int>(DeviceState::UNKNOWN):        return NetlinkParser::DeviceState::UNKNOWN;
		case static_cast<unsigned int>(DeviceState::NOTPRESENT):     return NetlinkParser::DeviceState::NOTPRESENT;
		case static_cast<unsigned int>(DeviceState::DOWN):           return NetlinkParser::DeviceState::DOWN;
		case static_cast<unsigned int>(DeviceState::LOWERLAYERDOWN): return NetlinkParser::DeviceState::LOWERLAYERDOWN;
		case static_cast<unsigned int>(DeviceState::TESTING):        return NetlinkParser::DeviceState::TESTING;
		case static_cast<unsigned int>(DeviceState::DORMANT):        return NetlinkParser::DeviceState::DORMANT;
		case static_cast<unsigned int>(DeviceState::UP):             return NetlinkParser::DeviceState::UP;
		case static_cast<unsigned int>(DeviceState::STATE_SIZE):     return NetlinkParser::DeviceState::STATE_SIZE;
		default: throw std::out_of_range("Unknown convertion to NetlinkParser::DeviceState"); return NetlinkParser::DeviceState::UNKNOWN;
		};
	}
	
	ControlMode operator=(const Netlink::NetlinkCanParser::ControlMode& m)
	{
		using namespace Netlink;
		switch( static_cast<unsigned int>(m) )
		{
		case static_cast<unsigned int>(NetlinkCanParser::ControlMode::LOOPBACK):        return ControlMode::LOOPBACK;
		case static_cast<unsigned int>(NetlinkCanParser::ControlMode::LISTEN_ONLY):     return ControlMode::LISTEN_ONLY;
		case static_cast<unsigned int>(NetlinkCanParser::ControlMode::TRIPLE_SAMPLING): return ControlMode::TRIPLE_SAMPLING;
		case static_cast<unsigned int>(NetlinkCanParser::ControlMode::ONE_SHOT):        return ControlMode::ONE_SHOT;
		case static_cast<unsigned int>(NetlinkCanParser::ControlMode::BERR_REPORTING):  return ControlMode::BERR_REPORTING;
		case static_cast<unsigned int>(NetlinkCanParser::ControlMode::FD):              return ControlMode::FD;
		case static_cast<unsigned int>(NetlinkCanParser::ControlMode::PRESUME_ACK):     return ControlMode::PRESUME_ACK;
		case static_cast<unsigned int>(NetlinkCanParser::ControlMode::FD_NON_ISO):      return ControlMode::FD_NON_ISO;
		default: throw std::out_of_range("Unknown convertion to ControlMode");          return ControlMode::UNKNOWN;
		};
	}
	
	Netlink::NetlinkCanParser::ControlMode operator=(const ControlMode& m)
	{
		using namespace Netlink;
		switch( static_cast<unsigned int>(m) )
		{
		case static_cast<unsigned int>(ControlMode::LOOPBACK):        return NetlinkCanParser::ControlMode::LOOPBACK;
		case static_cast<unsigned int>(ControlMode::LISTEN_ONLY):     return NetlinkCanParser::ControlMode::LISTEN_ONLY;
		case static_cast<unsigned int>(ControlMode::TRIPLE_SAMPLING): return NetlinkCanParser::ControlMode::TRIPLE_SAMPLING;
		case static_cast<unsigned int>(ControlMode::ONE_SHOT):        return NetlinkCanParser::ControlMode::ONE_SHOT;
		case static_cast<unsigned int>(ControlMode::BERR_REPORTING):  return NetlinkCanParser::ControlMode::BERR_REPORTING;
		case static_cast<unsigned int>(ControlMode::FD):              return NetlinkCanParser::ControlMode::FD;
		case static_cast<unsigned int>(ControlMode::PRESUME_ACK):     return NetlinkCanParser::ControlMode::PRESUME_ACK;
		case static_cast<unsigned int>(ControlMode::FD_NON_ISO):      return NetlinkCanParser::ControlMode::FD_NON_ISO;
		default: throw std::out_of_range("Unknown convertion to NetlinkCanParser::ControlMode"); return NetlinkCanParser::ControlMode::UNKNOWN;
		};
	}
	
	CanState operator=(const Netlink::NetlinkCanParser::CanState& s)
	{
		using namespace Netlink;
		switch( static_cast<unsigned int>(s) )
		{
		case static_cast<unsigned int>(NetlinkCanParser::CanState::ERROR_ACTIVE):  return CanState::ERROR_ACTIVE;
		case static_cast<unsigned int>(NetlinkCanParser::CanState::ERROR_WARNING): return CanState::ERROR_WARNING;
		case static_cast<unsigned int>(NetlinkCanParser::CanState::ERROR_PASSIV):  return CanState::ERROR_PASSIV;
		case static_cast<unsigned int>(NetlinkCanParser::CanState::BUS_OFF):       return CanState::BUS_OFF;
		case static_cast<unsigned int>(NetlinkCanParser::CanState::STOPPED):       return CanState::STOPPED;
		case static_cast<unsigned int>(NetlinkCanParser::CanState::SLEEPING):      return CanState::SLEEPING;
		case static_cast<unsigned int>(NetlinkCanParser::CanState::UNKNOWN):       return CanState::UNKNOWN;
		default: throw std::out_of_range("Unknown convertion to ControlState");    return CanState::UNKNOWN;
		};
	}
	
	Netlink::NetlinkCanParser::CanState operator=(const CanState& s)
	{
		using namespace Netlink;
		switch( static_cast<unsigned int>(s) )
		{
		case static_cast<unsigned int>(CanState::ERROR_ACTIVE):  return NetlinkCanParser::CanState::ERROR_ACTIVE;
		case static_cast<unsigned int>(CanState::ERROR_WARNING): return NetlinkCanParser::CanState::ERROR_WARNING;
		case static_cast<unsigned int>(CanState::ERROR_PASSIV):  return NetlinkCanParser::CanState::ERROR_PASSIV;
		case static_cast<unsigned int>(CanState::BUS_OFF):       return NetlinkCanParser::CanState::BUS_OFF;
		case static_cast<unsigned int>(CanState::STOPPED):       return NetlinkCanParser::CanState::STOPPED;
		case static_cast<unsigned int>(CanState::SLEEPING):      return NetlinkCanParser::CanState::SLEEPING;
		case static_cast<unsigned int>(CanState::UNKNOWN):       return NetlinkCanParser::CanState::UNKNOWN;
		default: throw std::out_of_range("Unknown convertion to NetlinkCanParser::ControlState"); return NetlinkCanParser::CanState::UNKNOWN;
		};
	}
};
} /* namespace CanSocket */

#endif /* SRC_TYPEHELPER_H_ */