/*
 * SocketCanImpl.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "SocketCanImpl.h"

namespace SocketCan {

SocketCanImpl::SocketCanImpl(const std::string& device_arg)
	: SocketCan( device_arg ),
	  device( device_arg)
{
	filterList.clear();
}

SocketCanImpl::~SocketCanImpl()
{
	filterList.clear();
}

const std::string& SocketCanImpl::getDevice() const
{
	return device;
}

int SocketCanImpl::addFilter(const SocketCan::CANFilter& filter)
{
	filterList.push_back( filter );
	return setFilter( filterList );
}

int SocketCanImpl::removeFilter(const SocketCan::CANFilter& filter)
{
	filterList.remove( filter );
	return setFilter( filterList );
}

std::list<SocketCan::CANFilter> SocketCanImpl::getFilterList()
{
	return filterList;
}

} /* namespace SocketCan */
