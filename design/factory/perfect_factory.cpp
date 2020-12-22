//
// Created by weining on 21/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <memory>
#include <string>
#include <iostream>
#include <type_traits>

// c++ 17 in detail P/271
// a generic factory template that can produces a family of types based on
//  - factory tag selection, and
//  - ctor type matching

// it can be implemented in c++14 using SFINAE and enable_if<>, or
// in c++17, using if-constexpr (which is much cleaner!)

// this example is inspired by Effective Modern C++, Item 18

// c++ 17 the complete guide P/39
// with rvo and mandatory copy-elision, this type of `perfect factory` is
// highly encouraged, even when the object is not allowed to copy or move
//
// examples:
// unique_ptr<>
// atomic<>

// base type
struct Investment
{
    virtual ~Investment() = default;
    virtual size_t risk()
    {
        return 0;
    }
};

// derived types
struct Stock : public Investment
{
    explicit Stock( int )
    {
    }

    size_t risk() override
    {
        return 1;
    }
};

struct Bond : public Investment
{
    Bond( double, double )
    {
    }

    size_t risk() override
    {
        return 2;
    }
};

struct RealEstate : public Investment
{
    RealEstate( int, double, int )
    {
    }

    size_t risk() override
    {
        return 3;
    }
};

// the example in Scott Meyers' book does not work with this type family,
// as the number of arguments is unique for each derived class; the code
// won't compile

// the perfect factory

// ======================== the c++14 impl ========================

template< typename Concrete, typename... Ts >
std::enable_if_t< std::is_constructible_v< Concrete, Ts... >,
                  std::unique_ptr< Concrete > >
constructArgs_14( Ts&&... params )
{
    return std::make_unique< Concrete >( std::forward< Ts >( params )... );
}

template< typename Concrete, typename... Ts >
std::enable_if_t< !std::is_constructible_v< Concrete, Ts... >,
                  std::unique_ptr< Concrete > >
constructArgs_14( Ts&&... )
{
    return nullptr;
}

template< typename... Ts >
std::unique_ptr< Investment >
makeInvestment_14( const std::string& name, Ts&&... params )
{
    std::unique_ptr< Investment > pInv;
    if ( name == "Stock" )
    {
        pInv = constructArgs_14< Stock, Ts... >( std::forward< Ts >( params )... );
    }
    else if ( name == "Bond" )
    {
        pInv = constructArgs_14< Bond, Ts... >( std::forward< Ts >( params )... );
    }
    else if ( name == "RealEstate" )
    {
        pInv = constructArgs_14< RealEstate, Ts... >( std::forward< Ts >( params )... );
    }
    return pInv;
}

TEST_CASE( "test c++14 implementation" )
{
    auto stock = makeInvestment_14( "Stock", 10 );
    CHECK_EQ( stock->risk(), 1 );

    auto bond = makeInvestment_14( "Bond", 1.0, 1.0 );
    CHECK_EQ( bond->risk(), 2 );

    auto realEstate = makeInvestment_14( "RealEstate", 10, 1.3, 20 );
    CHECK_EQ( realEstate->risk(), 3 );

    auto invalid1 = makeInvestment_14( "Doom", 10, 10 );
    CHECK_FALSE( invalid1 );
    auto invalid2 = makeInvestment_14( "Stock", 10, 1.3, 20 );
    CHECK_FALSE( invalid2 );
}

// ======================== the c++17 impl ========================

template< typename Concrete, typename... Ts >
std::unique_ptr< Concrete >
constructArgs_17( Ts... params )
{
    // utilizing c++17 fold expression
    std::cout << __PRETTY_FUNCTION__ << ": ";
    ( ( std::cout << params << ' ' ), ... );
    std::cout << '\n';

    if constexpr ( std::is_constructible_v< Concrete, Ts... > )
    {
        return std::make_unique< Concrete >( std::forward< Ts >( params )... );
    }
    else
    {
        return nullptr;
    }
}

template< typename... Ts >
std::unique_ptr< Investment >
makeInvestment_17( const std::string& name, Ts&&... params )
{
    std::unique_ptr< Investment > pInv;
    if ( name == "Stock" )
    {
        pInv = constructArgs_17< Stock, Ts... >( std::forward< Ts >( params )... );
    }
    else if ( name == "Bond" )
    {
        pInv = constructArgs_17< Bond, Ts... >( std::forward< Ts >( params )... );
    }
    else if ( name == "RealEstate" )
    {
        pInv = constructArgs_17< RealEstate, Ts... >( std::forward< Ts >( params )... );
    }
    return pInv;
}

TEST_CASE( "test c++17 implementation" )
{
    auto stock = makeInvestment_17( "Stock", 10 );
    CHECK_EQ( stock->risk(), 1 );

    auto bond = makeInvestment_17( "Bond", 1.0, 1.0 );
    CHECK_EQ( bond->risk(), 2 );

    auto realEstate = makeInvestment_17( "RealEstate", 10, 1.3, 20 );
    CHECK_EQ( realEstate->risk(), 3 );

    auto invalid1 = makeInvestment_17( "Doom", 10, 10 );
    CHECK_FALSE( invalid1 );
    auto invalid2 = makeInvestment_17( "Stock", 10, 1.3, 20 );
    CHECK_FALSE( invalid2 );
}
