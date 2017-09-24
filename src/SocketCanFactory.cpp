/*
 * CanSocketFactory.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "SocketCanFactory.h"

#include "SocketCanLinux.h"

namespace CanSocket
{

#ifdef __linux__
	#define SocketCanCreate SocketCanLinux
#else
	#error "Not implemented - Only linux."
#endif

SocketCanFactory::SocketCanFactory()
{
}

SocketCanFactory::~SocketCanFactory()
{
}

SocketCan* SocketCanFactory::createSocketCan(const std::string& device)
{
	if (device.empty())
	{
		/* TODO here we should throw an excpetion */
		return nullptr;
	}

	return new SocketCanCreate(device);
}

} /* namespace CanSocket */
