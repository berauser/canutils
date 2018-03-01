/*
 * CANBufferGrowingQueueTest.h
 *
 *  Created on: 26.02.2018
 *      Author: rauser
 */

#ifndef TEST_GROWINGQUEUETEST_H_
#define TEST_GROWINGQUEUETEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace CanUtils
{
namespace Test
{

class CANUtilsGrowingQueueTest : public ::testing::Test
{
protected:
	virtual void SetUp();
	virtual void TearDown();
};

} /* namespace Test */
} /* namespace CanUtils */

#endif /* TEST_GROWINGQUEUETEST_H_ */
