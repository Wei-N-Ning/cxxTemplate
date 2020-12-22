//
// Created by weining on 22/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <array>
#include <iostream>

// c++ 17 the complete guide P/121
// you can also use auto as template parameters with variable templates
// for example
template< typename T, auto N >
std::array< T, N > arr;

// this might occur in a header file, defines a variable template arr,
// parameterised for the type of elements and dimension

// in each translation unit, all usages of arr<int, 10> share the same global
// object, while arr<long, 10> and arr<int, 10u> would be different global
// objects, again both usable in all translation units.

// NOTE:
// this can be a quick way to provide parameterised globals

// the same storage applies to non-array variable such as int or struct

TEST_CASE( "global array template" )
{
    auto p1 = ( int* )( &arr< int, 10 > );
    auto p2 = ( double* )( &arr< double, 10 > );

    std::cout << p1 << '\n' << p2 << '\n';
    std::cout.flush();
}