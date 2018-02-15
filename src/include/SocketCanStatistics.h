/*
 * SocketCanStatistics.h
 *
 *  Created on: 10.02.2018
 *      Author: rauser
 */

#ifndef SRC_SOCKETCANSTATISTICS_H_
#define SRC_SOCKETCANSTATISTICS_H_

#include <string>

#include "CANStatistics.h"

namespace CanSocket
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
	
	virtual int read( CANStatistics* stats ) = 0;
	virtual int reset() = 0;
};

} /* namespace CanSocket */

#endif /* SRC_SOCKETCANSTATISTICS_H_ */
