/*
 * SocketCanImpl.h
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#ifndef SRC_BASIC_SOCKETCANIMPL_H_
#define SRC_BASIC_SOCKETCANIMPL_H_

#include "SocketCan.h"

#include <mutex>

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

	virtual int read(CANMessage& message) override final;
	virtual int write(const CANMessage& msg) override final;

	virtual const std::string& getDevice() const override final;

	virtual int addFilter(const CANFilter& filter) override final;
	virtual int removeFilter(const CANFilter& filter) override final;
	virtual int clearFilter() override final;
	virtual std::list<CANFilter> getFilterList() override final;

	virtual int setErrorFilterMask( CANErrorMask mask ) override final;
	virtual CANErrorMask getErrorFilterMask() const override final;
	virtual int clearErrorFilterMask() override final;
	
protected:
	virtual int openDevice() = 0;
	virtual int closeDevice() = 0;
	virtual int readDevice(CANMessage& message) = 0;
	virtual int writeDevice(const CANMessage& msg) = 0;

	virtual int getFiledescriptor() const = 0;

	virtual int setCanFilter(const std::list<CANFilter>& filterList) = 0;
	virtual int setCanErrorMask( CANErrorMask mask ) = 0;

private:
	std::string device;
	CANErrorMask errorMask;
	std::list<CANFilter> filterList;

	std::mutex mutex_write;
	std::mutex mutex_read;
};

} /* namespace CanSocket */

#endif /* SRC_BASIC_SOCKETCANIMPL_H_ */
