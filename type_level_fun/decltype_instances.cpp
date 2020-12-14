//
// Created by wein on 25/04/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <utility>
#include <string>
#include <iterator>
#include <type_traits>

// source:
// https://devblogs.microsoft.com/cppblog/how-to-use-class-template-argument-deduction/
// mentioned by
// C++ templates: complete guide L/2000

template< typename T, typename P >
struct Item
{
    T a;
    P b;

    Item() = default;

    Item( const T&, const P& ){};
};

TEST_CASE( "deduce class template parameter from constructor arguments" )
{
    std::pair p( 1729, "taxicab" );
    static_assert( std::is_same_v< decltype( p ), std::pair< int, const char* > > );

    Item i1{ 1, 'a' };
    static_assert( std::is_same_v< decltype( i1 ), Item< int, char > > );
    Item i2{ 'a', 1.0 };
    static_assert( std::is_same_v< decltype( i2 ), Item< char, double > > );
}

template< typename T >
struct MyVec
{
    template< typename Iter >
    MyVec( Iter, Iter )
    {
    }
};

template< typename Iter >
MyVec( Iter, Iter ) -> MyVec< typename std::iterator_traits< Iter >::value_type >;

template< typename A, typename B >
struct MyAdvancedPair
{
    template< typename T, typename U >
    MyAdvancedPair( T&&, U&& )
    {
    }
};

template< typename X, typename Y >
MyAdvancedPair( X, Y ) -> MyAdvancedPair< X, Y >;

TEST_CASE( "test drive" )
{
    int* ptr = nullptr;
    MyVec v( ptr, ptr );
    static_assert( std::is_same_v< decltype( v ), MyVec< int > > );
    MyAdvancedPair adv( 1729, "taxicab" );
    static_assert(
      std::is_same_v< decltype( adv ), MyAdvancedPair< int, const char* > > );
}