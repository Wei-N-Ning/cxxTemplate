//
// Created by weining on 22/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <type_traits>

// c++ 17 the complete guide P/112
// using fold expression to create type-level function

template< typename T, typename... Ts >
constexpr bool
isHomo( T, Ts... )
{
    return ( ... && std::is_same_v< T, Ts > );
}

TEST_CASE( "is homogeneous value level function" )
{
    static_assert( isHomo( 1, 1, 1, 1 ) );
    static_assert( !isHomo( 1, 1, 'a' ) );
}

template< typename T, typename... Ts >
struct IsHomo
{
    // note how to export the type level computation result
    // the && operator will short-circuit! (unlike the compile-time if
    // statement)
    static constexpr bool value = ( ... && std::is_same_v< T, Ts > );
};

TEST_CASE( "is homogeneous type level function" )
{
    static_assert( IsHomo< int, int, decltype( 19 ), decltype( 1 + 1 ) >::value );
    static_assert( !IsHomo< int, decltype( std::declval< std::string >() ) >::value );
}