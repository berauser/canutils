/*
 * CANErrorTest.h
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#ifndef TEST_CANERRORTEST_H_
#define TEST_CANERRORTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace CanUtils
{
namespace Test
{

class CANErrorTest : public ::testing::Test
{
protected:
	virtual void SetUp();
	virtual void TearDown();
};

} /* namespace Test */
} /* namespace CanUtils */

#endif /* TEST_CANERRORTEST_H_ */
