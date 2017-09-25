/*
 * SocketCan.cpp
 *
 *  Created on: 22.09.2017
 *      Author: rauser
 */

#include "SocketCanLinux.h"

#include "logger.h"

#include <cstring>
#include <stdexcept>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#define SOCKET_INVALID -1

namespace CanSocket
{

SocketCanLinux::SocketCanLinux(const std::string& device_arg)
		: SocketCanImpl(device_arg), socketfd( SOCKET_INVALID)
{
	static_assert( sizeof( CANMessage ) == sizeof( can_frame ), "CANMessage and can_frame has not the same size" );
}

SocketCanLinux::~SocketCanLinux()
{
	/* TODO Throw exception of not closed */
}

bool SocketCanLinux::isOpen()
{
	return (socketfd != SOCKET_INVALID);
}

int SocketCanLinux::write(const CANMessage& message)
{
	if (socketfd == SOCKET_INVALID)
	{
		throw std::logic_error("Device not open");
	}

	FTRACE( FFDC_SOCKETCAN_DEBUG, "SocketCanLinux::write() - %x [%d] %x %x %x %x %x %x %x %x",
			message.can_id, message.can_dlc, message.data[0], message.data[1],
			message.data[2], message.data[3], message.data[4], message.data[5],
			message.data[6], message.data[7]);

	return ::write(socketfd, &message, sizeof(CANMessage));
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

int SocketCanLinux::read(CANMessage* message)
{
	// TODO use select or something that can closed by shutdown!!!
	thread_local int recvbytes;
	memset(message, 0x00, sizeof(CANMessage));

	if (socketfd == SOCKET_INVALID)
	{
		throw std::logic_error("Device not open");
	}

	recvbytes = ::read(socketfd, message, sizeof(CANMessage));

	FTRACE( FFDC_SOCKETCAN_DEBUG, "SocketCanLinux::read() - %x [%d] %x %x %x %x %x %x %x %x",
			message->can_id, message->can_dlc, message->data[0],
			message->data[1], message->data[2], message->data[3],
			message->data[4], message->data[5], message->data[6],
			message->data[7]);

	if (recvbytes < 0)
	{
		/* error */
		FTRACE( FFDC_SOCKETCAN_DEBUG, "SocketCanLinux::read() - close");
		closeDevice();
	}
	else if (recvbytes == 0)
	{
		/* closed */
		FTRACE( FFDC_SOCKETCAN_DEBUG, "SocketCanLinux::read() - shutdown");
		closeDevice();
	}
	return recvbytes;
}

int SocketCanLinux::setFilter(const std::list<CANFilter>& filterList)
{
	FTRACE( FFDC_SOCKETCAN_DEBUG, "SocketCanLinux::setFilter( <list> )");
	if (socketfd == SOCKET_INVALID)
	{
		throw std::logic_error("Device not open");
	}

	if (filterList.size() > 0)
	{
		CANFilter* rfilter = new CANFilter[filterList.size()];
		std::copy(filterList.begin(), filterList.end(), rfilter);
		return setsockopt(socketfd, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter,
				sizeof(filterList.size()));
	}
	else
	{
		return setsockopt(socketfd, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);
	}
}

} /* namespace CanSocket */
