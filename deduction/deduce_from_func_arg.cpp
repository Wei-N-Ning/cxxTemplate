//
// Created by weining on 2/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <type_traits>

// complete guide L7225
// typename B is explicitly specified at the call site whereas A is deduced from
// the function arguments
template< typename B, typename A >
B
implicit_cast( const A& a )
{
    return a;
}

TEST_CASE( "explicit and implicit deduction" )
{
    CHECK_EQ( 1, implicit_cast< int >( 1.0 ) );

    static_assert( std::is_same_v< decltype( implicit_cast< int >( 1.0 ) ), int > );
}
