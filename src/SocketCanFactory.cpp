/*
 * CanSocketFactory.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "SocketCanFactory.h"

#include "logger.h"
#include "SocketCanLinux.h"

#include <stdexcept>

namespace CanSocket
{

#ifdef __linux__
	#define SocketCanCreate SocketCanLinux
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
	STRACE( FFDC_SOCKETCAN_INFO, "SocketCanFactory::createSocketCan( %s )", device.c_str() );
	if (device.empty())
	{
		throw std::invalid_argument( "Device is empty" );
	}

	return new SocketCanCreate(device);
}

} /* namespace CanSocket */
