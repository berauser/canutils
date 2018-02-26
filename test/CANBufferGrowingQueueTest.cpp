/*
 * CANBufferGrowingQueueTest.cpp
 *
 *  Created on: 26.02.2018
 *      Author: rauser
 */

#include "CANBufferGrowingQueueTest.h"

#include "SocketCanFactory.h"

namespace CanSocket
{
namespace Test
{

void CANBufferGrowingQueueTest::SetUp()
{  
}

void CANBufferGrowingQueueTest::TearDown()
{
}

TEST_F( CANBufferGrowingQueueTest, initialization )
{
    /* the GrowingQueue returns the current size, so we test for size 0 */
	SocketCanFactory factory;
	CanBufferPtr buffer1 = factory.createCanBuffer("GrowingQueue");
	    
	EXPECT_EQ   ( 0,              buffer1->size()           ); 
	EXPECT_EQ   ( "GrowingQueue", buffer1->implementation() );
	EXPECT_TRUE ( buffer1->isEmpty() );
	EXPECT_FALSE( buffer1->isFull()  );
	EXPECT_FALSE( buffer1->hasNext() );
	
	CanBufferPtr buffer2 = factory.createCanBuffer("GrowingQueue", 42);
	
	EXPECT_EQ   ( 0,              buffer2->size()           ); 
	EXPECT_EQ   ( "GrowingQueue", buffer2->implementation() );
	EXPECT_TRUE ( buffer2->isEmpty() );
	EXPECT_FALSE( buffer2->isFull()  );
	EXPECT_FALSE( buffer2->hasNext() );
}

TEST_F( CANBufferGrowingQueueTest, isFull )
{
    /* GrowingQueue is never full */ 
    
	SocketCanFactory factory;
	CanBufferPtr buffer = factory.createCanBuffer("GrowingQueue", 16);
	
	/* buffer should be not full */
	EXPECT_FALSE( buffer->isFull() );
	
	/* fill buffer */
	for( int i = 0; i < 16; ++i )
	{
		CANMessage message( i, CANMessage::CANFrameType::Standard, 1, i );
		EXPECT_EQ( 0, buffer->write( message ) );
	}
	
	/* buffer is now full */
	EXPECT_FALSE ( buffer->isFull() );
	
	/* read a single message -> buffer is not full */
	CANMessage msg;
	EXPECT_EQ( 0, buffer->read( msg ) );
	
	EXPECT_FALSE( buffer->isFull() );
}


TEST_F( CANBufferGrowingQueueTest, isEmpty )
{
	SocketCanFactory factory;
	CanBufferPtr buffer = factory.createCanBuffer("GrowingQueue", 16);
	
	/* buffer should be empty */
	EXPECT_TRUE( buffer->isEmpty() );
	
	/* add a single message */
	CANMessage message( 0x123, CANMessage::CANFrameType::Standard, 1, 0x01 );
	EXPECT_EQ( 0, buffer->write( message ) );

	/* buffer is not empty */
	EXPECT_FALSE( buffer->isEmpty() );
	
	/* read the last message -> buffer is empty */
	CANMessage msg;
	EXPECT_EQ( 0, buffer->read( msg ) );
	
	EXPECT_TRUE( buffer->isEmpty() );
}

TEST_F( CANBufferGrowingQueueTest, resize )
{
    /* We cannot resize the GrowingQueue */
	SocketCanFactory factory;
	CanBufferPtr buffer = factory.createCanBuffer("GrowingQueue", 2);
	
	/* add a single message */
	CANMessage message( 0x123, CANMessage::CANFrameType::Standard, 1, 0x01 );
	EXPECT_EQ( 0, buffer->write( message ) );
	EXPECT_EQ( 0, buffer->write( message ) );
	
	/* buffer should be full */
	EXPECT_FALSE( buffer->isFull() );
	
	/* double buffer size */
	EXPECT_EQ( -1, buffer->resize( 2 * buffer->size() ) );  
	
	/* buffer is not full */
	EXPECT_FALSE( buffer->isFull() );
	
	/* add another two messages */
	EXPECT_EQ( 0, buffer->write( message ) );
	EXPECT_EQ( 0, buffer->write( message ) );
	
	/* buffer should be full */
	EXPECT_FALSE( buffer->isFull() );
}

TEST_F( CANBufferGrowingQueueTest, read_write_single )
{
    SocketCanFactory factory;
    CanBufferPtr buffer = factory.createCanBuffer("GrowingQueue");
    
    CANMessage message1( 0x001, CANMessage::CANFrameType::Standard, 1, 0x01 );
    CANMessage message2( 0x002, CANMessage::CANFrameType::Standard, 1, 0x02 );
    CANMessage message3( 0x003, CANMessage::CANFrameType::Standard, 1, 0x03 );
    
    /* write some test messages */
    EXPECT_EQ( 0, buffer->write( message1 ) );
    EXPECT_EQ( 0, buffer->write( message2 ) );
    EXPECT_EQ( 0, buffer->write( message3 ) );
    
    /* read the messages */
    CANMessage msg1, msg2, msg3;
    EXPECT_EQ( 0, buffer->read( msg1 ) );
    EXPECT_EQ( 0, buffer->read( msg2 ) );
    EXPECT_EQ( 0, buffer->read( msg3 ) );
    
    /* compare, no reorder */
    EXPECT_EQ( message1, msg1 );
    EXPECT_EQ( message2, msg2 );
    EXPECT_EQ( message3, msg3 );
}

TEST_F( CANBufferGrowingQueueTest, read_write_multiple )
{
	EXPECT_TRUE(false);
}

TEST_F( CANBufferGrowingQueueTest, read_write_async )
{
	EXPECT_TRUE(false);
}

} /* namespace Test */
} /* namespace CanSocket */
