/*
 * SocketCanTest.h
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#ifndef TEST_SOCKETCANTEST_H_
#define TEST_SOCKETCANTEST_H_

#include <gtest/gtest.h>

namespace CanSocket
{
namespace Test
{

class SocketCanTest : public ::testing::Test
{
protected:
	virtual void SetUp();
	virtual void TearDown();
};

} /* namespace Test */
} /* namespace CanSocket */

#endif /* TEST_SOCKETCANTEST_H_ */
