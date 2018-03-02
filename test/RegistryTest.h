/*
 * RegistryTest.h
 *
 *  Created on: 02.03.2018
 *      Author: rauser
 */

#ifndef TEST_REGISTRYTEST_H_
#define TEST_REGISTRYTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

namespace CanUtils
{
namespace Test
{

class RegistryTest : public ::testing::Test
{
protected:
	virtual void SetUp();
	virtual void TearDown();
};

class Base
{
public:
    Base() : _arg(-1) {}
    Base( int arg ) : _arg(arg) {}
    virtual ~Base() = default;
    virtual std::string getType() = 0;
    virtual int arg()
    {
        return _arg;
    }
protected:
    int _arg;
};

class DerivedFoo : public Base
{
public:
    DerivedFoo() : Base() {} 
    DerivedFoo( int arg ) : Base(arg) {}
    virtual ~DerivedFoo() = default;
    virtual std::string getType()
    {
        return "DerivedFoo";
    }
};

class DerivedBar : public Base
{
public:
    DerivedBar() : Base() {} 
    DerivedBar( int arg ) : Base(arg) {}
    virtual ~DerivedBar() = default;
    virtual std::string getType()
    {
        return "DerivedBar";
    }
};

} /* namespace Test */
} /* namespace CanUtils */

#endif /* TEST_REGISTRYTEST_H_ */
