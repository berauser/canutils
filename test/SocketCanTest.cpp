/*
 * SocketCanTest.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "SocketCanTest.h"

#include "SocketCanFactory.h"
#include "MockListener.h"

#include <stdexcept>

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

TEST_F( SocketCanTest, init )
{
	SocketCanFactory factory;

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

	ASSERT_THROW( socketcan->open(), std::logic_error );

	EXPECT_EQ(0, socketcan->close());
	EXPECT_EQ(false, socketcan->isOpen());

	EXPECT_EQ(0, socketcan->close());

	delete socketcan;
}

TEST_F( SocketCanTest, registerListener )
{
	SocketCanFactory factory;
	SocketCan* socketcan = factory.createSocketCan("vcan0");

	EXPECT_EQ(nullptr, socketcan->getListener());

	MockListener listener;
	EXPECT_EQ(0, socketcan->setListener(&listener));

	EXPECT_EQ(&listener, socketcan->getListener());

	delete socketcan;
}

TEST_F( SocketCanTest, filter )
{
	SocketCanFactory factory;
	SocketCan* socketcan = factory.createSocketCan("vcan0");

	EXPECT_EQ(0, socketcan->getFilterList().size());

	CANFilter filter1 ( 0x123, 0x7FF );
	CANFilter filter2 ( 0x123, 0x3FF );
	CANFilter filter3 ( 0x007, 0x007 );
	CANFilter filter4 ( 0x007, 0x007 );

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

	std::list<CANFilter> flist = socketcan->getFilterList();
	std::list<CANFilter>::iterator it;

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

TEST_F( SocketCanTest, loopback_basic )
{
	SocketCanFactory factory;
	SocketCan* socketcan = factory.createSocketCan("vcan0");

	/* closed socket shoulkd throw an error */
	ASSERT_THROW( socketcan->enableLoopback( true ),  std::logic_error );
	ASSERT_THROW( socketcan->enableLoopback( false ), std::logic_error );
	ASSERT_THROW( socketcan->loopbackEnabled(),       std::logic_error );

	EXPECT_EQ(0, socketcan->open());

	EXPECT_EQ   ( 0, socketcan->enableLoopback( true ) );
	EXPECT_TRUE ( socketcan->loopbackEnabled() );

	EXPECT_EQ   ( 0, socketcan->enableLoopback( false ) );
	EXPECT_FALSE( socketcan->loopbackEnabled() );

	EXPECT_EQ(0, socketcan->close());

	delete socketcan;
}

TEST_F( SocketCanTest, receive_own_basic )
{
	SocketCanFactory factory;
	SocketCan* socketcan = factory.createSocketCan("vcan0");

	/* closed socket shoulkd throw an error */
	ASSERT_THROW( socketcan->receiveOwnMessage( true ),  std::logic_error );
	ASSERT_THROW( socketcan->receiveOwnMessage( false ), std::logic_error );
	ASSERT_THROW( socketcan->receiveOwnMessageEnabled(), std::logic_error );

	EXPECT_EQ(0, socketcan->open());

	EXPECT_EQ   ( 0, socketcan->receiveOwnMessage( true ) );
	EXPECT_TRUE ( socketcan->receiveOwnMessageEnabled() );

	EXPECT_EQ   ( 0, socketcan->receiveOwnMessage( false ) );
	EXPECT_FALSE( socketcan->receiveOwnMessageEnabled() );

	EXPECT_EQ(0, socketcan->close());

	delete socketcan;
}

TEST_F( SocketCanTest, read_write_basic )
{
	SocketCanFactory factory;
	SocketCan* socketcan_tx = factory.createSocketCan("vcan0");
	SocketCan* socketcan_rx = factory.createSocketCan("vcan0");

	/* message to send */
	CANMessage message( 0x123, false, 8, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 );

	/* setup listener */
	MockListener listener;
	EXPECT_EQ( 0, socketcan_rx->setListener( &listener ) );

	/* device not open, so we should not receive a message */
	EXPECT_CALL( listener, recvMessage(::testing::_) ).Times(0);
	ASSERT_THROW( socketcan_tx->write( message ), std::logic_error );

	/* wait for receiving */
	sleep(1);

	/* open the device and try send and receive */
	EXPECT_EQ( 0, socketcan_tx->open());
	EXPECT_EQ( 0, socketcan_rx->open());

	/* we send and receive one message */
	EXPECT_CALL( listener, recvMessage(::testing::_) ).Times(1);
	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message ));

	/* wait for receiving */
	sleep(1);

	/* cleanup */
	EXPECT_EQ(0, socketcan_rx->close());
	EXPECT_EQ(0, socketcan_tx->close());

	delete socketcan_rx;
	delete socketcan_tx;
}

TEST_F( SocketCanTest, read_write_extended )
{
	SocketCanFactory factory;
	SocketCan* socketcan_tx = factory.createSocketCan("vcan0");
	SocketCan* socketcan_rx = factory.createSocketCan("vcan0");

	/* message to send */
	CANMessage message( 0x123, true, 8, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 );

	/* setup listener */
	MockListener listener;
	EXPECT_EQ( 0, socketcan_rx->setListener( &listener ) );

	/* device not open, so we should not receive a message */
	EXPECT_CALL( listener, recvMessage(::testing::_) ).Times(0);
	ASSERT_THROW( socketcan_tx->write( message ), std::logic_error );

	/* wait for receiving */
	sleep(1);

	/* open the device and try send and receive */
	EXPECT_EQ( 0, socketcan_tx->open());
	EXPECT_EQ( 0, socketcan_rx->open());

	/* we send and receive one message */
	EXPECT_CALL( listener, recvMessage(message) ).Times(1);
	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message ));

	/* wait for receiving */
	sleep(1);

	/* cleanup */
	EXPECT_EQ(0, socketcan_rx->close());
	EXPECT_EQ(0, socketcan_tx->close());

	delete socketcan_rx;
	delete socketcan_tx;
}

