/*
 * SocketCan.h
 *
 *  Created on: 22.09.2017
 *      Author: rauser
 */

#ifndef SRC_SOCKETCAN_H_
#define SRC_SOCKETCAN_H_

#include <string>

#include "CANMessage.h"
#include "SocketCanListener.h"

namespace SocketCan
{

class SocketCan
{

public:
	SocketCan() = delete;
	SocketCan( const std::string& device_arg ) : device( device_arg ) {}
	virtual ~SocketCan() {}

	virtual bool open() = 0;
	virtual bool close() = 0;

	virtual int write( const CANMessage& msg ) = 0;
	virtual int registerListener( SocketCanListener& listener ) = 0;

	virtual SocketCan& operator=( const SocketCan& src ) = 0;
	virtual SocketCan& operator=( SocketCan&& src ) = 0;

	virtual const int getFiledescriptor() const = 0;
	virtual const std::string& getDevice() const = 0;

protected:
	std::string device;
};

} /* namespace SocketCan */

#endif /* SRC_SOCKETCAN_H_ */
