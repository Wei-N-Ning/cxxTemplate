//
// Created by weining on 2/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <set>
#include <vector>

// c++ stl cookbook P/37
// a similar example to variadic_match_many

template< typename T, typename... Ts >
bool
insert_all( std::set< T >& set, Ts... hd )
{
    // why set.insert returns a pair,
    // see: http://www.cplusplus.com/reference/set/set/insert/
    return ( set.insert( hd ).second && ... );
}

// c++ stl P/40
// use `,` as the binary operator to discard the individual return value
// because there is not any return value
// the intention is to just perform the actions of the same kind (the effect),
// without folding the actual result
// it also works nicely with an emtpy parameter pack because the comma op has
// an implicit identity element, void(), which translates to do-nothing
template< typename T, typename... Ts >
void
push_back_all( std::vector< T >& v, Ts... hd )
{
    ( v.push_back( hd ), ... );
}

TEST_CASE( "conslist as variadic function parameters" )
{
    std::set s{ 1, 2, 3, 1 };
    CHECK( insert_all( s, 10, 11, 12 ) );

    CHECK_FALSE( insert_all( s, 1, 1, 2 ) );

    std::vector< int > v{ 1, 2, 3 };
    push_back_all( v, 10, 20, 30 );
    CHECK_EQ( std::vector< int >{ 1, 2, 3, 10, 20, 30 }, v );
}
