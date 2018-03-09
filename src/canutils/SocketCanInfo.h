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

/*!
 * SocketCanInfo querys all CAN device information
 */
class SocketCanInfo
{
public:
	SocketCanInfo() = delete;
	/*!
	 * Constructor for SocketCanInfo
	 */
	explicit SocketCanInfo(const std::string& device_arg)
	{
		(void)device_arg;
	}
	/*!
	 * Destructor for SocketCanInfo
	 */
	virtual ~SocketCanInfo() noexcept(false)
	{
	}
	
	/*!
	 * Return the CAN device name
	 * @return CAN device name
	 */
	virtual const std::string& getDevice() const = 0;
	
	/*!
	 * Read the CAN device information
	 * @return Pointer to the CAN device information
	 */
	virtual CANDeviceInfoPtr read() = 0;
	
	/*!
	 * Convert the CAN state to string
	 * @param state CAN state to convert to string
	 * @return The CAN state as string
	 */
	static std::string toString(const CanState& state);
	/*!
	 * Convert the Device flags to string
	 * @param flag Device flag to convert to string
	 * @return The Device flag as string
	 */
	static std::string toString(const DeviceFlags& flag);
	/*!
	 * Convert the CAN control mode to string
	 * @param mode CAN control mode to convert to string
	 * @return The CAN control mode as string
	 */
	static std::string toString(const ControlMode& mode);
	/*!
	 * Convert the CAN device state to string
	 * @param state CAN device state to convert to string
	 * @return The CAN device state as string
	 */
	static std::string toString(const DeviceState& state);
};
typedef std::shared_ptr<SocketCanInfo> SocketCanInfoPtr;

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_SOCKETCANSTATISTICS_H_ */
