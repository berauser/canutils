/*
 * CanSocketFactory.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "SocketCanFactory.h"

#include "logger.h"

#include "../linux/SocketCanLinux.h"
#include "../linux/SocketCanInfoLinux.h"
#include "../linux/SocketCanStatisticsLinux.h"

#include <stdexcept>

namespace CanSocket
{

#ifdef __linux__
	#define SocketCanCreate           SocketCanLinux
	#define SocketCanInfoCreate       SocketCanInfoLinux
	#define SocketCanStatisticsCreate SocketCanStatisticsLinux
#else
	#error "No implementation found - Only Linux is implemented."
#endif

SocketCanFactory::SocketCanFactory()
{
}

SocketCanFactory::~SocketCanFactory()
{
}

SocketCan* SocketCanFactory::createSocketCan(const std::string& device)
{
	LOGGER( SOCKETCAN_INFO, "SocketCanFactory::createSocketCan( %s )", device.c_str() );
	if (device.empty())
	{
		throw std::invalid_argument( "Device is empty" );
	}
	return new SocketCanCreate(device);
}

SocketCanInfo* SocketCanFactory::createSocketCanInfo(const std::string& device)
{
	LOGGER( SOCKETCAN_INFO, "SocketCanFactory::createSocketCanInfo( %s )", device.c_str() );
	if (device.empty())
	{
		throw std::invalid_argument( "Device is empty" );
	}
	return new SocketCanInfoCreate(device);
}

SocketCanStatistics* SocketCanFactory::createSocketCanStatistics(const std::string& device)
{
	LOGGER( SOCKETCAN_INFO, "SocketCanFactory::createSocketCanStatistics( %s )", device.c_str() );
	if (device.empty())
	{
		throw std::invalid_argument( "Device is empty" );
	}
	return new SocketCanStatisticsCreate(device);
}


} /* namespace CanSocket */
