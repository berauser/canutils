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
		FTRACE(FFDC_SOCKETCAN_INFO, "Device is already opened");
		throw std::logic_error("Device already opened");
	}
	return openDevice();
}

int SocketCanImpl::close()
{
	FTRACE(FFDC_SOCKETCAN_DEBUG, "SocketCanImpl::close()");
	if (!isOpen())
	{
		FTRACE(FFDC_SOCKETCAN_INFO, "Device is already closed");
		return 0;
	}
	return closeDevice();
}

const std::string& SocketCanImpl::getDevice() const
{
	return device;
}

int SocketCanImpl::addFilter(const CANFilter& filter)
{
	FTRACE(FFDC_SOCKETCAN_DEBUG, "SocketCanImpl::addFilter( <%x:%x> )",
			filter.can_id, filter.can_mask);
	filterList.push_back(filter);
	return setFilter(filterList);
}

int SocketCanImpl::removeFilter(const CANFilter& filter)
{
	FTRACE(FFDC_SOCKETCAN_DEBUG, "SocketCanImpl::removeFilter( <%x:%x> )",
			filter.can_id, filter.can_mask);
	filterList.remove(filter);
	return setFilter(filterList);
}

int SocketCanImpl::clearFilter()
{
	FTRACE(FFDC_SOCKETCAN_DEBUG, "SocketCanImpl::clearFilter()");
	filterList.clear();
	filterList.push_back( CANFilter( 0x000, 0x000 ) ); // match all
	return setFilter(filterList);
}

std::list<CANFilter> SocketCanImpl::getFilterList()
{
	return filterList;
}

} /* namespace CanSocket */
