/*
 * SocketCanInfo.h
 *
 *  Created on: 17.02.2018
 *      Author: rauser
 */

#ifndef SRC_SOCKETCANINFO_H_
#define SRC_SOCKETCANINFO_H_

#include "CANDeviceInfo.h"

#include <string>

namespace CanSocket
{

class SocketCanInfo
{
public:
	SocketCanInfo() = delete;
	explicit SocketCanInfo(const std::string& device_arg)
	{
		(void)device_arg;
	}
	virtual ~SocketCanInfo()
	{
	}
	
	virtual const std::string& getDevice() const = 0;
	
	virtual int read(CANDeviceInfo* info) = 0;
};

} /* namespace CanSocket */

#endif /* SRC_SOCKETCANSTATISTICS_H_ */