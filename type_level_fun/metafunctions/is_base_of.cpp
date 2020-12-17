//
// Created by weining on 5/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iterator>
#include <list>
#include <unordered_map>
#include <vector>

// inspired by master c++ stl P/30

template< typename It >
int
dis( It from, It to )
{
    if constexpr ( std::is_base_of_v< std::random_access_iterator_tag, It > )
    {
        return to - from;
    }
    else
    {
        return std::distance( from, to );
    }
}

TEST_CASE( "is base (class) of" )
{
    std::vector< int > v{ 1, 2, 3, 4 };
    CHECK_EQ( -4, dis( v.cend(), v.cbegin() ) );
    CHECK_EQ( 4, dis( v.cbegin(), v.cend() ) );

    std::list< int > l{ 1, 2, 3, 4 };
    CHECK_EQ( 4, dis( l.cbegin(), l.cend() ) );

    std::unordered_map< int, int > um{ {
                                         1,
                                         1,
                                       },
                                       { 2, 2 },
                                       { 3, 3 },
                                       { 4, 4 } };
    CHECK_EQ( 4, dis( um.cbegin(), um.cend() ) );
}
