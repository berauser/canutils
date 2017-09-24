/*
 * SocketCanImpl.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "SocketCanImpl.h"

#include "logger.h"

#include <stdexcept>

namespace CanSocket
{

SocketCanImpl::SocketCanImpl(const std::string& device_arg)
		: SocketCan(device_arg), device(device_arg)
{
	filterList.clear();
}

SocketCanImpl::~SocketCanImpl()
{
	filterList.clear();
}

int SocketCanImpl::open()
{
	FTRACE(FFDC_SOCKETCAN_DEBUG, "SocketCanImpl::open()");
	if (isOpen())
	{
		FTRACE(FFDC_SOCKETCAN_ERROR, "Device is already opened");
		throw std::logic_error("Device already opened");
	}

	int ret = openDevice();
	if ( ret == 0 )
	{
		recvThread = std::thread(&SocketCanImpl::recvLoop, this);
	}

	return ret;
}

int SocketCanImpl::close()
{
	FTRACE(FFDC_SOCKETCAN_DEBUG, "SocketCanImpl::close()");
	if (!isOpen())
	{
		return 0;
	}

	int ret = closeDevice();

	FTRACE(FFDC_SOCKETCAN_DEBUG, "SocketCanImpl::close() - wait for thread ");
//	FIXME do not join now linux socketcan does not return
//	if (recvThread.joinable())
//	{
//		recvThread.join();
//	}

	return ret;
}

int SocketCanImpl::addListener(SocketCanListener& listener)
{
	FTRACE(FFDC_SOCKETCAN_DEBUG, "SocketCanImpl::addListener( %p )", &listener);
	listeners.push_back(&listener);
	return 0;
}

int SocketCanImpl::removeListener(SocketCanListener& listener)
{
	FTRACE(FFDC_SOCKETCAN_DEBUG, "SocketCanImpl::removeListener( %p )",
			&listener);
	listeners.remove(&listener);
	return 0;
}

std::list<SocketCanListener*> SocketCanImpl::getListeners() const
{
	return listeners;
}

const std::string& SocketCanImpl::getDevice() const
{
	return device;
}

int SocketCanImpl::addFilter(const SocketCan::CANFilter& filter)
{
	FTRACE(FFDC_SOCKETCAN_DEBUG, "SocketCanImpl::addFilter( <%x:%x> )",
			filter.id, filter.mask);
	filterList.push_back(filter);
	return setFilter(filterList);
}

int SocketCanImpl::removeFilter(const SocketCan::CANFilter& filter)
{
	FTRACE(FFDC_SOCKETCAN_DEBUG, "SocketCanImpl::removeFilter( <%x:%x> )",
			filter.id, filter.mask);
	filterList.remove(filter);
	return setFilter(filterList);
}

std::list<SocketCan::CANFilter> SocketCanImpl::getFilterList()
{
	return filterList;
}

void SocketCanImpl::recvLoop()
{
	thread_local int recvbytes;
	thread_local CANMessage message;

	FTRACE(FFDC_SOCKETCAN_DEBUG, "SocketCanImpl::recvLoop() - start");
	while ( isOpen() )
	{
		/* */
		recvbytes = read(&message);
		if (recvbytes < 0)
		{
			/* error */
			FTRACE(FFDC_SOCKETCAN_ERROR, "SocketCanImpl::recvLoop() - error");
			break;
		}
		else if (recvbytes == 0)
		{
			/* Ordinarily close */
			FTRACE(FFDC_SOCKETCAN_INFO, "SocketCanImpl::recvLoop() - shutdown");
			break;
		}
		else if (recvbytes != sizeof(CANMessage))
		{
			/* wrong size */
			FTRACE(FFDC_SOCKETCAN_DEBUG, "SocketCanImpl::recvLoop() - wrong size");
			break;
		}

		for (auto listener : listeners)
		{
			listener->recvMessage(message);
		}
	}

	/* close the current device */
	FTRACE(FFDC_SOCKETCAN_DEBUG, "SocketCanImpl::recvLoop() - close");
	close();
}

} /* namespace CanSocket */
