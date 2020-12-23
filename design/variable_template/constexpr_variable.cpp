//
// Created by weining on 23/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <type_traits>
#include <iostream>

// c++ 17 the complete guide
// as a type trait extension, each standard type trait has a corresponding
// variable template:

template< typename T >
constexpr bool is_const_v = std::is_const< T >::value;

// as type traits are evaluated at compile time, you can use the result at
// compile time (if constexpr)

// c++ 17 the complete guide P/246
// example of using the boolean constexpr variable to conditionally specialise
// a class template
template< typename T, bool = std::is_pointer_v< T > >
struct C
{
    using type = T;
};

template< typename T >
struct C< T, true >
{
    using type = std::remove_pointer_t< T >;
};

// c++ 17 the complete guide P/247
// boolean traits usually inherit from std::true_type (or false_type); and a
// specialized version inherits from the opposite;
// therefore it models the general cases (yielding true or false) for any T,
// and also the special cases where T meets certain condition (yielding the
// opposite boolean value)
//
// P/248
// in c++ 17, there is a new bool_constant<> trait that can combine these
// two branches into one, if you are able to formulate the compile-time
// expression as a boolean condition
//
// with this understanding and the new bool_constant<> feature, take a look
// at type_level_fun/conditional
//    type_level_fun/metafunctions
// and see if I can improve these traits/metafunctions

template< typename T >
struct IsLargerThanInt : std::bool_constant< ( sizeof( T ) > sizeof( int ) ) >
{
};

template< typename T >
constexpr bool is_larger_than_int_v = IsLargerThanInt< T >::value;

TEST_CASE( "use boolean constexpr variable template" )
{
    const auto x{ 1 };
    static_assert( is_const_v< decltype( x ) > );

    static_assert( std::is_same_v< int, C< int >::type > );
    static_assert( std::is_same_v< int, C< int* >::type > );

    static_assert( is_larger_than_int_v< long long > );
}

TEST_CASE( "using an integral constexpr variable" )
{
    static_assert( 0 == std::extent_v< decltype( 1 + 1 ) > );

    // extent yields the size of the dimension of a raw array
    static_assert( 5 == std::extent_v< int[ 10 ][ 5 ], 1 > );
}
