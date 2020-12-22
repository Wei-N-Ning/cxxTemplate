//
// Created by weining on 30/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

enum class Case
{
    Red,
    Blue,
};

// complete guide L/5198
// c++17 introduces a compile-time if statement, to decide whether
// to apply the then part or the else part
// the fact that the code is not instantiated means that only
// the first translation phase (the definition time) is performed,
// which checks for correct syntax and names that don't depend on
// template parameters
template< typename... Ts >
Case
f( Ts... args )
{
    if constexpr ( sizeof...( args ) > 1 )
    {
        return Case::Blue;
    }
    else // DO NOT omit the else branch
    {
        return Case::Red;
    }
}

// c++ 17 complete guide P/97

// some important notes on constexpr if-statement (compile-time if-statement)

//  - it does not short-circuit; use nested constexpr if-statement to model
//    the chain of requirements
//  - both if-branch and else-branch matters! do not omit the else-branch (use
//    runtime if-statement's fall-over mechanism)
//  - it can cause the return type of the function template differs

TEST_CASE( "test drive" )
{
    CHECK_EQ( Case::Blue, f( 1, 'c', nullptr ) );
    CHECK_EQ( Case::Red, f() );
    CHECK_EQ( Case::Red, f( 1 ) );
}

// c++ 17 complete guide P/99
// compile-time if statement can model tag dispatching efficiently, in one
// function template.
// however, the set of overloaded functions gives you best-match semantics
// whereas the implementation with compile-time if gives your the first-match
// semantics;
// to this end, I should think of the order of the if-conditions (place the
// best match condition at the front)

// c++ 17 complete guide P/100
// compile-time if with initialization
// I can even do value-comparison, provided that both operands are constexpr