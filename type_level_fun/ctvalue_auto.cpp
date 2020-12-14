//
// Created by weining on 20/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

// c++ template: complete guide L19629
// in C++17. CTValue can be improved by using a single, deducible nontype
// param: auto

template<auto Value>
struct CTValue {
    static constexpr auto value = Value;
};

template<auto... Values>
struct ValueList {};

using CTString = ValueList<'i', 'd', 'd', 'q', 'd'>;
using Primes = ValueList<2, 3, 5, 7, 11>;

// L19630
// (beware)
// a nontype parameter pack with deduced type allows the types of each
// argument to differ
static int x = 12;
using Haystack = ValueList<1, &x, 'a', false>;

TEST_CASE ("") {
    ;
}
