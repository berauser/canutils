/*
 * CanSocketFactory.h
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#ifndef SRC_SOCKETCANFACTORY_H_
#define SRC_SOCKETCANFACTORY_H_

#include "CanBuffer.h"
#include "SocketCan.h"
#include "SocketCanInfo.h"
#include "SocketCanStatistics.h"

namespace CanSocket
{

class SocketCanFactory
{
public:
	SocketCanFactory();
	virtual ~SocketCanFactory();

    CanBufferPtr createCanBuffer(const std::string& type = "default", const unsigned int size = 16 );
	SocketCanPtr createSocketCan(const std::string& device);
	SocketCanInfoPtr createSocketCanInfo( const std::string& device);
	SocketCanStatisticsPtr createSocketCanStatistics(const std::string& device);
};

} /* namespace CanSocket */

#endif /* SRC_SOCKETCANFACTORY_H_ */