TEST_F( SocketCanTest, add_remove_filter )
{
	/* TODO add and remove filter */
	EXPECT_TRUE( false );
}

TEST_F( SocketCanTest, receive_filter_not_inverted )
{
	SocketCanFactory factory;
	SocketCan* socketcan_tx = factory.createSocketCan("vcan0");
	SocketCan* socketcan_rx = factory.createSocketCan("vcan0");

	/* message to send */
	CANMessage message1( 0x111, false, 8, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 );
	CANMessage message2( 0x222, false, 8, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22 );
	CANMessage message3( 0x333, false, 8, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 );
	CANMessage message4( 0x440, false, 8, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44 );
	CANMessage message5( 0x441, false, 8, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55 );

	/* setup filter */
	CANFilter filter1( 0x111, 0x7FF ); /* recv 0x111 */
	CANFilter filter2( 0x440, 0x7F0 ); /* recv 0x440 and 0x441 */

	/* setup listener */
	MockListener listener;
	EXPECT_EQ( 0, socketcan_rx->setListener( &listener ) );

	/* open the device and try send and receive */
	EXPECT_EQ( 0, socketcan_tx->open());
	EXPECT_EQ( 0, socketcan_rx->open());

	EXPECT_EQ( 0, socketcan_rx->addFilter( filter1 ) );
	EXPECT_EQ( 0, socketcan_rx->addFilter( filter2 ) );

	/* write frames */
	/* receive only three frames 0x111, 0x440, 0x441 */
	// TODO check with matchers
	EXPECT_CALL( listener, recvMessage(::testing::AnyOf( message1, message4, message5))).Times(3);
	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message1 ));
	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message2 ));
	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message3 ));
	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message4 ));
	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message5 ));

	/* wait for receiving */
	sleep(1);

	/* cleanup */
	EXPECT_EQ(0, socketcan_rx->close());
	EXPECT_EQ(0, socketcan_tx->close());

	delete socketcan_rx;
	delete socketcan_tx;
}

TEST_F( SocketCanTest, receive_filter_inverted )
{
	SocketCanFactory factory;
	SocketCan* socketcan_tx = factory.createSocketCan("vcan0");
	SocketCan* socketcan_rx = factory.createSocketCan("vcan0");

	/* message to send */
	CANMessage message1( 0x111, false, 8, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 );
	CANMessage message2( 0x222, false, 8, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22 );
	CANMessage message3( 0x333, false, 8, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 );
	CANMessage message4( 0x440, false, 8, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44 );
	CANMessage message5( 0x441, false, 8, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55 );

	/* setup filter */
	CANFilter filter1( 0x440, 0x7F0 );
	filter1.invert(); /* recv all except 0x440 and 0x441 */

	/* setup listener */
	MockListener listener;
	EXPECT_EQ( 0, socketcan_rx->setListener( &listener ) );

	/* open the device and try send and receive */
	EXPECT_EQ( 0, socketcan_tx->open());
	EXPECT_EQ( 0, socketcan_rx->open());

	EXPECT_EQ( 0, socketcan_rx->addFilter( filter1 ) );

	/* write frames */
	/* receive only three frames 0x111, 0x222, 0x333 */
	// TODO check with matchers
	EXPECT_CALL( listener, recvMessage(::testing::AnyOf( message1, message2, message3))).Times(3);

	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message1 ));
	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message2 ));
	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message3 ));
	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message4 ));
	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message5 ));

	/* wait for receiving */
	sleep(1);

	/* cleanup */
	EXPECT_EQ(0, socketcan_rx->close());
	EXPECT_EQ(0, socketcan_tx->close());

	delete socketcan_rx;
	delete socketcan_tx;
}

TEST_F( SocketCanTest, reset_filter )
{
	SocketCanFactory factory;
	SocketCan* socketcan_tx = factory.createSocketCan("vcan0");
	SocketCan* socketcan_rx = factory.createSocketCan("vcan0");

	/* message to send */
	CANMessage message1( 0x111, false, 8, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 );
	CANMessage message2( 0x222, false, 8, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22 );

	/* setup filter */
	CANFilter filter1( 0x333, 0x7FF );

	/* setup listener */
	MockListener listener;
	EXPECT_EQ( 0, socketcan_rx->setListener( &listener ) );

	/* open the device and try send and receive */
	EXPECT_EQ( 0, socketcan_tx->open());
	EXPECT_EQ( 0, socketcan_rx->open());

	EXPECT_EQ( 0, socketcan_rx->addFilter( filter1 ) );

	/* receive nothing */
	EXPECT_CALL( listener, recvMessage(::testing::_)).Times(0);
	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message1 ));
	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message2 ));

	/* wait for receiving */
	sleep(1);

	/* clear filter */
	EXPECT_EQ( 0, socketcan_rx->clearFilter() );

	/* receive all frames */
	EXPECT_CALL( listener, recvMessage(::testing::_)).Times(2);
	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message1 ));
	EXPECT_EQ( sizeof( CANMessage ), socketcan_tx->write( message2 ));

	/* wait for receiving */
	sleep(1);

	/* cleanup */
	EXPECT_EQ(0, socketcan_rx->close());
	EXPECT_EQ(0, socketcan_tx->close());

	delete socketcan_rx;
	delete socketcan_tx;
}

} /* namespace Test */
} /* namespace CanSocket */
