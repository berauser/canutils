/*
 * CANErrorTest.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "CANErrorTest.h"

#include "SocketCanFactory.h"
#include "SocketCanErrorTranslator.h"

#include "CANError.h"

namespace CanUtils
{
namespace Test
{

void CANErrorTest::SetUp()
{  
}

void CANErrorTest::TearDown()
{
}

TEST_F( CANErrorTest, basic )
{
	EXPECT_EQ( 0x0000, static_cast<uint32_t>(CANErrorFlag::NoError)                 );
	EXPECT_EQ( (1<<0), static_cast<uint32_t>(CANErrorFlag::TransmissionTimoutError) );
	EXPECT_EQ( (1<<1), static_cast<uint32_t>(CANErrorFlag::LostArbitrationError)    );
	EXPECT_EQ( (1<<2), static_cast<uint32_t>(CANErrorFlag::ControllerError)         );
	EXPECT_EQ( (1<<3), static_cast<uint32_t>(CANErrorFlag::ProtocolViolationError)  );
	EXPECT_EQ( (1<<4), static_cast<uint32_t>(CANErrorFlag::TransceiveError)         );
	EXPECT_EQ( (1<<5), static_cast<uint32_t>(CANErrorFlag::MissingAcknowledgeError) );
	EXPECT_EQ( (1<<6), static_cast<uint32_t>(CANErrorFlag::BusOffError)             );
	EXPECT_EQ( (1<<7), static_cast<uint32_t>(CANErrorFlag::BusError)                );
	EXPECT_EQ( (1<<8), static_cast<uint32_t>(CANErrorFlag::ControllerRestartError)  );
	EXPECT_EQ( (1<<9), static_cast<uint32_t>(CANErrorFlag::UnknownError)            );
}

TEST_F( CANErrorTest, flag_bit_operator_and )
{
	CANErrorMask mask = static_cast<CANErrorMask>(CANErrorFlag::TransmissionTimoutError);
	mask |= CANErrorFlag::ControllerError;
	
	EXPECT_EQ( ((1<<0) | (1<<1)) , mask  ); 
}

TEST_F( CANErrorTest, bit_operator_or )
{
//	CANError f1(0x000, 0x7FF);
//	CANError f2 = f1; f2 |= CANError::CANErrorFlags::Invert;
//	CANError f3 = f1     |  CANError::CANErrorFlags::Invert;
//	CANError f4 = CANError(0x000, 0x7FF) | CANError::CANErrorFlags::Invert;
//
//	EXPECT_EQ(f1.can_mask, f2.can_mask);
//	EXPECT_EQ(
//			f1.can_id
//					| static_cast<uint32_t>(CANError::CANErrorFlags::Invert),
//			f2.can_id);
//
//	EXPECT_EQ(f2.can_id, f3.can_id);
//	EXPECT_EQ(f2.can_mask, f3.can_mask);
//
//	EXPECT_EQ(f2.can_id, f4.can_id);
//	EXPECT_EQ(f2.can_mask, f4.can_mask);
}

TEST_F( CANErrorTest, compare )
{
//	CANError f1(0x123, 0x7FF);
//	CANError f2(0x123, 0x000);
//	CANError f3(0x7FF, 0x7FF);
//	CANError f4(0x123, 0x7FF);	f4 = f4 | CANError::CANErrorFlags::Invert;
//	CANError f5(0x123, 0x7FF);
//
//	/* check operator== */
//	EXPECT_FALSE(f1 == f2);
//	EXPECT_FALSE(f1 == f3);
//	EXPECT_FALSE(f1 == f4);
//	EXPECT_TRUE(f1 == f5);
//
//	/* check operator!= */
//	EXPECT_TRUE(f1 != f2);
//	EXPECT_TRUE(f1 != f3);
//	EXPECT_TRUE(f1 != f4);
//	EXPECT_FALSE(f1 != f5);
}

TEST_F( CANErrorTest, invert )
{
//	CANErrorFlag flag = CANErrorFlag::TransmissionTimoutError;
//
//	EXPECT_EQ( 0x00000001, static_cast<uint32_t>(  CANErrorFlag::TransmissionTimoutError  ) );
//	EXPECT_EQ( 0xFFFFFFFE, static_cast<uint32_t>( ~CANErrorFlag::TransmissionTimoutError  ) );
//
//	EXPECT_EQ( 0x00000010, static_cast<uint32_t>(  CANErrorFlag::TransceiveError  ) );
//	EXPECT_EQ( 0xFFFFFFEF, static_cast<uint32_t>( ~CANErrorFlag::TransceiveError  ) );
//
//	EXPECT_EQ( 0x00000100, static_cast<uint32_t>(  CANErrorFlag::ControllerRestartError  ) );
//	EXPECT_EQ( 0xFFFFFEFF, static_cast<uint32_t>( ~CANErrorFlag::ControllerRestartError  ) );
}

} /* namespace Test */
} /* namespace CanUtils */
