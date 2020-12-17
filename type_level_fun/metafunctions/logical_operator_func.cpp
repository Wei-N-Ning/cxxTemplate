//
// Created by weining on 17/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <type_traits>
#include <sstream>

// C++ 17 in detail {/60
// some new handy template metafunctions for the logical operation
// conjunction_v ... AND
// disjunction_v ... OR
// negation !

template< typename OStream, typename... Ts >
std::enable_if_t< std::conjunction_v< std::is_same< int, Ts >... > >
printInts( OStream& os, Ts... args )
{
    ( os << ... << args );
}

TEST_CASE( "print integers only" )
{
    std::ostringstream oss;
    printInts( oss, 1, 2, 3, 4 );
    CHECK_EQ( oss.str(), "1234" );

    // can't compile
    //  printInts("asd", 1, 'a');

    static_assert( std::is_same_v< void, decltype( printInts( oss, 1, 2 ) ) > );
}