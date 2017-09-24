/*
 * SocketCan.h
 *
 *  Created on: 22.09.2017
 *      Author: rauser
 */

#ifndef SRC_SOCKETCANLINUX_H_
#define SRC_SOCKETCANLINUX_H_

#include "SocketCanImpl.h"

#include <string>
#include <thread>

namespace CanSocket
{

class SocketCanLinux final : public SocketCanImpl
{

public:
	SocketCanLinux() = delete;
	SocketCanLinux(const std::string& device);
	virtual ~SocketCanLinux();

	virtual bool isOpen();

	int write(const CANMessage& msg) override;

protected:
	virtual int openDevice() override;
	virtual int closeDevice() override;

	virtual int getFiledescriptor() const override;

	virtual int read(CANMessage* message) override;

	virtual int setFilter(const std::list<CANFilter>& filterList) override;

private:
	int socketfd;
};

} /* namespace CanSocket */

#endif /* SRC_SOCKETCANLINUX_H_ */
