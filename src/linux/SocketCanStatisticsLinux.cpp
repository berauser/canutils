
#include "SocketCanStatisticsLinux.h"

#include <cstring>

#include "helper/Netlink.h"
#include "helper/NetlinkCanParser.h"

#include "logger.h"

namespace CanSocket
{
  
SocketCanStatisticsLinux::SocketCanStatisticsLinux(const std::string& device_arg): SocketCanStatisticsImpl(device_arg), device(device_arg), netlink(nullptr)
{
	static_assert( sizeof( CanSocket::CANStatistics ) == sizeof( Netlink::NetlinkParser::DeviceStatistics ), "CANStatistics and DeviceStatistics has not the same size" ); 
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

int SocketCanStatisticsLinux::closeDevice()
{
	if( !deviceIsOpen() )
	{
		throw std::logic_error("Device is already closed");
	}
	
	delete netlink;
	netlink = nullptr;
	return 0;
}

bool SocketCanStatisticsLinux::deviceIsOpen()
{
	return ( netlink != nullptr );
}

int SocketCanStatisticsLinux::readDevice(CANStatistics* stats)
{
	if( stats == nullptr )
	{
		throw std::invalid_argument("CANStatistics is nullptr");
	}
	
	Netlink::Netlink::Data* data = netlink->getDeviceInformation( device );
	if( data == nullptr )
	{
		// TODO error
		return -1;
	}
	
	Netlink::NetlinkParser::DeviceStatistics* nstats = Netlink::NetlinkCanParser::parseStatistics( data );
	if ( nstats == nullptr )
	{
		// TODO error
		netlink->destroy(data);
		return -1;
	}
	
	// currently we can use memcpy to copy the struct data
	memcpy( stats, nstats, sizeof(CANStatistics) );
	
	// cleanup
	delete nstats;
	netlink->destroy(data);
	
	return 0;
}

int SocketCanStatisticsLinux::resetStatistics()
{
	return -1;
}

} /* namespace CanSocket */