//
// Created by weining on 30/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <vector>

// complete guide L5156
// 1. specify the return type with the trailing return type syntax
// 2. decltype
// 3. formulate all expressions that must be valid
// 4. define an object of the real return type
//
// the operand of the decltype construct is a comma-separated list of exprs,
// so that the last expr T::size_type() yields a value of the desired return
// type (which decltype uses to convert into the return type)
// before the last comma, we have the expressions that must be valid, which
// in this case is just `t.size()`
// the cast of the expression to void is to avoid the possibility of a user-
// defined comma operator overloaded for the type of the expression
// NOTE: this pattern does not check whether t.size() really returns T::size_type

// UPDATE:
// on L15152, when explaining the SFINAE-based trait algorithms, it shows again
// how to implement a "has-member-x" validation mechanism.
// for the sake of clarity I put all the examples in /predicates
template< typename T >
auto
len( const T& t )
  -> decltype( ( void )( t.size() ), ( void )( t.empty() ), typename T::size_type() )
{
    return t.size();
}

class X
{
};

TEST_CASE( "test function template" )
{
    std::allocator< int > alloc{};
    // no matching function - sfinae works
    // len(alloc);
    std::vector< int > xs{ 1, 2, 3 };
    CHECK_EQ( 3, len( xs ) );

    X x{};
    // no matching function
    // len(x);
}
