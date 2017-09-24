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

class MockListener: public SocketCanListener
{
public:
	MOCK_METHOD1(recvMessage, void(const CANMessage&));
};

void SocketCanTest::SetUp()
{
}

void SocketCanTest::TearDown()
{
}

TEST_F( SocketCanTest, init )
{
	CanSocket::SocketCanFactory factory;
	CanSocket::SocketCan* socketcan = factory.createSocketCan("vcan0");

	EXPECT_EQ("vcan0", socketcan->getDevice());
	EXPECT_EQ(false, socketcan->isOpen());

	EXPECT_EQ(nullptr, socketcan->getListener());
	EXPECT_EQ(0, socketcan->getFilterList().size());

//	EXPECT_EQ(0, socketcan->open());
//	EXPECT_EQ(true, socketcan->isOpen());
//
//	sleep(1);
//
//	EXPECT_EQ(0, socketcan->close());
//	EXPECT_EQ(false, socketcan->isOpen());

	delete socketcan;
}

TEST_F( SocketCanTest, registerListener )
{
	CanSocket::SocketCanFactory factory;
	CanSocket::SocketCan* socketcan = factory.createSocketCan("vcan0");

	EXPECT_EQ(nullptr, socketcan->getListener());

	MockListener listener;
	EXPECT_EQ(0, socketcan->setListener(&listener));

	EXPECT_EQ(&listener, socketcan->getListener());

	delete socketcan;
}

TEST_F( SocketCanTest, filter )
{
	CanSocket::SocketCanFactory factory;
	CanSocket::SocketCan* socketcan = factory.createSocketCan("vcan0");

	EXPECT_EQ( 0, socketcan->getFilterList().size() );

	SocketCan::CANFilter filter { 0x123, 0x7FF };
	EXPECT_EQ( 0, socketcan->addFilter( filter ) );

	std::list<SocketCan::CANFilter> flist = socketcan->getFilterList();
	std::list<SocketCan::CANFilter>::iterator it = std::find( flist.begin(), flist.end(), filter );
	EXPECT_EQ( flist.end(), it );

	delete socketcan;
}

} /* namespace Test */
} /* namespace CanSocket */
