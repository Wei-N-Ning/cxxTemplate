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

// c++ 17 the complete guide P/248
// shows how to roll my own version of this trait
// see also cxxTemplate/design/variable_template for the complete concept of
// of variable template - the building block the empowers this trait

// T( std::declval< T >() )
// is T( T&& )
template< typename T >
struct has_nothrow_move_ctor : std::bool_constant< noexcept( T( std::declval< T >() ) ) >
{
};

template< typename T >
constexpr bool has_nothrow_move_ctor_v = has_nothrow_move_ctor< T >::value;

struct Item
{
    Item( Item&& ) // may throw exception
    {
    }
};

TEST_CASE( "has nothrow move ctor" )
{
    static_assert( has_nothrow_move_ctor_v< int > );
    static_assert( !has_nothrow_move_ctor_v< Item > );
}
