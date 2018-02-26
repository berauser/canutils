/*
 * CANBufferQueueTest.cpp
 *
 *  Created on: 26.02.2018
 *      Author: rauser
 */

#include "CANBufferQueueTest.h"

#include "SocketCanFactory.h"

namespace CanSocket
{
namespace Test
{

void CANBufferQueueTest::SetUp()
{  
}

void CANBufferQueueTest::TearDown()
{
}

TEST_F( CANBufferQueueTest, initialization )
{
	SocketCanFactory factory;
	CanBufferPtr buffer1 = factory.createCanBuffer("Queue");
	
	EXPECT_EQ   ( DEFAULT_BUFFER_SIZE, buffer1->size()           ); 
	EXPECT_EQ   ( "Queue",             buffer1->implementation() );
	EXPECT_TRUE ( buffer1->isEmpty() );
	EXPECT_FALSE( buffer1->isFull()  );
	EXPECT_FALSE( buffer1->hasNext() );
	
	CanBufferPtr buffer2 = factory.createCanBuffer("Queue", 42);
	
	EXPECT_EQ   ( 42,      buffer2->size()           ); 
	EXPECT_EQ   ( "Queue", buffer2->implementation() );
	EXPECT_TRUE ( buffer2->isEmpty() );
	EXPECT_FALSE( buffer2->isFull()  );
	EXPECT_FALSE( buffer2->hasNext() );
}

TEST_F( CANBufferQueueTest, isFull )
{
	SocketCanFactory factory;
	CanBufferPtr buffer = factory.createCanBuffer("Queue", 16);
	
	/* buffer should be not full */
	EXPECT_FALSE( buffer->isFull() );
	
	/* fill buffer */
	for( int i = 0; i < 16; ++i )
	{
		CANMessage message( i, CANMessage::CANFrameType::Standard, 1, i );
		buffer->write( message );
	}
	
	/* buffer is now full */
	EXPECT_TRUE ( buffer->isFull() );
	
	/* read a single message -> buffer is not full */
	CANMessage msg;
	buffer->read( msg );
	
	EXPECT_FALSE( buffer->isFull() );
}


TEST_F( CANBufferQueueTest, isEmpty )
{
	SocketCanFactory factory;
	CanBufferPtr buffer = factory.createCanBuffer("Queue", 16);
	
	/* buffer should be empty */
	EXPECT_TRUE( buffer->isEmpty() );
	
	/* add a single message */
	CANMessage message( 0x123, CANMessage::CANFrameType::Standard, 1, 0x01 );
	buffer->write( message );

	/* buffer is not empty */
	EXPECT_FALSE( buffer->isEmpty() );
	
	/* read the last message -> buffer is empty */
	CANMessage msg;
	buffer->read( msg );
	
	EXPECT_TRUE( buffer->isEmpty() );
}

TEST_F( CANBufferQueueTest, resize )
{
	SocketCanFactory factory;
	CanBufferPtr buffer = factory.createCanBuffer("Queue", 2);
	
	/* add a single message */
	CANMessage message( 0x123, CANMessage::CANFrameType::Standard, 1, 0x01 );
	buffer->write( message );
	buffer->write( message );
	
	/* buffer should be full */
	EXPECT_TRUE( buffer->isFull() );
	
	/* double buffer size */
	EXPECT_EQ(0, buffer->resize( 2 * buffer->size() ) );  
	
	/* buffer is not full */
	EXPECT_FALSE( buffer->isFull() );
	
	/* add another two messages */
	buffer->write( message );
	buffer->write( message );
	
	/* buffer should be full */
	EXPECT_TRUE( buffer->isFull() );
}

TEST_F( CANBufferQueueTest, read_write_single )
{
	EXPECT_TRUE(false);
}

TEST_F( CANBufferQueueTest, read_write_multiple )
{
	EXPECT_TRUE(false);
}

TEST_F( CANBufferQueueTest, read_write_async )
{
	EXPECT_TRUE(false);
}

} /* namespace Test */
} /* namespace CanSocket */
