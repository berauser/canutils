/*
 * SocketCanImpl.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "SocketCanImpl.h"

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
	if (isOpen())
	{
		throw std::logic_error("Device already opened");
	}

	recvThread = std::thread(&SocketCanImpl::recvLoop, this);

	return openDevice(device);
}

int SocketCanImpl::close()
{
	if (!isOpen())
	{
		return 0;
	}

	int ret = closeDevice();

	if (recvThread.joinable())
	{
		recvThread.join();
	}

	return ret;
}

int SocketCanImpl::addListener(SocketCanListener& listener)
{
	listeners.push_back(&listener);
	return 0;
}

int SocketCanImpl::removeListener(SocketCanListener& listener)
{
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
	filterList.push_back(filter);
	return setFilter(filterList);
}

int SocketCanImpl::removeFilter(const SocketCan::CANFilter& filter)
{
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

	while (true)
	{
		/* */
		recvbytes = read(&message);
		if (recvbytes < 0)
		{
			/* error */
			break;
		}
		else if (recvbytes == 0)
		{
			/* Ordinarily close */
			break;
		}
		else if (recvbytes != sizeof(CANMessage))
		{
			/* wrong size */
			break;
		}

		for (auto listener : listeners)
		{
			listener->recvMessage(message);
		}
	}

	/* close the current device */
	close();
}

} /* namespace CanSocket */
