/*
 * CANFilter.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "CANFilter.h"

#include "SocketCanFactory.h"

#include <unistd.h>

namespace CanSocket
{
namespace Test
{

class MockListener: public SocketCanListener
{
public:
	MOCK_METHOD1(recvMessage, void(const CANMessage&));
};

void CANFilter::SetUp()
{
}

void CANFilter::TearDown()
{
}

TEST_F( CANFilter, compare )
{
	SocketCan::CANFilter f1 { 0x123, 0x7FF };
	SocketCan::CANFilter f2 { 0x123, 0x000 };
	SocketCan::CANFilter f3 { 0x7FF, 0x7FF };
	SocketCan::CANFilter f4 { 0x123, 0x7FF };

	EXPECT_FALSE(  f1 == f2 );
	EXPECT_FALSE(  f1 == f3 );
	EXPECT_TRUE (  f1 == f4 );

	EXPECT_TRUE (  f1 != f2 );
	EXPECT_TRUE (  f1 != f3 );
	EXPECT_FALSE(  f1 != f4 );
}

} /* namespace Test */
} /* namespace CanSocket */
