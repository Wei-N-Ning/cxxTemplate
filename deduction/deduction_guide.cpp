//
// Created by weining on 22/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <array>
#include <type_traits>

// c++17 the complete guide P/84
// NOTE:
// c++ 17 introduces the `deduction guide` which looks like type signature in
// haskell;
// it can make my life easier (omitting the explicit instantiation) but it
// has a contraption around decaying and ref types;
// I may revisit this part later, but I don't think it is immediately useful.

// c++ 17 the complete guide P/86
// std::array<> provides a deduction guide that can deduce the array dimension
// by the size of the IL

TEST_CASE( "deduce array dimension" )
{
    std::array arr{ 1, 2, 3, 4, 5 };
    static_assert( std::is_same_v< decltype( arr ),
                                   // 5 is deduced by a fold expression
                                   std::array< int, 5 > > );
}

template< size_t Dim, typename Element >
struct Item
{
    explicit Item( Element... )
    {
    }
};

template< typename Head, typename... Tail >
Item( Head, Tail... )
  -> Item< ( 1 + sizeof...( Tail ) ),
           // both enable_if and sizeof() uses the fold expression
           std::enable_if_t< ( std::is_same_v< Head, Tail > && ... ), Head > >;

TEST_CASE( "deduce custom dimension" )
{
    // replicating the std::array<> deduction guide for a custom type
    // (this technique can be useful to model graphic types such as
    // wt's float3, float4 ....); wt was using boost's type_trait library
    Item i1{ 1, 2, 3 };
    Item i2{ 1.0, 2.0, 3.0, 4.0 };

    static_assert( std::is_same_v< decltype( i1 ), Item< 3, int > > );
    static_assert( std::is_same_v< decltype( i2 ), Item< 4, double > > );
}