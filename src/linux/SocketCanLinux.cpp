/*
 * SocketCan.cpp
 *
 *  Created on: 22.09.2017
 *      Author: rauser
 */

#include "SocketCanLinux.h"

#include "logger.h"

#include <cstring>

#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#define SOCKET_INVALID -1

namespace CanSocket
{

SocketCanLinux::SocketCanLinux(const std::string& device_arg)
		: SocketCanImpl(device_arg), socketfd(SOCKET_INVALID)
{
	static_assert( sizeof( CANMessage ) == sizeof( can_frame  ), "CANMessage and can_frame has not the same size" );
	static_assert( sizeof( CANFilter  ) == sizeof( can_filter ), "CANFilter and can_filter has not the same size" );
}

SocketCanLinux::~SocketCanLinux()
{
}

bool SocketCanLinux::isOpen()
{
	return (socketfd != SOCKET_INVALID);
}

int SocketCanLinux::writeDevice(const CANMessage& message)
{
	if (socketfd == SOCKET_INVALID)
	{
		throw std::logic_error("Device not open");
	}

	return ::write(socketfd, &message, sizeof(CANMessage));
}

int SocketCanLinux::readDevice(CANMessage* message)
{
	if (socketfd == SOCKET_INVALID)
	{
		throw std::logic_error("Device not open");
	}
	
	// TODO ioctl call for timestamp
	
	return ::read(socketfd, message, sizeof(CANMessage));
}

int SocketCanLinux::enableLoopback(bool enable)
{
	STRACE( FFDC_SOCKETCAN_DEBUG, "SocketCanLinux::enableLoopback( %s )", ( enable ? "true" : "false" ) );
	if (socketfd == SOCKET_INVALID)
	{
		throw std::logic_error("Device not open");
	}

	int loopback;
	if( enable )
	{
		loopback = 1;
	}
	else
	{
		loopback = 0;
	}

	if( setsockopt(socketfd, SOL_CAN_RAW, CAN_RAW_LOOPBACK, &loopback, sizeof(loopback)) < 0 )
	{
		STRACE( FFDC_SOCKETCAN_ERROR, "SocketCanLinux::enableLoopback() - %s", strerror(errno) );
		return -1;
	}
	return 0;
}

bool SocketCanLinux::loopbackEnabled() const
{
	if (socketfd == SOCKET_INVALID)
	{
		throw std::logic_error("Device not open");
	}

	int loopback = 0;
	socklen_t size = sizeof(loopback);
	if ( getsockopt(socketfd, SOL_CAN_RAW, CAN_RAW_LOOPBACK, &loopback, &size) < 0 )
	{
		STRACE( FFDC_SOCKETCAN_ERROR, "SocketCanLinux::loopbackEnabled() - %s", strerror(errno) );
		return -1;
	}
	return ( loopback == 1 );
}

int SocketCanLinux::receiveOwnMessage(bool enable)
{
	STRACE( FFDC_SOCKETCAN_DEBUG, "SocketCanLinux::receiveOwnMessage( %s )", ( enable ? "true" : "false" ) );
	if (socketfd == SOCKET_INVALID)
	{
		throw std::logic_error("Device not open");
	}

	int own_msgs;
	if( enable )
	{
		own_msgs = 1;
	}
	else
	{
		own_msgs = 0;
	}

	if( setsockopt(socketfd, SOL_CAN_RAW, CAN_RAW_RECV_OWN_MSGS, &own_msgs, sizeof(own_msgs)) < 0 )
	{
		STRACE( FFDC_SOCKETCAN_ERROR, "SocketCanLinux::receiveOwnMessage() - %s", strerror(errno) );
		return -1;
	}
	return 0;
}

bool SocketCanLinux::receiveOwnMessageEnabled() const
{
	if (socketfd == SOCKET_INVALID)
	{
		throw std::logic_error("Device not open");
	}

	int own_msgs = 0;
	socklen_t size = sizeof(own_msgs);
	if ( getsockopt(socketfd, SOL_CAN_RAW, CAN_RAW_RECV_OWN_MSGS, &own_msgs, &size) < 0 )
	{
		STRACE( FFDC_SOCKETCAN_ERROR, "SocketCanLinux::enableReceiveOwnMessage() - %s", strerror(errno) );
		return -1;
	}
	return ( own_msgs == 1 );
}

int SocketCanLinux::openDevice()
{
	const std::string device = getDevice();

	STRACE( FFDC_SOCKETCAN_DEBUG, "SocketCanLinux::openDevice( %s )", device.c_str());
	if (socketfd != SOCKET_INVALID)
	{
		throw std::logic_error("Device already opened");
	}

	struct ifreq ifr;
	struct sockaddr_can addr;
	memset(&ifr, 0, sizeof(struct ifreq));
	memset(&addr, 0, sizeof(struct sockaddr_can));

	socketfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (socketfd < 0)
	{
		socketfd = SOCKET_INVALID;
		return (-1);
	}

	addr.can_family = AF_CAN;
	device.copy(ifr.ifr_name, device.length());

	if (ioctl(socketfd, SIOCGIFINDEX, &ifr) < 0)
	{
		::close(socketfd);
		socketfd = SOCKET_INVALID;
		return (-2);
	}

	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(socketfd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
	{
		::close(socketfd);
		socketfd = SOCKET_INVALID;
		return (-3);
	}

	return 0;
}

int SocketCanLinux::closeDevice()
{
	FTRACE( FFDC_SOCKETCAN_DEBUG, "SocketCanLinux::closeDevice()");
	if (socketfd == SOCKET_INVALID)
	{
		return 0;
	}

	FTRACE( FFDC_SOCKETCAN_DEBUG, "SocketCanLinux::closeDevice() - close");
	int ret = ::close(socketfd);
	if (ret == 0)
	{
		socketfd = SOCKET_INVALID;
	}
	return ret;
}

int SocketCanLinux::getFiledescriptor() const
{
	return socketfd;
}

int SocketCanLinux::setFilter(const std::list<CANFilter>& filterList)
{
	FTRACE( FFDC_SOCKETCAN_DEBUG, "SocketCanLinux::setFilter( <list> )");
	if (socketfd == SOCKET_INVALID)
	{
		throw std::logic_error("Device not open");
	}

	CANFilter rfilter[filterList.size()];

	if (filterList.size() > 0)
	{
		std::copy(filterList.begin(), filterList.end(), rfilter);
	}

	if( setsockopt(socketfd, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter) ) < 0 )
	{
		FTRACE( FFDC_SOCKETCAN_ERROR, "setsockopt: %s", std::strerror( errno ) );
		return -1;
	}

	return 0;
}

} /* namespace CanSocket */

