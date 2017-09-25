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

namespace CanSocket
{

class SocketCan
{
public:
	struct CANFilter
	{
		uint32_t id;
		uint32_t mask;
		bool inverted;

		bool operator==(const CANFilter& f1) const
		{
			return (this->id == f1.id && this->mask == f1.mask && this->inverted == f1.inverted);
		}

		bool operator!=(const CANFilter& f1) const
		{
			return (this->id != f1.id || this->mask != f1.mask || this->inverted != f1.inverted );
		}
	};

public:
	SocketCan() = delete;
	SocketCan(const std::string& device_arg)
	{
	}
	virtual ~SocketCan()
	{
	}

	virtual int open() = 0;
	virtual int close() = 0;
	virtual bool isOpen() = 0;

	virtual int write(const CANMessage& msg) = 0;

	virtual int setListener(SocketCanListener* listener) = 0;
	virtual SocketCanListener* getListener() = 0;

	virtual const std::string& getDevice() const = 0;

	virtual int addFilter(const CANFilter& filter) = 0;
	virtual int removeFilter(const CANFilter& filter) = 0;
	virtual int clearFilter() = 0;
	virtual std::list<CANFilter> getFilterList() = 0;
};

} /* namespace CanSocket */

#endif /* SRC_SOCKETCAN_H_ */
