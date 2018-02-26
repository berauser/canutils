/*
 * CANBufferPriortiyQueueTest.h
 *
 *  Created on: 26.02.2018
 *      Author: rauser
 */

#ifndef TEST_CANBUFFER_PRIORITYQUEUETEST_H_
#define TEST_CANBUFFER_PRIORITYQUEUETEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace CanSocket
{
namespace Test
{

class CANBufferPriortiyQueueTest : public ::testing::Test
{
protected:
	virtual void SetUp();
	virtual void TearDown();
};

} /* namespace Test */
} /* namespace CanSocket */

#endif /* TEST_CANBUFFER_PRIORITYQUEUETEST_H_ */
