/*
 * RegistryTest.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "RegistryTest.h"
#include "Registry.h"

#include <algorithm>

namespace CanUtils
{
namespace Test
{
void RegistryTest::SetUp()
{  
}

void RegistryTest::TearDown()
{
}

TEST_F( RegistryTest, intial )
{
    
}

TEST_F( RegistryTest, without_args )
{
    Registry<Base,std::string> registry;
    EXPECT_EQ( 0, registry.registeredClassKeys().size() );
    
    registry.registerClass<DerivedBar>( "DerivedBar" );
    EXPECT_EQ( 1, registry.registeredClassKeys().size() );
    
    std::shared_ptr<Base> bar = registry.get( "DerivedBar" );
    
    EXPECT_EQ( -1, bar->arg() );
}

TEST_F( RegistryTest, with_args )
{
    Registry<Base,std::string,int> registry;
    EXPECT_EQ( 0, registry.registeredClassKeys().size() );
    
    registry.registerClass<DerivedBar>( "DerivedBar" );
    EXPECT_EQ( 1, registry.registeredClassKeys().size() );
    
    std::shared_ptr<Base> bar1 = registry.get( "DerivedBar", 1 );
    std::shared_ptr<Base> bar2 = registry.get( "DerivedBar", 2 );
    
    EXPECT_EQ( 1, bar1->arg() );
    EXPECT_EQ( 2, bar2->arg() );
}

TEST_F( RegistryTest, un_register )
{
    Registry<Base,std::string> registry;
    EXPECT_EQ( 0, registry.registeredClassKeys().size() );
    
    registry.registerClass<DerivedBar>( "DerivedBar" );
    
    EXPECT_EQ  ( 1, registry.registeredClassKeys().size() );
    EXPECT_TRUE( registry.isRegisteredClass("DerivedBar") );
    
    registry.unregisterClass( "DerivedBar" );
    
    EXPECT_EQ   ( 0, registry.registeredClassKeys().size() );
    EXPECT_FALSE( registry.isRegisteredClass("DerivedBar") );
}

TEST_F( RegistryTest, create_unknown )
{
    Registry<Base,std::string> registry;
    EXPECT_EQ( 0, registry.registeredClassKeys().size() );
    
    EXPECT_THROW( registry.get("unknown"), UndefinedKeyException<std::string> );
    
    try { registry.get("unknown"); }
    catch ( UndefinedKeyException<std::string> e )
    {
        EXPECT_EQ( "Key is not defined", std::string(e.what()) );
        EXPECT_EQ( "unknown",            std::string(e.key() ) );
    }
    
    try { registry.get("DerivedBar"); }
    catch ( UndefinedKeyException<std::string> e )
    {
        EXPECT_EQ( "Key is not defined", std::string(e.what()) );
        EXPECT_EQ( "DerivedBar",         std::string(e.key() ) );
    }
}

TEST_F( RegistryTest, list )
{
    Registry<Base,std::string,int> registry;
    EXPECT_EQ( 0, registry.registeredClassKeys().size() );
    
    registry.registerClass<DerivedBar>( "DerivedBar" );
    registry.registerClass<DerivedFoo>( "DerivedFoo" );
    EXPECT_EQ( 2, registry.registeredClassKeys().size() );
    
    std::list<std::string> keys = registry.registeredClassKeys();
    EXPECT_TRUE( std::find(keys.begin(), keys.end(), "DerivedBar") != keys.end() );
    EXPECT_TRUE( std::find(keys.begin(), keys.end(), "DerivedFoo") != keys.end() );
}

TEST_F( RegistryTest, clear )
{
    Registry<Base,std::string,int> registry;
    EXPECT_EQ( 0, registry.registeredClassKeys().size() );
    
    registry.registerClass<DerivedBar>( "DerivedBar" );
    registry.registerClass<DerivedFoo>( "DerivedFoo" );
    EXPECT_EQ( 2, registry.registeredClassKeys().size() );
    
    registry.clear();
    EXPECT_EQ( 0, registry.registeredClassKeys().size() );
}

TEST_F( RegistryTest, get )
{
    Registry<Base,std::string> registry;
    EXPECT_EQ( 0, registry.registeredClassKeys().size() );
    
    registry.registerClass<DerivedBar>( "DerivedBar" );
    registry.registerClass<DerivedFoo>( "DerivedFoo" );
    EXPECT_EQ( 2, registry.registeredClassKeys().size() );
    
    std::shared_ptr<Base> bar = registry.get( "DerivedBar" );;
    std::shared_ptr<Base> foo = registry.get( "DerivedFoo" );;
    
    EXPECT_EQ( "DerivedBar", bar->getType() );
    EXPECT_EQ( "DerivedFoo", foo->getType() );
}

} /* namespace Test */
} /* namespace CanUtils */
