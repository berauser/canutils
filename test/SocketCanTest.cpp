/*
 * SocketCanTest.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "SocketCanTest.h"

#include "SocketCanFactory.h"

#include <unistd.h>

#include <stdexcept>

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

	/* invalid argument */
	ASSERT_THROW(factory.createSocketCan(""), std::invalid_argument);

	/* open device */
	CanSocket::SocketCan* socketcan = factory.createSocketCan("vcan0");

	EXPECT_EQ("vcan0", socketcan->getDevice());
	EXPECT_EQ(false, socketcan->isOpen());

	EXPECT_EQ(nullptr, socketcan->getListener());
	EXPECT_EQ(0, socketcan->getFilterList().size());

	EXPECT_EQ(0, socketcan->open());
	EXPECT_EQ(true, socketcan->isOpen());

	EXPECT_EQ(0, socketcan->close());
	EXPECT_EQ(false, socketcan->isOpen());

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

	EXPECT_EQ(0, socketcan->getFilterList().size());


	SocketCan::CANFilter filter1 { 0x123, 0x7FF };
	SocketCan::CANFilter filter2 { 0x123, 0x3FF };
	SocketCan::CANFilter filter3 { 0x007, 0x007 };
	SocketCan::CANFilter filter4 { 0x007, 0x007 };

	ASSERT_THROW( socketcan->addFilter( filter1 ),    std::logic_error ); // device not open
	ASSERT_THROW( socketcan->removeFilter( filter1 ), std::logic_error ); // device not open
	ASSERT_THROW( socketcan->clearFilter(),           std::logic_error ); // device not open

	EXPECT_EQ(0, socketcan->open());
	EXPECT_EQ(true, socketcan->isOpen());

	EXPECT_EQ(0, socketcan->addFilter(filter1)); // 1
	EXPECT_EQ(0, socketcan->addFilter(filter2)); // 2
	EXPECT_EQ(0, socketcan->addFilter(filter3)); // 3
	EXPECT_EQ(0, socketcan->addFilter(filter4)); // 3

	EXPECT_EQ(3, socketcan->getFilterList().size());

	std::list<SocketCan::CANFilter> flist = socketcan->getFilterList();
	std::list<SocketCan::CANFilter>::iterator it;

	/* search all filters */
	it = std::find(flist.begin(), flist.end(), filter1);
	EXPECT_NE(flist.end(), it);

	it = std::find(flist.begin(), flist.end(), filter2);
	EXPECT_NE(flist.end(), it);

	it = std::find(flist.begin(), flist.end(), filter3);
	EXPECT_NE(flist.end(), it);

	it = std::find(flist.begin(), flist.end(), filter4);
	EXPECT_NE(flist.end(), it);

	/* remove one filter */
	EXPECT_EQ(0, socketcan->removeFilter(filter2)); // 2
	EXPECT_EQ(2, socketcan->getFilterList().size());
	it = std::find(flist.begin(), flist.end(), filter2);
	EXPECT_EQ(flist.end(), it);

	/* remove the double filter */
	EXPECT_EQ(0, socketcan->removeFilter(filter3 /*, filter4 */)); // 1
	EXPECT_EQ(1, socketcan->getFilterList().size());
	it = std::find(flist.begin(), flist.end(), filter3);
	EXPECT_EQ(flist.end(), it);
	it = std::find(flist.begin(), flist.end(), filter4);
	EXPECT_EQ(flist.end(), it);

	/* clear all */
	EXPECT_EQ(0, socketcan->clearFilter());
	EXPECT_EQ(0, socketcan->getFilterList().size());

	EXPECT_EQ(0, socketcan->close());
	EXPECT_EQ(false, socketcan->isOpen());

	delete socketcan;
}

} /* namespace Test */
} /* namespace CanSocket */
