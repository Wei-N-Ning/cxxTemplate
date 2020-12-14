//
// Created by weining on 17/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <type_traits>
#include <utility>

// c++ template: complete guide L15622
// Pair's move ctor can throw exceptions when the move operations of either
// T1 or T2 can throw

template< typename T1, typename T2 >
class Pair
{
public:
    Pair( Pair&& other ) noexcept( std::is_nothrow_move_constructible_v< T1 >&&
                                     std::is_nothrow_move_constructible_v< T2 > )
      : first( std::forward< T1 >( other.first ) )
      , second( std::forward< T2 >( other.second ) )
    {
    }

private:
    T1 first;
    T2 second;
};

struct Foo
{
};

TEST_CASE( "can T's move-ctor throw exception" )
{
    static_assert( std::is_nothrow_move_constructible_v< Pair< int, char > >, "Pair" );
    static_assert( std::is_nothrow_move_constructible_v< Foo >, "Foo" );
}
