/*
 * SocketCanImpl.h
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#ifndef SRC_SOCKETCANIMPL_H_
#define SRC_SOCKETCANIMPL_H_

#include "SocketCan.h"

#include <thread>

namespace CanSocket
{

class SocketCanImpl: public SocketCan
{
public:
	SocketCanImpl() = delete;
	SocketCanImpl(const std::string& device_arg);
	virtual ~SocketCanImpl();

	virtual int open() override final;
	virtual int close() override final;
	virtual bool isOpen() = 0;

	virtual int write(const CANMessage& msg) = 0;

	virtual int setListener(SocketCanListener* listener);
	virtual SocketCanListener* getListener();

	virtual const std::string& getDevice() const override final;

	virtual int addFilter(const SocketCan::CANFilter& filter) override final;
	virtual int removeFilter(const SocketCan::CANFilter& filter) override final;
	virtual int clearFilter() override final;
	virtual std::list<SocketCan::CANFilter> getFilterList() override final;


protected:
	virtual int openDevice() = 0;
	virtual int closeDevice() = 0;

	virtual int getFiledescriptor() const = 0;

	virtual int read(CANMessage* message) = 0;

	virtual int setFilter(const std::list<CANFilter>& filterList) = 0;

private:
	virtual void recvLoop() final;

protected:
	std::string device;
	SocketCanListener* listener;
	std::list<SocketCan::CANFilter> filterList;

	std::thread recvThread;
};

} /* namespace CanSocket */

#endif /* SRC_SOCKETCANIMPL_H_ */
