//
// Created by weining on 28/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// complete guide L3503
// a useful application of variable templates is to define variables that
// represent members of class templates
template<typename T>
struct is_signed {
    // constexpr must be a static member
    static constexpr bool value = std::numeric_limits<T>::is_signed;
};

TEST_CASE ("") {
    // since C++17. the standard library uses the technique of variable
    // templates to define shortcuts for all type traits in the standard
    // library that yield a bool value
    // ..._v
    CHECK(is_signed<int>::value);
    CHECK_FALSE(is_signed<bool>::value);
}
