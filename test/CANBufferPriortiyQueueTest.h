/*
 * CANBufferPriortiyQueueTest.h
 *
 *  Created on: 26.02.2018
 *      Author: rauser
 */

#ifndef TEST_PRIORITYQUEUETEST_H_
#define TEST_PRIORITYQUEUETEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace CanUtils
{
namespace Test
{

class CANUtilsPriortiyQueueTest : public ::testing::Test
{
protected:
	virtual void SetUp();
	virtual void TearDown();
};

} /* namespace Test */
} /* namespace CanUtils */

#endif /* TEST_PRIORITYQUEUETEST_H_ */
