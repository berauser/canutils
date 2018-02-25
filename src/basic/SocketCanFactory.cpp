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

SocketCanPtr SocketCanFactory::createSocketCan(const std::string& device)
{
	LOGGER( SOCKETCAN_INFO, "SocketCanFactory::createSocketCan( %s )", device.c_str() );
	if (device.empty())
	{
		throw std::invalid_argument( "Device is empty" );
	}
	return std::shared_ptr<SocketCan>(new SocketCanCreate(device));
}

SocketCanInfoPtr SocketCanFactory::createSocketCanInfo(const std::string& device)
{
	LOGGER( SOCKETCAN_INFO, "SocketCanFactory::createSocketCanInfo( %s )", device.c_str() );
	if (device.empty())
	{
		throw std::invalid_argument( "Device is empty" );
	}
	return std::shared_ptr<SocketCanInfo>(new SocketCanInfoCreate(device));
}

SocketCanStatisticsPtr SocketCanFactory::createSocketCanStatistics(const std::string& device)
{
	LOGGER( SOCKETCAN_INFO, "SocketCanFactory::createSocketCanStatistics( %s )", device.c_str() );
	if (device.empty())
	{
		throw std::invalid_argument( "Device is empty" );
	}
	return std::shared_ptr<SocketCanStatistics>(new SocketCanStatisticsCreate(device));
}


} /* namespace CanSocket */
