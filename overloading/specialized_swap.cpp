//
// Created by weining on 18/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <array>

// c++ template: complete guide L16419
// algorithm specialization
template<typename T>
void swap_(T &x, T &y) {
    T tmp{x};
    x = y;
    y = tmp;
}

static int state = 0;

// partial ordering rules:
// the compiler will pick the more specialized (and, therefore more efficient)
// function template when it is applicable (for std::array<T, sz>)
// and fallback to the more general (potentially less efficient) algorithm
// when the more specialized version is not applicable
template<typename T, std::size_t sz>
void swap_(std::array<T, sz> &x, std::array<T, sz> &y) {
    x.swap(y);

    // side effects
    state = 1;
}

TEST_CASE ("") {
    using namespace std;
    array<int, 3> arr1{1, 2, 3};
    array<int, 3> arr2{10, 20, 30};
    swap_(arr1, arr2);
    CHECK_EQ(state, 1);
}
