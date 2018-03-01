/*
 * SocketCan.h
 *
 *  Created on: 22.09.2017
 *      Author: rauser
 */

#ifndef SRC_INCLUDE_SOCKETCAN_H_
#define SRC_INCLUDE_SOCKETCAN_H_

#include <list>
#include <string>
#include <memory>

#include "Base.h"

#include "CANMessage.h"
#include "CANFilter.h"
#include "CANError.h"

namespace CanUtils
{

class SocketCan : public Base<CANMessage>
{

public:
	SocketCan() = delete;
	explicit SocketCan(const std::string& device_arg)
	{
		(void)device_arg;
	}
	virtual ~SocketCan()
	{
	}

	virtual int open() = 0;
	virtual int close() = 0;
	virtual bool isOpen() = 0;

	virtual int write(const CANMessage& msg) = 0;
	virtual int read(CANMessage& message) = 0;

	virtual const std::string& getDevice() const = 0;

	virtual int addFilter(const CANFilter& filter) = 0;
	virtual int removeFilter(const CANFilter& filter) = 0;
	virtual int clearFilter() = 0;
	virtual std::list<CANFilter> getFilterList() = 0;

	virtual int enableLoopback(bool enable) = 0;
	virtual bool loopbackEnabled() const = 0;

	virtual int receiveOwnMessage(bool enable) = 0;
	virtual bool receiveOwnMessageEnabled() const = 0;

	virtual int setErrorFilterMask( CANErrorMask mask ) = 0;
	virtual CANErrorMask getErrorFilterMask() const = 0;
	virtual int clearErrorFilterMask() = 0;
};
typedef std::shared_ptr<SocketCan> SocketCanPtr;

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_SOCKETCAN_H_ */
