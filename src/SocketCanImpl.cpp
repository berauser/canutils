/*
 * SocketCanImpl.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "SocketCanImpl.h"

#include "logger.h"

#include <cstring>
#include <stdexcept>

namespace CanSocket
{

bool is_filter_equal( const CANFilter& f1, const CANFilter& f2 )
{
	return ( f1 == f2 );
}

bool compare_filter( const CANFilter& f1, const CANFilter& f2 )
{
	if ( f1.can_id < f2.can_id ) return true;
	if ( f1.can_id > f2.can_id ) return false;
	/* equal -> compare can_mask */
	if ( f1.can_mask < f2.can_mask ) return true;
	if ( f1.can_mask > f2.can_mask ) return false;
	/* equal return true */
	return true;
}

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

int SocketCanImpl::read(CANMessage* message)
{
	thread_local int recvbytes;
	memset(message, 0x00, sizeof(CANMessage));

	if (isOpen() == false)
	{
		throw std::logic_error("Device not open");
	}

	{
		std::lock_guard<std::mutex> lock(mutex_read);
		recvbytes = readDevice(message);
	}

	FTRACE( FFDC_SOCKETCAN_DEBUG, "SocketCanLinux::read() - %x [%d] %x %x %x %x %x %x %x %x",
			message->can_id, message->can_dlc, message->data[0],
			message->data[1], message->data[2], message->data[3],
			message->data[4], message->data[5], message->data[6],
			message->data[7]);

	if (recvbytes < 0)
	{
		// TODO
	}
	else if (recvbytes == 0)
	{
		/* closed */
		FTRACE( FFDC_SOCKETCAN_DEBUG, "SocketCanLinux::read() - shutdown");
		closeDevice();
	}
	return recvbytes;
}

int SocketCanImpl::write(const CANMessage& message)
{
	if( isOpen() == false )
	{
		throw std::logic_error("Device not open");
	}

	FTRACE( FFDC_SOCKETCAN_DEBUG, "SocketCanLinux::write() - %x [%d] %x %x %x %x %x %x %x %x",
			message.can_id, message.can_dlc, message.data[0], message.data[1],
			message.data[2], message.data[3], message.data[4], message.data[5],
			message.data[6], message.data[7]);

	std::lock_guard<std::mutex> lock(mutex_write);
	return writeDevice(message);
}

int SocketCanImpl::addFilter(const CANFilter& filter)
{
	FTRACE(FFDC_SOCKETCAN_DEBUG, "SocketCanImpl::addFilter( <%x:%x> )",
			filter.can_id, filter.can_mask);
	filterList.push_back(filter);
	
	/* remove duplicate */
	filterList.sort(compare_filter);
	filterList.unique(is_filter_equal);
	
	FTRACE(FFDC_SOCKETCAN_ERROR, "Filter size: %ld", filterList.size() );
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
