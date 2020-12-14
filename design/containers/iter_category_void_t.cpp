//
// Created by weining on 18/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <type_traits>
#include <iterator>

// inspired by c++ template: complete guide L/16466

// also curious to see how std::iterator_traits<> is implemented,
// here is me replicating the mechanism of std::iterator_traits<> and
// showing how tag-dispatching can be built on top of it

// this show how to write generic algorithms that work with a family of types (type class);
// std::void_t<> (or my own version VoidT) is the KEY to make this happen

struct Forward
{
};
struct Random
{
};

struct ForIter
{
    using category = Forward;
};

struct RandAccessIter
{
    using category = Random;
};

// I should use std::void_t<>
template< typename... >
using VoidT = void;

// this is the base condition - it matches any T
template< typename Iterator, typename = VoidT<> >
struct Traits
{
    using category = Forward;
};

// this is the specialized condition - it only matches a T that provides ::category type
// member
template< typename Iterator >
struct Traits< Iterator, VoidT< typename Iterator::category > >
{
    using category = typename Iterator::category;
};

// any template can take advance of Traits, which is a total function,
// to implement tag-dispatching:
template< typename T >
int
impl( T t, Forward )
{
    return 0;
}

template< typename T >
int
impl( T t, Random )
{
    return 1;
}

template< typename T >
int
entry_point( T t )
{
    return impl( t, typename Traits< T >::category() );
}

TEST_CASE( "type-level assertion and runtime assertion" )
{

    // type-level assertions
    static_assert( std::is_same_v< Traits< ForIter >::category, Forward > );

    static_assert(
      // specialized
      std::is_same_v< Traits< RandAccessIter >::category, Random > );

    static_assert(
      // fallback to the default/general
      std::is_same_v< Traits< int >::category, Forward > );

    // runtime assertions, testing the dispatching logic
    CHECK_EQ( 1, entry_point( RandAccessIter() ) );
    CHECK_EQ( 0, entry_point( ForIter() ) );
}
