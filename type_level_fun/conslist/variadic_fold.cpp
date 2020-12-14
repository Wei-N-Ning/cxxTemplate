//
// Created by weining on 2/5/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// complete guide L7766

// right fold
// (pack op .. op value)
// left fold
// (value op .. op pack)

// NOTE:
// see also variadic_match_many/insert_many.cpp for how to use an
// arbitrary function with the l-fold or r-fold idiom
// if I look at Ts... args with my haskell glasses, it looks like the classic (x:xs)
// and the parameter pack fold becomes:
// f x op fold xs
// f: is the arbitrary function that may take other arguments not part of the
//    parameter pack
// x: is the head
// fold xs: is the recursion:
// fold (hd:tl)
// f hd op fold tl
// NOTE: op can be `,` the comma operator, meaning that "I don't want to reduce
// any results but process multiple actions of the same kind"
// see variadic_insert_many.cpp for the multi-push-back example
// see also: modern c++ programming cookbook L3261
// it also uses the head..tail terminology to express the argument expansion

template< typename F, typename B, typename A, typename... Ts >
B
left_accumulate( F f, const B& init, const A& a, Ts... xs )
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return init + left_accumulate( f, a, xs... );
}

template< typename F, typename B, typename A >
B
left_accumulate( F f, const B& init, const A& a )
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return f( init, a );
}

template< typename F, typename B, typename A, typename... Ts >
B
right_accumulate( F f, const B& init, const A& a, Ts... xs )
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return right_accumulate( f, f( a, init ), xs... );
}

template< typename F, typename B, typename A >
B
right_accumulate( F f, const B& init, const A& a )
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return f( a, init );
}

// see: modern c++ programming cookbook L3346
// left folding
// unary form: (... op pack)
//  (pack1 op pack2) op ...) op packn
// binary form: (init op ... op pack)
//  (((init op pack1) op pack2) op ...) op packn
// right folding
// unary form: (pack op ...);
//  pack1 op (... op(packn-1 op packn))
// binary form: (pack op ... op init);
//  pack1 op (... op (packn-1 op (packn op init)))

// L3393
// fold expressions work with all overloads for the supported binary operators,
// but DO NOT WORK WITH ARBITRARY BINARY FUNCTIONS
// workaround is to use a wrapper type

template< typename F, typename B, typename A, typename... Ts >
B
left_fold( F f, const B& init, const A& a, Ts... xs )
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return ( ( init + a ) + ... + xs );
}

TEST_CASE( "foldl and foldr" )
{
    auto o1 =
      left_accumulate( []( auto init, auto x ) -> decltype( init ) { return init + x; },
                       1,
                       2,
                       3.0,
                       4.0,
                       5.0 );
    CHECK_EQ( o1, 15 );

    auto o1fold =
      left_fold( []( auto init, auto x ) -> decltype( init ) { return init + x; },
                 1,
                 2,
                 3.0,
                 4.0,
                 5.0 );
    CHECK_EQ( o1fold, 15 );

    auto o2 =
      right_accumulate( []( auto x, auto init ) -> decltype( init ) { return init + x; },
                        1,
                        2,
                        3.0,
                        4.0,
                        5.0 );
    CHECK_EQ( o2, 15 );
}
