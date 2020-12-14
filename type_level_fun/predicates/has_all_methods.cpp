//
// Created by weining on 17/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iterator>
#include <vector>
#include <type_traits>
#include <utility>

// c++ template: complete guide L15385
// (this is a continuation of has_member.cpp; this one extends the technique
// to cover multiple requirements)
// NOTE, this chapter also introduces another method that uses generic lambda
// to express the member requirement.

// also mentioned in FP in C++, meta-programming chapter
// std::void_t is a good example of SNIFAE;
// the example below also demonstrates the value of decltype and std::declval<> which
// returns the type of a given expression; this makes C++ equally capable as Scala in
// regards to type-level programming.

template< typename... >
using VoidT = void;

template< typename, typename = std::void_t<> >
struct HasIterMethods : std::false_type
{
};

template< typename T >
struct HasIterMethods< T,
                       std::void_t< decltype( std::declval< T >().begin() ),
                                    decltype( std::declval< T >().end() ),
                                    decltype( std::declval< T >().cbegin() ),
                                    decltype( std::declval< T >().cend() ),
                                    typename T::difference_type,
                                    typename T::iterator > > : std::true_type
{
};

template< typename T >
inline constexpr bool has_iter_methods_v = HasIterMethods< T >::value;

struct Foo
{
};

TEST_CASE( "has_iter_methods<> predicate" )
{
    static_assert( !has_iter_methods_v< Foo >, "Foo does not have iterator" );
    static_assert( has_iter_methods_v< std::vector< int > >, "vector" );
    static_assert( has_iter_methods_v< std::vector< bool > >, "vector of bool" );
}
