//
// Created by weining on 20/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <type_traits>

// c++ template: complete guide L19721
// a list modelled after Lisp's cons cell:
// data List T = List T (List T)
//             | Nil

// TODO:
// implement type function:
// InsertionSort

struct Nil
{
    using tail = Nil;
};

template< auto hd, typename Tl = Nil >
struct Cons
{
    static constexpr decltype( hd ) head = hd;
    using tail = Tl;
};

template< auto hd >
using Singleton = Cons< hd >;

template< typename L, typename = std::void_t< decltype( L::head ) > >
inline constexpr decltype( L::head ) Front = L::head;

template< auto hd, typename L, typename = std::void_t< typename L::tail > >
struct PushFrontImpl
{
    using type = Cons< hd, L >;
};

template< auto hd, typename L >
using PushFront = typename PushFrontImpl< hd, L >::type;

template< typename L, typename = std::void_t<> >
struct PopFrontImpl
{
    using type = Nil;
};

// this feels redundant

// template< typename L >
// struct PopFrontImpl< L, std::enable_if< std::is_same_v< L, Nil > > >
//{
//    using type = Nil;
//};

template< typename L >
struct PopFrontImpl< L, std::void_t< decltype( L::head ), typename L::tail > >
{
    using type = typename L::tail;
};

template< typename L >
using PopFront = typename PopFrontImpl< L >::type;

template< typename L, typename = std::void_t<> >
struct IsEmptyImpl : public std::true_type
{
};

template< typename L >
struct IsEmptyImpl< L, std::void_t< decltype( L::head ) > > : public std::false_type
{
};

template< typename L >
inline constexpr bool IsEmpty = IsEmptyImpl< L >::value;

TEST_CASE( "construct ConsList" )
{
    using Empty = Nil;
    using Singleton = Cons< 113, Nil >;
    // L19733
    // List does not have to be homogeneous
    using L = Cons< 113, Singleton >;

    static_assert( Front< L > == 113 );

    // is empty
    static_assert( IsEmpty< Empty > );
    static_assert( !IsEmpty< Singleton > );
    static_assert( !IsEmpty< L > );
}

TEST_CASE( "push front" )
{
    using L1 = PushFront< 12, Singleton< 133 > >;
    static_assert( Front< L1 > == 12 );

    using L2 = PushFront< 'a', L1 >;
    static_assert( Front< L2 > == 'a' );
}

TEST_CASE( "pop front" )
{
    using L1 = PushFront< 12, Singleton< 133 > >;
    using L2 = PushFront< 'a', L1 >;
    using L3 = PopFront< L2 >;
    static_assert( std::is_same_v< PopFront< Nil >, Nil > );
    static_assert( std::is_same_v< L1, L3 > );
}

// c++ 17 the complete guide P/118
// also briefly touched this type-level data structure,

template< auto... xs >
struct HeteroValueList
{
};

template< auto head, decltype( head )... tail >
struct HomoValueList
{
};

TEST_CASE( "hetero and homo type level list" )
{
    HeteroValueList< 3, 'a', true > xs;
    HomoValueList< 3, 3, 3, 3 > ys;

    // can not compile
    // HomoValueList< true, 'a' > os;
}