/*
 * SocketCanInfo.h
 *
 *  Created on: 17.02.2018
 *      Author: rauser
 */

#ifndef SRC_INCLUDE_SOCKETCANINFO_H_
#define SRC_INCLUDE_SOCKETCANINFO_H_

#include "canutils/CANDeviceInfo.h"

#include <string>
#include <memory>

namespace CanUtils
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
typedef std::shared_ptr<SocketCanInfo> SocketCanInfoPtr;

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_SOCKETCANSTATISTICS_H_ */
