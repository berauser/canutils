/*
 * SocketCanTest.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "SocketCanTest.h"

#include "SocketCanFactory.h"

#include <unistd.h>

namespace CanSocket
{
namespace Test
{
void SocketCanTest::SetUp()
{
}

void SocketCanTest::TearDown()
{
}

TEST_F( SocketCanTest, process )
{
	CanSocket::SocketCanFactory factory;
	CanSocket::SocketCan* socketcan = factory.createSocketCan( "vcan0" );

	EXPECT_EQ( "vcan0", socketcan->getDevice() );
	EXPECT_EQ( false,   socketcan->isOpen() );

	EXPECT_EQ( 0, socketcan->getListeners().size() );
	EXPECT_EQ( 0, socketcan->getFilterList().size() );

	EXPECT_EQ( 0, socketcan->open() );

	sleep(1);

	EXPECT_EQ( 0, socketcan->close() );

	delete socketcan;
}


} /* namespace Test */
} /* namespace CanSocket */
