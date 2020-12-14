//
// Created by weining on 29/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// complete guide: L/3786
// to achieve the functionality for variable(mutable), constant(immutable) and
// movable we have to program all three cases
class X
{
};

enum class Case
{
    Variable,
    Constant,
    Movable,
};

Case
g( X& )
{
    return Case::Variable;
}

Case
g( const X& )
{
    return Case::Constant;
}

Case
g( X&& )
{
    return Case::Movable;
}

auto
f( X& x )
{
    return g( x );
}

auto
f( const X& x )
{
    return g( x );
}

auto
f( X&& x )
{
    // complete guide L/3824
    // move semantics is not passed through
    return g( std::move( x ) );
}

TEST_CASE(
  "invoke specific overloaded version of g() and f(), in the case of const & and &&" )
{
    X x1;
    const X x2;
    CHECK_EQ( Case::Variable, g( x1 ) );
    CHECK_EQ( Case::Constant, g( x2 ) );
    CHECK_EQ( Case::Movable, g( X{} ) );

    CHECK_EQ( Case::Variable, f( x1 ) );
    CHECK_EQ( Case::Constant, f( x2 ) );
    CHECK_EQ( Case::Movable, f( X{} ) );
}

// C++11 introduces a special rules for perfect forwarding parameters
template< typename T >
auto
pf( T&& val )
{
    // complete guide L3835
    // std::move() has no template parameter and triggers move semantics for the
    // passed argument; while std::forward<>() forwards potential move semantic
    // depending on a passed template argument
    // don't assume that T&& for a template parameter T behaves as X&& for a
    // specific type X, different rules apply!
    // T must really be the name of a template parameter.
    // typename T::iterator && is just an rvalue reference, not a forwarding
    // reference
    return g( std::forward< T >( val ) );
}

TEST_CASE( "function template perfect forwarding (no specific overloading)" )
{
    X x1;
    const X x2;
    CHECK_EQ( Case::Variable, pf( x1 ) );
    CHECK_EQ( Case::Constant, pf( x2 ) );
    CHECK_EQ( Case::Movable, pf( X{} ) );
}
