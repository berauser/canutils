/*
 * CANMessageTest.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "CANMessageTest.h"

#include "SocketCanFactory.h"
#include "MockListener.h"

namespace CanSocket
{
namespace Test
{

void CANMessageTest::SetUp()
{
}

void CANMessageTest::TearDown()
{
}

TEST_F( CANMessageTest, functions )
{
	CANMessage message1( 0x1FFFFFFFU, CANMessage::CANFrameType::Standard, 8, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 );
	CANMessage message2( 0x1FFFFFFFU, CANMessage::CANFrameType::Extended, 8, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 );
	CANMessage message3( 0x1FFFFFFFU, CANMessage::CANFrameType::Remote,   8, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 );
	CANMessage message4( 0x1FFFFFFFU, CANMessage::CANFrameType::Error,    8, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 );

	EXPECT_EQ( 0x000007FFU | 0x00000000U, message1.can_id );
	EXPECT_EQ( 0x1FFFFFFFU | 0x80000000U, message2.can_id );
	EXPECT_EQ( 0x1FFFFFFFU | 0x40000000U, message3.can_id );
	EXPECT_EQ( 0x1FFFFFFFU | 0x20000000U, message4.can_id );

	EXPECT_EQ( 0x000007FFU, message1.id() );
	EXPECT_EQ( 0x1FFFFFFFU, message2.id() );
	EXPECT_EQ( 0x1FFFFFFFU, message3.id() );
	EXPECT_EQ( 0x1FFFFFFFU, message4.id() );

	EXPECT_EQ( CANMessage::CANFrameType::Standard, message1.type() );
	EXPECT_EQ( CANMessage::CANFrameType::Extended, message2.type() );
	EXPECT_EQ( CANMessage::CANFrameType::Remote,   message3.type() );
	EXPECT_EQ( CANMessage::CANFrameType::Error,    message4.type() );
}

TEST_F( CANMessageTest, compare )
{
	CANMessage message1( 0x111, CANMessage::CANFrameType::Standard, 8, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 );

	EXPECT_EQ( static_cast<uint32_t>(0x111), message1.can_id  );
	EXPECT_EQ( static_cast<uint8_t> (8),     message1.can_dlc );

	EXPECT_EQ( static_cast<uint8_t>(0x00), message1.data[0] );
	EXPECT_EQ( static_cast<uint8_t>(0x11), message1.data[1] );
	EXPECT_EQ( static_cast<uint8_t>(0x22), message1.data[2] );
	EXPECT_EQ( static_cast<uint8_t>(0x33), message1.data[3] );
	EXPECT_EQ( static_cast<uint8_t>(0x44), message1.data[4] );
	EXPECT_EQ( static_cast<uint8_t>(0x55), message1.data[5] );
	EXPECT_EQ( static_cast<uint8_t>(0x66), message1.data[6] );
	EXPECT_EQ( static_cast<uint8_t>(0x77), message1.data[7] );
}

TEST_F( CANMessageTest, flag )
{
	CANMessage message( 0x000 );

	/* test logical or */
	EXPECT_EQ( 0x80000000U, (message | CANFlag::Extended).can_id );
	EXPECT_EQ( 0x40000000U, (message | CANFlag::Remote).can_id );
	EXPECT_EQ( 0x20000000U, (message | CANFlag::Error).can_id );

	EXPECT_EQ( ~0x80000000U, (message | ~CANFlag::Extended).can_id );
	EXPECT_EQ( ~0x40000000U, (message | ~CANFlag::Remote).can_id );
	EXPECT_EQ( ~0x20000000U, (message | ~CANFlag::Error).can_id );


	message.can_id = ~message.can_id;

	/* test logical and */
	EXPECT_EQ( 0xFFFFFFFFU & 0x80000000U, (message & CANFlag::Extended).can_id );
	EXPECT_EQ( 0xFFFFFFFFU & 0x40000000U, (message & CANFlag::Remote).can_id );
	EXPECT_EQ( 0xFFFFFFFFU & 0x20000000U, (message & CANFlag::Error).can_id );

	EXPECT_EQ( 0xFFFFFFFFU & ~0x80000000U, (message & ~CANFlag::Extended).can_id );
	EXPECT_EQ( 0xFFFFFFFFU & ~0x40000000U, (message & ~CANFlag::Remote).can_id );
	EXPECT_EQ( 0xFFFFFFFFU & ~0x20000000U, (message & ~CANFlag::Error).can_id );
}

TEST_F( CANMessageTest, mask )
{
	CANMessage message( 0x000 );

	/* test logical or */
	EXPECT_EQ( 0x000007FFU, (message | CANMask::Standard).can_id );
	EXPECT_EQ( 0x1FFFFFFFU, (message | CANMask::Extended).can_id );
	EXPECT_EQ( 0x1FFFFFFFU, (message | CANMask::Error).can_id );

	EXPECT_EQ( ~0x000007FFU, (message | ~CANMask::Standard).can_id );
	EXPECT_EQ( ~0x1FFFFFFFU, (message | ~CANMask::Extended).can_id );
	EXPECT_EQ( ~0x1FFFFFFFU, (message | ~CANMask::Error).can_id );


	message.can_id = ~message.can_id;

	/* test logical and */
	EXPECT_EQ( 0xFFFFFFFFU & 0x000007FFU, (message & CANMask::Standard).can_id );
	EXPECT_EQ( 0xFFFFFFFFU & 0x1FFFFFFFU, (message & CANMask::Extended).can_id );
	EXPECT_EQ( 0xFFFFFFFFU & 0x1FFFFFFFU, (message & CANMask::Error).can_id );

	EXPECT_EQ( 0xFFFFFFFFU & ~0x000007FFU, (message & ~CANMask::Standard).can_id );
	EXPECT_EQ( 0xFFFFFFFFU & ~0x1FFFFFFFU, (message & ~CANMask::Extended).can_id );
	EXPECT_EQ( 0xFFFFFFFFU & ~0x1FFFFFFFU, (message & ~CANMask::Error).can_id );
}

} /* namespace Test */
} /* namespace CanSocket */
