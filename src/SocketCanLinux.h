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
	explicit SocketCanLinux(const std::string& device);
	virtual ~SocketCanLinux();

	virtual bool isOpen();

	virtual int enableLoopback( bool enable ) override;
	virtual bool loopbackEnabled()  const override;

	virtual int receiveOwnMessage( bool enable ) override;
	virtual bool receiveOwnMessageEnabled() const override;

protected:
	virtual int openDevice() override;
	virtual int closeDevice() override;
	virtual int readDevice(CANMessage* message) override;
	virtual int writeDevice(const CANMessage& msg) override;

	virtual int getFiledescriptor() const override;



	virtual int setFilter(const std::list<CANFilter>& filterList) override;

private:
	int socketfd;
};

} /* namespace CanSocket */

#endif /* SRC_SOCKETCANLINUX_H_ */
