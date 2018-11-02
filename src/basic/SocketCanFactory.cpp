/*
 * CanUtilsFactory.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "SocketCanFactory.h"

/*************************************************************************//***
 *
 * Includes
 * 
 * ***************************************************************************/
#include <stdexcept>

#ifdef __linux__
	#include "../linux/SocketCanLinux.h"
	#include "../linux/SocketCanInfoLinux.h"
	#include "../linux/SocketCanWorkerLinux.h"
	#include "../linux/SocketCanStatisticsLinux.h"
#else
	#error "No implementation found - Only Linux is implemented" 
#endif

#include "../buffer/CanBufferRegistry.h"

#include "logger.h"
#include "version.h"

namespace CanUtils
{

/*************************************************************************//***
 *
 * Main
 * 
 * ***************************************************************************/
#ifdef __linux__
	#define SocketCanCreate           SocketCanLinux
	#define SocketCanInfoCreate       SocketCanInfoLinux
	#define SocketCanWorkerCreate     SocketCanWorkerLinux
	#define SocketCanStatisticsCreate SocketCanStatisticsLinux
#else
	#error "No implementation found - Only Linux is implemented."
#endif

#define DEFAULT_BUFFER_IMPLEMENTATION "Queue"

SocketCanFactory::SocketCanFactory()
{
}

SocketCanFactory::~SocketCanFactory() noexcept(false)
{
}

std::string SocketCanFactory::version()
{
    return CANUTILS_VERSION_STRING;
}

CanBufferPtr SocketCanFactory::createCanBuffer( const std::string& type, const unsigned int size  )
{
	LOGGER( SOCKETCAN_INFO, "SocketCanFactory::createCanBuffer( %s, %u )", type.c_str(), size );
	
	std::string buffer_type = type;
	if( type == DEFAULT_BUFFER_TYPE )
	{
		buffer_type = DEFAULT_BUFFER_IMPLEMENTATION;
	}
	
	if( !CAN_BUFFER_REGISTRATION->isRegisteredClass( buffer_type ) )
	{
		throw std::invalid_argument("CanBuffer type is unknown");
	}
	
	return CAN_BUFFER_REGISTRATION->get( buffer_type, size );
}

SocketCanPtr SocketCanFactory::createSocketCan(const std::string& device)
{
	LOGGER( SOCKETCAN_INFO, "SocketCanFactory::createSocketCan( %s )", device.c_str() );
	if (device.empty())
	{
		throw std::invalid_argument( "Device is empty" );
	}
	return SocketCanPtr(new SocketCanCreate(device));
}

SocketCanWorkerPtr SocketCanFactory::createSocketCanWorker()
{
        return SocketCanWorkerPtr(new SocketCanWorkerCreate());
}

SocketCanInfoPtr SocketCanFactory::createSocketCanInfo(const std::string& device)
{
	LOGGER( SOCKETCAN_INFO, "SocketCanFactory::createSocketCanInfo( %s )", device.c_str() );
	if (device.empty())
	{
		throw std::invalid_argument( "Device is empty" );
	}
	return SocketCanInfoPtr(new SocketCanInfoCreate(device));
}

SocketCanStatisticsPtr SocketCanFactory::createSocketCanStatistics(const std::string& device)
{
	LOGGER( SOCKETCAN_INFO, "SocketCanFactory::createSocketCanStatistics( %s )", device.c_str() );
	if (device.empty())
	{
		throw std::invalid_argument( "Device is empty" );
	}
	return SocketCanStatisticsPtr(new SocketCanStatisticsCreate(device));
}


} /* namespace CanUtils */
