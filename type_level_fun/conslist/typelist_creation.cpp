//
// Created by weining on 20/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <type_traits>

// c++ template: complete guide L19646
// this follows the researches on typelist, CTValue and their algorithms
// pack expansions can be a useful mechanism for offloading the work of typelist
// iteration to the compiler

template< typename... Elements >
struct TypeList
{
};

template< typename List >
struct IsEmptyT
{
    static constexpr bool value = false;
};

template<>
struct IsEmptyT< TypeList<> >
{
    static constexpr bool value = true;
};

// L19657
// transform naturally lends itself to the use of a pack expansion, because
// it is applying the same operation to each of the elements in the list
template< typename List,
          template< typename T >
          typename MetaFun,
          bool Empty = IsEmptyT< List >::value >
struct TransformT;

template< typename... Elements, template< typename T > typename MetaFun >
struct TransformT< TypeList< Elements... >, MetaFun, false >
{
    using Type = TypeList< typename MetaFun< Elements >::Type... >;
    //                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //         apply the metafun to each type in the Elements and form a
    //          a typelist from the results
    // there is no need to handle the base case explicitl (empty list)
};

template< typename T >
struct AddConstT
{
    using Type = const T;
};

template< auto... Values >
struct ValueList
{
};

template< typename List, typename Indices >
struct SelectT;

// TODO: implement it
template< typename List, unsigned... Indices >
struct SelectT< List, ValueList< Indices... > >
{
};

TEST_CASE( "construct type list using explicit types" )
{
    using TL = TypeList< char, int >;
    using TLconst = TransformT< TL, AddConstT >::Type;
    static_assert( std::is_same_v< TLconst, TypeList< const char, const int > > );
}

// C++ 17 in detail P/58
// deduce type-list from compile-time values
// however this approach has some limitation:
// - not all the value types are supported (e.g. float/double is not)
// - the value must be known to the compiler (can not be any dynamically created
//   value)

template< auto... vs >
struct HeterogeneousValueList
{
    using Types = TypeList< decltype( vs )... >;
};

TEST_CASE( "create type list on the fly" )
{
    using MyList = HeterogeneousValueList< 1, ( int* )nullptr, 'c', 1l, 1u >;
    static_assert( std::is_same_v< TypeList< int, int*, char, long, unsigned >, MyList::Types > );
}
