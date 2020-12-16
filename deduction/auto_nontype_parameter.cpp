//
// Created by weining on 17/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <type_traits>

// C++ 17 in detail P/58
// this new syntax feature can simplify template definition
// can also enable heterogeneous compile-time type list - see:
// cxxFP/type_level_fun/conslist/typelist_creation.cpp

template< typename T >
struct Wrapped
{
    using value_t = T;
    T x;

    explicit Wrapped( T&& value )
      : x( std::forward< T >( value ) )
    {
    }
};

template< auto X >
Wrapped< decltype( X ) >
amplify( decltype( X ) multiplier )
{
    return Wrapped( X * multiplier );
}

TEST_CASE( "automatically deduce non-type parameter" )
{
    static_assert( std::is_same_v< decltype( amplify< 19 >( 2 ) )::value_t, int > );
    CHECK_EQ( amplify< 10 >( 2 ).x, 20 );
}
