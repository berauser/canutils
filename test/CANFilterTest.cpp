/*
 * CANFilterTest.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "CANFilterTest.h"

#include "SocketCanFactory.h"
#include "MockListener.h"

namespace CanSocket
{
namespace Test
{

void CANFilterTest::SetUp()
{
}

void CANFilterTest::TearDown()
{
}

TEST_F( CANFilterTest, compare )
{
	SocketCan::CANFilter f1 { 0x123, 0x7FF, false };
	SocketCan::CANFilter f2 { 0x123, 0x000, false };
	SocketCan::CANFilter f3 { 0x7FF, 0x7FF, false };
	SocketCan::CANFilter f4 { 0x123, 0x7FF, true  };
	SocketCan::CANFilter f5 { 0x123, 0x7FF, false };

	EXPECT_FALSE(  f1 == f2 );
	EXPECT_FALSE(  f1 == f3 );
	EXPECT_FALSE(  f1 == f4 );
	EXPECT_TRUE (  f1 == f5 );

	EXPECT_TRUE (  f1 != f2 );
	EXPECT_TRUE (  f1 != f3 );
	EXPECT_TRUE (  f1 != f4 );
	EXPECT_FALSE(  f1 != f5 );
}

} /* namespace Test */
} /* namespace CanSocket */
