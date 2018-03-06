/*
 * CanUtilsFactory.h
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#ifndef SRC_INCLUDE_SOCKETCANFACTORY_H_
#define SRC_INCLUDE_SOCKETCANFACTORY_H_

#include "canutils/CanBuffer.h"
#include "canutils/SocketCan.h"
#include "canutils/SocketCanInfo.h"
#include "canutils/SocketCanWorker.h"
#include "canutils/SocketCanStatistics.h"

namespace CanUtils
{
const unsigned int DEFAULT_BUFFER_SIZE = 16;
const std::string  DEFAULT_BUFFER_TYPE = "default";

class SocketCanFactory
{    
public:
	SocketCanFactory();
	virtual ~SocketCanFactory() noexcept(false);
	
	static std::string version();
	
	CanBufferPtr createCanBuffer(const std::string& type = DEFAULT_BUFFER_TYPE, const unsigned int size = DEFAULT_BUFFER_SIZE );
	SocketCanPtr createSocketCan(const std::string& device);
    
	SocketCanWorkerPtr createSocketCanWorker();
	SocketCanInfoPtr createSocketCanInfo( const std::string& device);
	SocketCanStatisticsPtr createSocketCanStatistics(const std::string& device);
};

} /* namespace CanUtils */

#endif /* SRC_INCLUDE_SOCKETCANFACTORY_H_ */
