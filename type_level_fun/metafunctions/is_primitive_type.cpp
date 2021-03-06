//
// Created by weining on 17/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <type_traits>

// c++ template: complete guide L15817
// note: STL uses term "fundamental_type" to refer to the built-in types,
// I used the term "primitive type"

// also mentioned in
// mastering c++ programming L1285
// fundamental types: int, double, char, void
//  compound types: ptr, array, class
// std::is_compound_v<Point>;

struct Foo
{
};

TEST_CASE( "std::is_fundamental (check if T is a primitive/fundamental type)" )
{
    using namespace std;

    // see c++ template: complete guide L15827 for a complete list of
    // fundamental/primitive types
    // NOTE: pointer is not primitive type
    static_assert( is_fundamental_v< int >, "int" );
    static_assert( !is_fundamental_v< int* >, "int ptr" );
    static_assert( !is_fundamental_v< Foo >, "Foo" );
}

TEST_CASE( "is T a compound type" )
{
    static_assert( std::is_compound_v< Foo > );
}
