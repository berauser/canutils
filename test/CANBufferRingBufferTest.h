/*
 * CANBufferRingBufferTest.h
 *
 *  Created on: 26.02.2018
 *      Author: rauser
 */

#ifndef TEST_RINGBUFFERTEST_H_
#define TEST_RINGBUFFERTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace CanSocket
{
namespace Test
{

class CANBufferRingBufferTest : public ::testing::Test
{
protected:
	virtual void SetUp();
	virtual void TearDown();
};

} /* namespace Test */
} /* namespace CanSocket */

#endif /* TEST_RINGBUFFERTEST_H_ */
