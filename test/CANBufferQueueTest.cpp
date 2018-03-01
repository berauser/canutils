/*
 * CANBufferQueueTest.cpp
 *
 *  Created on: 26.02.2018
 *      Author: rauser
 */

#include "CANBufferQueueTest.h"

#include "SocketCanFactory.h"
#include <thread>

namespace CanUtils
{
namespace Test
{

void CANUtilsQueueTest::SetUp()
{  
}

void CANUtilsQueueTest::TearDown()
{
}

TEST_F( CANUtilsQueueTest, initialization )
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

TEST_F( CANUtilsQueueTest, isFull )
{
	SocketCanFactory factory;
	CanBufferPtr buffer = factory.createCanBuffer("Queue", 16);
	
	/* buffer should be not full */
	EXPECT_FALSE( buffer->isFull() );
	
	/* fill buffer */
	for( unsigned int i = 0; i < buffer->size() ; ++i )
	{
		CANMessage message( i, CANMessage::CANFrameType::Standard, 1, i );
		EXPECT_EQ( 0, buffer->write( message ) );
	}
	
	/* buffer is now full */
	EXPECT_TRUE ( buffer->isFull() );
	
	/* read a single message -> buffer is not full */
	CANMessage msg;
	EXPECT_EQ( 0, buffer->read( msg ) );
	
	EXPECT_FALSE( buffer->isFull() );
}


TEST_F( CANUtilsQueueTest, isEmpty )
{
	SocketCanFactory factory;
	CanBufferPtr buffer = factory.createCanBuffer("Queue", 16);
	
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

TEST_F( CANUtilsQueueTest, resize )
{
	SocketCanFactory factory;
	CanBufferPtr buffer = factory.createCanBuffer("Queue", 2);
	
	/* add a single message */
	CANMessage message( 0x123, CANMessage::CANFrameType::Standard, 1, 0x01 );
	EXPECT_EQ( 0, buffer->write( message ) );
	EXPECT_EQ( 0, buffer->write( message ) );
	
	/* buffer should be full */
	EXPECT_TRUE( buffer->isFull() );
	
	/* double buffer size */
	EXPECT_EQ(0, buffer->resize( 2 * buffer->size() ) );  
	
	/* buffer is not full */
	EXPECT_FALSE( buffer->isFull() );
	
	/* add another two messages */
	EXPECT_EQ( 0, buffer->write( message ) );
	EXPECT_EQ( 0, buffer->write( message ) );
	
	/* buffer should be full */
	EXPECT_TRUE( buffer->isFull() );
}

TEST_F( CANUtilsQueueTest, clear )
{
	SocketCanFactory factory;
	CanBufferPtr buffer = factory.createCanBuffer("Queue", 16);
	
	/* buffer should be empty */
	EXPECT_TRUE( buffer->isEmpty() );
	
	/* add a single message */
	CANMessage message( 0x123, CANMessage::CANFrameType::Standard, 1, 0x01 );
	EXPECT_EQ( 0, buffer->write( message ) );
	
	/* buffer is not empty */
	EXPECT_FALSE( buffer->isEmpty() );
	
	/* clear the buffer */
	buffer->clear();
	
	EXPECT_TRUE( buffer->isEmpty() );
}

TEST_F( CANUtilsQueueTest, read_write_single )
{
    SocketCanFactory factory;
    CanBufferPtr buffer = factory.createCanBuffer("Queue");
    
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

TEST_F( CANUtilsQueueTest, read_write_async )
{
    SocketCanFactory factory;
    CanBufferPtr buffer = factory.createCanBuffer("Queue");
    const unsigned int retries = 100;
    
    std::thread worker = std::thread
    (
        [&](){
            for( unsigned int i = 0; i < retries; ++i )
            {
                CANMessage message_tx( 0x001, CANMessage::CANFrameType::Standard, 1, i );
                EXPECT_EQ( 0, buffer->write( message_tx ) );
            }
        }
    );
        
    /* read the messages */
    for( unsigned int i = 0; i< retries; ++i )
    {
        CANMessage message( 0x001, CANMessage::CANFrameType::Standard, 1, i );
        CANMessage message_rx;
        /* order should be the same, if we inserted it */
        EXPECT_EQ( 0, buffer->read( message_rx ) );
        EXPECT_EQ( message, message_rx );
    }
    
    /* wait for thread */
    if( worker.joinable() )
    {
        worker.join();
    }
}

} /* namespace Test */
} /* namespace CanUtils */
