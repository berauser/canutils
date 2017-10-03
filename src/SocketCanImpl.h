/*
 * SocketCanImpl.h
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#ifndef SRC_SOCKETCANIMPL_H_
#define SRC_SOCKETCANIMPL_H_

#include "SocketCan.h"

namespace CanSocket
{

class SocketCanImpl: public SocketCan
{
public:
	SocketCanImpl() = delete;
	explicit SocketCanImpl(const std::string& device_arg);
	virtual ~SocketCanImpl();

	virtual int open() override final;
	virtual int close() override final;
	virtual bool isOpen() override = 0;

	virtual int write(const CANMessage& msg) override = 0;
	virtual int read(CANMessage* message) override = 0;

	virtual const std::string& getDevice() const override final;

	virtual int addFilter(const CANFilter& filter) override final;
	virtual int removeFilter(const CANFilter& filter) override final;
	virtual int clearFilter() override final;
	virtual std::list<CANFilter> getFilterList() override final;

protected:
	virtual int openDevice() = 0;
	virtual int closeDevice() = 0;

	virtual int getFiledescriptor() const = 0;

	virtual int setFilter(const std::list<CANFilter>& filterList) = 0;

protected:
	std::string device;
	std::list<CANFilter> filterList;
};

} /* namespace CanSocket */

#endif /* SRC_SOCKETCANIMPL_H_ */
