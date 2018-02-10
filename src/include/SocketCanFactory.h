/*
 * CanSocketFactory.h
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#ifndef SRC_SOCKETCANFACTORY_H_
#define SRC_SOCKETCANFACTORY_H_

#include "SocketCan.h"

namespace CanSocket
{

class SocketCanFactory
{
public:
	SocketCanFactory();
	virtual ~SocketCanFactory();

	SocketCan* createSocketCan(const std::string& device);
};

} /* namespace CanSocket */

#endif /* SRC_SOCKETCANFACTORY_H_ */
