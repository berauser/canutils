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

TEST_F( CANFilterTest, create )
{
	CANFilter f1;
	EXPECT_EQ( f1.can_id,   0x00 );
	EXPECT_EQ( f1.can_mask, 0x1FFFFFFFU );

	CANFilter f2( 0x111 );
	EXPECT_EQ( f2.can_id,   0x111 );
	EXPECT_EQ( f2.can_mask, 0x1FFFFFFFU );

	CANFilter f3( 0x222, 0x333 );
	EXPECT_EQ( f3.can_id,   0x222 );
	EXPECT_EQ( f3.can_mask, 0x333 );
}

TEST_F( CANFilterTest, bit_operator_and )
{
	CANFilter f1( 0x7FF, 0x7FF );
	CANFilter f2 = f1 & CANFilter::CANFilterFlags::Invert;
	CANFilter f3 = CANFilter ( 0x7FF, 0x7FF ) & CANFilter::CANFilterFlags::Invert;

	EXPECT_EQ( f1.can_mask, f2.can_mask );
	EXPECT_EQ( f1.can_id & static_cast<uint32_t>(CANFilter::CANFilterFlags::Invert), f2.can_id );

	EXPECT_EQ( f2.can_id, f3.can_id );
	EXPECT_EQ( f2.can_mask, f3.can_mask );
}

TEST_F( CANFilterTest, bit_operator_or )
{
	CANFilter f1( 0x000, 0x7FF );
	CANFilter f2 = f1 | CANFilter::CANFilterFlags::Invert;
	CANFilter f3 = CANFilter ( 0x000, 0x7FF ) | CANFilter::CANFilterFlags::Invert;

	EXPECT_EQ  ( f1.can_mask, f2.can_mask );
	EXPECT_EQ  ( f1.can_id | static_cast<uint32_t>(CANFilter::CANFilterFlags::Invert), f2.can_id );

	EXPECT_EQ( f2.can_id, f3.can_id );
	EXPECT_EQ( f2.can_mask, f3.can_mask );
}

TEST_F( CANFilterTest, compare )
{
	CANFilter f1 { 0x123, 0x7FF };
	CANFilter f2 { 0x123, 0x000 };
	CANFilter f3 { 0x7FF, 0x7FF };
	CANFilter f4 { 0x123, 0x7FF }; f4 = f4 | CANFilter::CANFilterFlags::Invert;
	CANFilter f5 { 0x123, 0x7FF };

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
