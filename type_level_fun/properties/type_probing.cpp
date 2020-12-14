//
// Created by weining on 13/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iostream>
#include <memory>
#include <type_traits>
#include <variant>

// FP in c++ P/228
// decltype() is quite useful;
// it enables me to probe the type of an expression - recall that in Scala's
// everything is an expression

// this has a serious limitation: decltype(Element()) will return the wrong
// result for variant<T, Q> - see the right answer below
template< typename Collection >
bool
canBeFoldedIfEmpty( const Collection& xs )
{
    using Element = std::remove_cv< decltype( *xs.begin() ) >;
    if constexpr ( std::is_same_v< decltype( Element() ), Element > )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// FP in c++ P/229
// decltype vs std::declval()
// declval<T>() takes a type T and pretends to create an instance of that type
// so you can use it in metafunctions when you need values instead of types -
// which is often the case when you use decltype

using Result = std::variant< std::string, std::vector< int > >;

// FP in c++ P/230
// a helper type-level function that works for both default-constructable
// types and those that are not.
// however in the production code, I should just use the ::value_type member
// instead.
template< typename Collection >
using contained_type_t = std::remove_cv_t<
  std::remove_reference_t< decltype( *std::begin( std::declval< Collection >() ) ) > >;

TEST_CASE( "probe container element type" )
{
    std::vector< int > xs;
    CHECK( canBeFoldedIfEmpty( xs ) );

    std::vector< Result > rs;
    constexpr bool canBeDefaultConstructed =
      std::is_same_v< decltype( std::declval< std::vector< Result > >() ),
                      std::vector< Result > >;
    static_assert( !canBeDefaultConstructed, "." );

    static_assert( std::is_same_v< contained_type_t< std::vector< Result > >, Result >,
                   "." );
}

// FP in c++ P/235
// checking type properties at compile-time
// it ignores all its parameters and always returns void
// it is useful because it can be evaluated only IF the types passed in are
// valid;
// if they are not, it triggers SNIFAE and the compiler will ignore the
// definition
// c++17 provides void_t out of box
// P/236
// void_t can also be used to check expressions with a little help from
// decltype and std::declval<> - see the example is_iterable<>
template< typename... >
using void_t = void;

// FP in c++ P/235
// define the general case: assume an arbitrary type does not have a nested
// value_type member
template< typename Col, typename = void_t<> >
struct has_value_type_member : std::false_type
{
};

// define the specialized case: (emphasizing the word `specialized`)
// do not re-define the struct template
template< typename Col >
struct has_value_type_member< Col, void_t< typename Col::value_type > > : std::true_type
{
};

template< typename Col >
constexpr bool has_value_type_member_v = has_value_type_member< Col >::value;

TEST_CASE( "check if type (or type member) exists" )
{
    static_assert( std::is_same_v< void, void_t< std::vector< int >::value_type > > );

    // see the definition of std::is_same_v<>
    // it is a constexpr boolean
    static_assert( has_value_type_member_v< std::vector< int > > );
    static_assert( !has_value_type_member_v< int > );
}

template< typename T, typename = void_t<> >
struct is_iterable : std::false_type
{
};

template< typename T >
struct is_iterable< T,
                    void_t< decltype( *std::begin( std::declval< T >() ) ),
                            decltype( *std::end( std::declval< T >() ) ) > >
  : std::true_type
{
};

template< typename T >
constexpr bool is_iterable_v = is_iterable< T >::value;

TEST_CASE( "if type is iterable" )
{
    static_assert( is_iterable_v< std::vector< int > > );
    static_assert( !is_iterable_v< int > );
}