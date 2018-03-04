/*
 * CANFilterTest.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "CANFilterTest.h"

#include "SocketCanFactory.h"

namespace CanUtils
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
	/* use default */
	CANFilter f1;
	EXPECT_EQ(f1.can_id, 0x00);
	EXPECT_EQ(f1.can_mask, 0x1FFFFFFFU);

	/* override default can_id */
	CANFilter f2(0x111);
	EXPECT_EQ(f2.can_id, 0x111);
	EXPECT_EQ(f2.can_mask, 0x1FFFFFFFU);

	/* set can_id and can_mask */
	CANFilter f3(0x222, 0x333);
	EXPECT_EQ(f3.can_id, 0x222);
	EXPECT_EQ(f3.can_mask, 0x333);
}

TEST_F( CANFilterTest, bit_operator_and )
{
	CANFilter f1(0x7FF, 0x7FF);
	CANFilter f2 = f1; f2 &= CANFilter::CANFilterFlags::Invert;
	CANFilter f3 = f1 & CANFilter::CANFilterFlags::Invert;
	CANFilter f4 = CANFilter(0x7FF, 0x7FF) & CANFilter::CANFilterFlags::Invert;

	EXPECT_EQ(f1.can_mask, f2.can_mask);
	EXPECT_EQ(
			f1.can_id
					& static_cast<uint32_t>(CANFilter::CANFilterFlags::Invert),
			f2.can_id);

	EXPECT_EQ(f2.can_id, f3.can_id);
	EXPECT_EQ(f2.can_mask, f3.can_mask);

	EXPECT_EQ(f2.can_id, f4.can_id);
	EXPECT_EQ(f2.can_mask, f4.can_mask);
}

TEST_F( CANFilterTest, bit_operator_or )
{
	CANFilter f1(0x000, 0x7FF);
	CANFilter f2 = f1; f2 |= CANFilter::CANFilterFlags::Invert;
	CANFilter f3 = f1     |  CANFilter::CANFilterFlags::Invert;
	CANFilter f4 = CANFilter(0x000, 0x7FF) | CANFilter::CANFilterFlags::Invert;

	EXPECT_EQ(f1.can_mask, f2.can_mask);
	EXPECT_EQ(
			f1.can_id
					| static_cast<uint32_t>(CANFilter::CANFilterFlags::Invert),
			f2.can_id);

	EXPECT_EQ(f2.can_id, f3.can_id);
	EXPECT_EQ(f2.can_mask, f3.can_mask);

	EXPECT_EQ(f2.can_id, f4.can_id);
	EXPECT_EQ(f2.can_mask, f4.can_mask);
}

TEST_F( CANFilterTest, compare )
{
	CANFilter f1(0x123, 0x7FF);
	CANFilter f2(0x123, 0x000);
	CANFilter f3(0x7FF, 0x7FF);
	CANFilter f4(0x123, 0x7FF);	f4 = f4 | CANFilter::CANFilterFlags::Invert;
	CANFilter f5(0x123, 0x7FF);

	/* check operator== */
	EXPECT_FALSE(f1 == f2);
	EXPECT_FALSE(f1 == f3);
	EXPECT_FALSE(f1 == f4);
	EXPECT_TRUE(f1 == f5);

	/* check operator!= */
	EXPECT_TRUE(f1 != f2);
	EXPECT_TRUE(f1 != f3);
	EXPECT_TRUE(f1 != f4);
	EXPECT_FALSE(f1 != f5);
}

TEST_F( CANFilterTest, invert )
{
	CANFilter f1(0x123, 0x7FF);
	CANFilter f2 = f1 | CANFilter::CANFilterFlags::Invert;
	CANFilter f3(0x123, 0x7FF);

	/* check inversion with parameter */
	EXPECT_EQ(false, f3.isInverted());
	f3.invert();
	EXPECT_EQ(true, f3.isInverted());

	/* comapre with operator | */
	EXPECT_EQ( f2.can_id, f3.can_id );
	EXPECT_EQ( f3.can_mask, f3.can_mask);
}

TEST_F( CANFilterTest, matches )
{
    CANFilter f1, f2, f3;
    CANMessage m1( 0x123, CANMessage::CANFrameType::Standard, 0);
    CANMessage m2( 0x700, CANMessage::CANFrameType::Standard, 0);
    CANMessage m3( 0x7F3, CANMessage::CANFrameType::Standard, 0);
    CANMessage m4( 0x2F1, CANMessage::CANFrameType::Standard, 0);
    CANMessage m5( 0x001, CANMessage::CANFrameType::Standard, 0);
    CANMessage m6( 0x3F5, CANMessage::CANFrameType::Standard, 0);
    CANMessage m7( 0x2F0, CANMessage::CANFrameType::Standard, 0);
    
    /* ID 0x123 */
    f1.can_id   = 0x123;
    f1.can_mask = 0x7FF;
    
    EXPECT_TRUE ( f1.matches( m1 ) );
    EXPECT_FALSE( f1.matches( m2 ) );
    EXPECT_FALSE( f1.matches( m3 ) );
    EXPECT_FALSE( f1.matches( m4 ) );
    EXPECT_FALSE( f1.matches( m5 ) );
    EXPECT_FALSE( f1.matches( m6 ) );
    EXPECT_FALSE( f1.matches( m7 ) );
    
    /* ID 0x3F0 - 0x3FF */
    f2.can_id   = 0x3F0;
    f2.can_mask = 0x7F0;
    
    EXPECT_FALSE( f2.matches( m1 ) );
    EXPECT_FALSE( f2.matches( m2 ) );
    EXPECT_FALSE( f2.matches( m3 ) );
    EXPECT_FALSE( f2.matches( m4 ) );
    EXPECT_FALSE( f2.matches( m5 ) );
    EXPECT_TRUE ( f2.matches( m6 ) );
    EXPECT_FALSE( f2.matches( m7 ) );
    
    /* ID != 0x2F0,0x2F1 */
    f3.can_id   = 0x2F0;
    f3.can_mask = 0x2FE;
    f3.invert();
    
    EXPECT_TRUE ( f3.matches( m1 ) );
    EXPECT_TRUE ( f3.matches( m2 ) );
    EXPECT_TRUE ( f3.matches( m3 ) );
    EXPECT_FALSE( f3.matches( m4 ) );
    EXPECT_TRUE ( f3.matches( m5 ) );
    EXPECT_TRUE ( f3.matches( m6 ) );
    EXPECT_FALSE( f3.matches( m7 ) );
}

} /* namespace Test */
} /* namespace CanUtils */
