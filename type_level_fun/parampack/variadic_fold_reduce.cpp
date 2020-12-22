//
// Created by weining on 22/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// c++ 17 the complete guide P/110
// combining hash functions

// this example shows a lighter way to implement the `reduce` (or accumulate)
// with fold expression;

// I can go full-on with the mini-framework documented in variadic_map_filter_acc
// but it's too verbose;

// the key in this example is how to model mutability (aggregating the results
// from individual steps) without relying on the 32 built-in operators or a
// custom Accumulator function object.

TEST_CASE( "" )
{
    ;
}
