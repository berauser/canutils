/*
 * SocketCan.h
 *
 *  Created on: 22.09.2017
 *      Author: rauser
 */

#ifndef SRC_SOCKETCANLINUX_H_
#define SRC_SOCKETCANLINUX_H_

#include "SocketCan.h"

#include <string>
#include <thread>

namespace SocketCan {

class SocketCanLinux final : public SocketCan
{

public:
	SocketCanLinux() = delete;
	SocketCanLinux( const std::string& device );
	virtual ~SocketCanLinux();

	bool open() override;
	bool close() override;

	int write( const CANMessage& msg ) override;
	int registerListener( SocketCanListener& listener ) override;

	SocketCanLinux& operator=( const SocketCanLinux& src );
	SocketCanLinux& operator=( SocketCanLinux&& src );

	const int getFiledescriptor() const override;
	const std::string& getDevice() const override;

private:
	int socketfd;

	std::thread recvThread;
};

} /* namespace SocketCan */

#endif /* SRC_SOCKETCANLINUX_H_ */
