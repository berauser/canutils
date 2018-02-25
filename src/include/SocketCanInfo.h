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
	
	virtual CANDeviceInfoPtr read() = 0;
	
	static std::string toString(const CanState& state);
	static std::string toString(const DeviceFlags& flag);
	static std::string toString(const ControlMode& mode);
	static std::string toString(const DeviceState& state);
};

} /* namespace CanSocket */

#endif /* SRC_SOCKETCANSTATISTICS_H_ */