
#include "SocketCanInfoImpl.h"

namespace CanSocket
{

SocketCanInfoImpl::SocketCanInfoImpl(const std::string& device_arg): SocketCanInfo(device_arg), device(device_arg)
{
	
}

SocketCanInfoImpl::~SocketCanInfoImpl()
{
	
}

const std::string& SocketCanInfoImpl::getDevice() const
{
	return device;
}

CANDeviceInfoPtr SocketCanInfoImpl::read()
{
	openDevice();
	CANDeviceInfoPtr info = readDevice();
	closeDevice();
	
	return info;
}

std::string SocketCanInfo::toString(const CanState& state)
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

std::string SocketCanInfo::toString(const DeviceFlags& flag)
{
	switch( static_cast<unsigned int>(flag) )
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

std::string SocketCanInfo::toString(const ControlMode& mode)
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

std::string SocketCanInfo::toString(const DeviceState& state)
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

} /* namespace CanSocket */