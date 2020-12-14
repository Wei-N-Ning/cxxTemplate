//
// Created by weining on 29/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

enum class Case
{
    Red,
    Blue,
    Pod,
};

static Case state{ Case::Red };

// complete guide L4007
// if sizeof(T) > 4 is false, this definition is ignored
// if true, its type member yields a type
// - the type is void is no second template argument is passed
// - otherwise type is the second template argument
// in this case if T satisfy sizeof(T) > 4, the resulting type is void, e.g.
// void f() { ::state = Case::Blue ; }
template< typename T >
// typename std::enable_if<(sizeof(T) > 4)>::type
// complete guide L4019
// since C++14, can write:
typename std::enable_if_t< ( sizeof( T ) > 4 ) >
f()
{
    ::state = Case::Blue;
}

template< typename T >
Case
ff( typename std::enable_if< ( sizeof( T ) > 4 ), T >::type x )
{
    return Case::Blue;
}

// complete guide L4042
// the common way to use std::enable_if<> is to use an additional function
// template argument with a default value
template< typename T, typename = std::enable_if_t< ( sizeof( T ) > 4 ) > >
Case
fff( T x )
{
    return Case::Blue;
}

// inspired by: modern c++ programming cookbook L3956
// use a type alias to de-clutter the template parameter list
template< typename T >
using EnableIfPod = typename std::enable_if_t< std::is_pod_v< T > >;
template< typename T, typename = EnableIfPod< T > >
Case
needPod( T x )
{
    return Case::Pod;
}

// L4054,
// make the requirement/constraint more explicit, you can define your own name
// for it using an alias template
template< typename T >
using EnableIfSizeGT4 = std::enable_if_t< ( sizeof( T ) > 4 ) >;

template< typename T, typename = EnableIfSizeGT4< T > >
Case
f4( T x )
{
    return Case::Blue;
}

struct X
{
    int a;
    int b;
    int c;
};

// complete guide L3998
// enable_if<> to ignore function templates under certain compile-time
// conditions
TEST_CASE( "test drive" )
{
    CHECK_EQ( Case::Red, state );
    f< long long >();
    // won't type check: enable_if<> yields false
    // f<char>();
    CHECK_EQ( Case::Blue, state );
    CHECK_EQ( Case::Blue, ff< long long >( 1ll ) );
    CHECK_EQ( Case::Blue, fff< long long >( 1ll ) );
    CHECK_EQ( Case::Blue, f4< long long >( 1ll ) );

    CHECK_EQ( Case::Pod, needPod( X{} ) );
}