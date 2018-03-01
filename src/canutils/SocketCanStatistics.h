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

class SocketCanStatistics
{
public:
	SocketCanStatistics() = delete;
	explicit SocketCanStatistics(const std::string& device_arg)
	{
		(void)device_arg;
	}
	virtual ~SocketCanStatistics()
	{
	}
	
	virtual const std::string& getDevice() const = 0;
	
	virtual CANStatisticsPtr read() = 0;
	virtual int reset() = 0;
};
typedef std::shared_ptr<SocketCanStatistics> SocketCanStatisticsPtr;

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_SOCKETCANSTATISTICS_H_ */
