/*
 * MockListener.h
 *
 *  Created on: 25.09.2017
 *      Author: rauser
 */

#ifndef TEST_MOCKLISTENER_H_
#define TEST_MOCKLISTENER_H_

#include "SocketCanListener.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace CanSocket
{
namespace Test
{

class MockListener: public SocketCanListener
{
public:
	MOCK_METHOD1(recvMessage, void(const CANMessage&));
};

} /* namespace Test */
} /* namespace CanSocket */

#endif /* TEST_MOCKLISTENER_H_ */
