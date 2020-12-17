//
// Created by wein on 4/9/18.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// practice the type-level predicate: roll my own is_bool<> predicate
// the steps are:
// define a (base) template that works for any T;
// specialize this template for the selected T(s) that meet my criteria;
// optionally provided a type alias acting as a type-level function (the _v<> pattern in
// STL)

template< typename T >
struct is_bool
{
    static const bool value = false;
};

template<>
struct is_bool< bool >
{
    static const bool value = true;
};

template< typename T >
int
sut( T t )
{
    if ( is_bool< T >::value )
    {
        return 101;
    }
    return -10;
}

TEST_CASE( "test_isBool()" )
{
    CHECK_EQ( -10, sut( 101 ) );
    CHECK_EQ( 101, sut( false ) );
}
