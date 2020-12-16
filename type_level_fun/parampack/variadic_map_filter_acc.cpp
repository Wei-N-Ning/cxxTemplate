//
// Created by weining on 16/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iostream>

template< typename Map, typename Filter, typename Acc, typename T, typename... Ts >
T
mapFilterAcc( Map map, Filter filter, Acc acc, T&& init, T&& head, Ts&&... tail )
{
    // check parameter pack length:
    // https://stackoverflow.com/questions/2770474/how-to-find-the-length-of-a-parameter-pack
    // also inspired by the example on this page:
    // https://en.cppreference.com/w/cpp/language/parameter_pack
    T x = map( std::forward< T >( head ) );
    if constexpr ( sizeof...( tail ) == 0 )
    {
        return filter( x ) ? acc( std::forward< T >( init ), x )
                           : std::forward< T >( init );
    }
    else
    {
        return filter( x ) ? acc( x,
                                  mapFilterAcc( map,
                                                filter,
                                                acc,
                                                std::forward< T >( init ),
                                                std::forward< Ts >( tail )... ) )
                           : mapFilterAcc( map,
                                           filter,
                                           acc,
                                           std::forward< T >( init ),
                                           std::forward< Ts >( tail )... );
    }
}

TEST_CASE( "map filter accumulate variadic recursion" )
{
    // NOTE: this is not using the variadic fold expression which only
    // works with an operator (one of the 32 operators);
    // If I want to provide my own pure functions, I need to use pattern
    // match and recursion
    auto map = []( const int& x ) { return x + 1; };
    auto filter = []( const int& x ) { return x > 2; };
    auto acc = []( const int& a, const int& b ) { return a + b; };
    auto o = mapFilterAcc( map, filter, acc, 0, 1, 2, 3, 4 );
    // the result of map()                               2  3  4  5
    // the result of filter()                               ^  ^  ^
    CHECK_EQ( 12, o );
}

struct Item
{
    int value{ 0 };

    explicit Item( int x )
      : value{ x }
    {
    }
};

TEST_CASE( "perfect forwarding no copying" )
{
    auto map = []( const Item& x ) { return Item{ x.value + 1 }; };
    auto filter = []( const Item& x ) { return x.value > 2; };
    auto acc = []( const Item& a, const Item& b ) { return Item{ a.value + b.value }; };
    auto o = mapFilterAcc(
      map, filter, acc, Item{ 0 }, Item{ 1 }, Item{ 2 }, Item{ 3 }, Item{ 4 } );
    CHECK_EQ( o.value, 12 );
}