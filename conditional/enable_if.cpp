//
// Created by weining on 29/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

enum class Case {
    Red,
    Blue,
};

static Case state{Case::Red};

// complete guide L4007
// if sizeof(T) > 4 is false, this definition is ignored
template<typename T>
typename std::enable_if<(sizeof(T) > 4)>::type
f() {
    ::state = Case::Blue;
}

struct X {
    int a;
    int b;
    int c;
};

// complete guide L3998
// enable_if<> to ignore function templates under certain compile-time conditions
TEST_CASE ("") {
    CHECK_EQ(Case::Red, state);
    f<long long>();
    // won't type check: enable_if<> yields false
    // f<char>();
    CHECK_EQ(Case::Blue, state);
}