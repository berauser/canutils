/*
 * CANBufferRingBufferTest.cpp
 *
 *  Created on: 26.02.2018
 *      Author: rauser
 */

#include "CANBufferRingBufferTest.h"

#include "SocketCanFactory.h"

namespace CanSocket
{
namespace Test
{

void CANBufferRingBufferTest::SetUp()
{  
}

void CANBufferRingBufferTest::TearDown()
{
}

TEST_F( CANBufferRingBufferTest, initialization )
{
	SocketCanFactory factory;
	CanBufferPtr buffer1 = factory.createCanBuffer("RingBuffer");
	
	EXPECT_EQ   ( DEFAULT_BUFFER_SIZE, buffer1->size()           ); 
	EXPECT_EQ   ( "RingBuffer",             buffer1->implementation() );
	EXPECT_TRUE ( buffer1->isEmpty() );
	EXPECT_FALSE( buffer1->isFull()  );
	EXPECT_FALSE( buffer1->hasNext() );
	
	CanBufferPtr buffer2 = factory.createCanBuffer("RingBuffer", 42);
	
	EXPECT_EQ   ( 42,      buffer2->size()           ); 
	EXPECT_EQ   ( "RingBuffer", buffer2->implementation() );
	EXPECT_TRUE ( buffer2->isEmpty() );
	EXPECT_FALSE( buffer2->isFull()  );
	EXPECT_FALSE( buffer2->hasNext() );
}

TEST_F( CANBufferRingBufferTest, isFull )
{
	SocketCanFactory factory;
	CanBufferPtr buffer = factory.createCanBuffer("RingBuffer", 16);
	
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


TEST_F( CANBufferRingBufferTest, isEmpty )
{
	SocketCanFactory factory;
	CanBufferPtr buffer = factory.createCanBuffer("RingBuffer", 16);
	
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

TEST_F( CANBufferRingBufferTest, resize )
{
	SocketCanFactory factory;
	CanBufferPtr buffer = factory.createCanBuffer("RingBuffer", 2);
	
	/* double buffer size */
	/* NOTE Resizing is currently not possible */
	EXPECT_EQ(-1, buffer->resize( 2 * buffer->size() ) );  
	
}

TEST_F( CANBufferRingBufferTest, clear )
{
	SocketCanFactory factory;
	CanBufferPtr buffer = factory.createCanBuffer("RingBuffer", 16);
	
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

TEST_F( CANBufferRingBufferTest, override_write_single )
{
    SocketCanFactory factory;
    CanBufferPtr buffer = factory.createCanBuffer("RingBuffer");
    
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

TEST_F( CANBufferRingBufferTest, override_write_async )
{
    /* NOTE messages can be lost */
	EXPECT_TRUE(false);
}

} /* namespace Test */
} /* namespace CanSocket */
