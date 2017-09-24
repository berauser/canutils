/*
 * SocketCan.h
 *
 *  Created on: 22.09.2017
 *      Author: rauser
 */

#ifndef SRC_SOCKETCAN_H_
#define SRC_SOCKETCAN_H_

#include <list>
#include <string>
#include <cstdint>

#include "CANMessage.h"
#include "SocketCanListener.h"

namespace SocketCan
{

class SocketCan
{
public:
	struct CANFilter {
		uint32_t id;
		uint32_t mask;

		bool operator==( const CANFilter& f1 )
		{
			return ( this->id == f1.id && this->mask == f1.mask );
		}
	};

public:
	SocketCan() = delete;
	SocketCan( const std::string& device_arg ) {}
	virtual ~SocketCan() {}

	virtual bool open() = 0;
	virtual bool close() = 0;

	virtual int write( const CANMessage& msg ) = 0;
	virtual int registerListener( SocketCanListener& listener ) = 0;

	virtual SocketCan& operator=( const SocketCan& src ) = 0;
	virtual SocketCan& operator=( SocketCan&& src ) = 0;

	virtual const int getFiledescriptor() const = 0;
	virtual const std::string& getDevice() const = 0;

	virtual int addFilter   ( const CANFilter& filter ) = 0;
	virtual int removeFilter( const CANFilter& filter ) = 0;
	virtual std::list<CANFilter> getFilterList() = 0;
};

} /* namespace SocketCan */

#endif /* SRC_SOCKETCAN_H_ */
