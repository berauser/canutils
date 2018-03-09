/*
 * SocketCanStatistics.h
 *
 *  Created on: 10.02.2018
 *      Author: rauser
 */

#ifndef SRC_INCLUDE_SOCKETCANSTATISTICS_H_
#define SRC_INCLUDE_SOCKETCANSTATISTICS_H_

#include "canutils/CANStatistics.h"

#include <string>
#include <memory>

namespace CanUtils
{

/*!
 * SocketCanStatistics querys all CAN statistics
 */
class SocketCanStatistics
{
public:
	SocketCanStatistics() = delete;
	/*!
	 * Constructor for SocketCanStatistics
	 */
	explicit SocketCanStatistics(const std::string& device_arg)
	{
		(void)device_arg;
	}
	/*!
	 * Destructor for SocketCanStatistics
	 */
	virtual ~SocketCanStatistics() noexcept(false)
	{
	}
	
	/*!
	 * Return the CAN device name
	 * @return CAN device name
	 */
	virtual const std::string& getDevice() const = 0;
	
	/*!
	 * Read the CAN device statistics
	 * @return Pointer to the CAN device statistics
	 */
	virtual CANStatisticsPtr read() = 0;
	/*!
	 * Reset the CAN device statistics
	 * @note Not implemented
	 * @return always -1
	 */
	virtual int reset() = 0;
};
typedef std::shared_ptr<SocketCanStatistics> SocketCanStatisticsPtr;

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_SOCKETCANSTATISTICS_H_ */
