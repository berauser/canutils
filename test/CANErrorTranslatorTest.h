/*
 * CANErrorTranslatorTest.h
 *
 *  Created on: 09.02.2018
 *      Author: rauser
 */

#ifndef TEST_CANERRORTRANSLATORTEST_H
#define TEST_CANERRORTRANSLATORTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace CanSocket
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
} /* namespace CanSocket */

#endif // TEST_CANERRORTRANSLATORTEST_H
