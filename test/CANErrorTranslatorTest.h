/*
 * CANErrorTranslatorTest.h
 *
 *  Created on: 09.02.2018
 *      Author: rauser
 */

#ifndef TEST_CANERRORTRANSLATORTEST_H_
#define TEST_CANERRORTRANSLATORTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace CanUtils
{
namespace Test
{

class CANErrorTranslatorTest : public ::testing::Test
{
protected:
	virtual void SetUp();
	virtual void TearDown();
};

} /* namespace Test */
} /* namespace CanUtils */

#endif /* TEST_CANERRORTRANSLATORTEST_H_ */
