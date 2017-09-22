/*
 * SocketCanListener.h
 *
 *  Created on: 22.09.2017
 *      Author: rauser
 */

#ifndef SRC_SOCKETCANLISTENER_H_
#define SRC_SOCKETCANLISTENER_H_

#include "CANMessage.h"

namespace SocketCan
{

class SocketCanListener
{
		virtual void recvMessage( const CANMessage& msg ) = 0;
		virtual ~SocketCanListener() {}
};

} /* namespace SocketCan */

#endif /* SRC_SOCKETCANLISTENER_H_ */
