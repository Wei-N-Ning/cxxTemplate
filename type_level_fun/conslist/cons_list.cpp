//
// Created by weining on 20/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// c++ template: complete guide L19721
// a list modelled after Lisp's cons cell:
// data List T = List T (List T)
//             | Nil

// TODO:
// implement type function:
// Singleton<>
// Front
// PushFront
// PopFront
// IsEmpty
// InsertionSort

struct Nil
{
};

template< typename HeadT, typename TailT = Nil >
struct Cons
{
    using Head = HeadT;
    using Tail = TailT;
};

TEST_CASE( "construct ConsList" )
{
    using Empty = Nil;
    using Singleton = Cons< int, Nil >;
    // L19733
    // List does not have to be homogeneous
    using L = Cons< int, Singleton >;
}
