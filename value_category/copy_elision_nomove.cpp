//
// Created by weining on 15/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <iostream>

// C++17 in detail P/23
// copy elision if even T does not have move-assignment operator (or is not movable at
// all)

// for the complete value category. read:
// https://en.cppreference.com/w/cpp/language/value_category

// prvalue describes initialization; glvalue describes location

// this basically makes move-assignment operator less useful, because T x = someFactoryOfT()
// will initialize x with the value(s) that (were originally going to) construct the
// prvalue directly

// c++ 17 the complete guide P/43

// prvalue: pure rvalue
// xvalue: expiring value
// glvalue: generalized lvalue

// glvalues: expressions for locations of objects or functions
// prvalues: expressions for initializations

// c++ 17 then introduces a new term, called materialization (of a temporary),
// for the moment a prvalue becomes a temporary object. Thus a temporary
// materialization conversion is a prvalue-to-xvalue conversion.

// any time a prvalue validly appears where a glvalue (lvalue or xvalue) is
// expected, a temporary object is created and initialized with the prvalue
// (recall that prvalues are primarily "initializing values"), and the prvalues
// is replaced by an xvalue designating the temporary

// with this modification, that prvalues are no longer objects but are instead
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// expressions that can be used to initialize objects, the required copy
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// elision makes perfect sense
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^
// we only pass an initial value (expression) around that is sooner or later
// materialized to initialize an object

// NOTE:
// copy-elision is also documented in cxxPerformance with a different focus.

struct T
{
    // the only way to construct T is via this ctor
    T( int, int, int )
    {
        std::cout << "constructing T" << '\n';
    }

    // T is not movable
    T( T&& other ) = delete;
};

T
createT( int a, int b, int c )
{
    return T( a, b, c );
}

T
wrappedCreateT( int a, int b, int c )
{
    return createT( a, b, c );
}

TEST_CASE( "expect copy elision even if T is not movable" )
{
    // x is initialized by calling T's ctor directly, even when there are two functions
    // wrapping T's ctor.
    auto x = wrappedCreateT( 1, 2, 3 );
    CHECK( &x );
}