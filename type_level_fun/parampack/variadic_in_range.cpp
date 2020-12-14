//
// Created by weining on 2/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// c++ stl cookbook P/38
// check if one variable is within some specific range

template< typename T, typename... Ts >
auto
within( T min, T max, Ts... hd )
{
    return ( ( min <= hd && hd <= max ) && ... );
}

TEST_CASE( "value is within conslist" )
{
    CHECK( within( 1, 10, 2, 3, 4, 5 ) );
    CHECK( within( 1, 10, 2.0, 3u, 4.0f, 5ll ) );
}
