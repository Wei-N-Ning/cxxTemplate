//
// Created by weining on 30/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

enum class Case {
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
template<typename... Ts>
Case f(Ts... args) {
    if constexpr(sizeof...(args) > 1) {
        return Case::Blue;
    }
    return Case::Red;
}

TEST_CASE ("") {
    CHECK_EQ(Case::Blue, f(1, 'c', nullptr));
    CHECK_EQ(Case::Red, f());
    CHECK_EQ(Case::Red, f(1));
}
