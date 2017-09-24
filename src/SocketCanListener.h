/*
 * SocketCanListener.h
 *
 *  Created on: 22.09.2017
 *      Author: rauser
 */

#ifndef SRC_SOCKETCANLISTENER_H_
#define SRC_SOCKETCANLISTENER_H_

#include "CANMessage.h"

namespace CanSocket
{

class SocketCanListener
{
public:
	SocketCanListener()
	{
	}
	virtual ~SocketCanListener()
	{
	}

	virtual void recvMessage(const CANMessage& msg) = 0;

	bool operator==(const SocketCanListener& l1) const
	{
		return (this == &l1);
	}
};

} /* namespace CanSocket */

#endif /* SRC_SOCKETCANLISTENER_H_ */
