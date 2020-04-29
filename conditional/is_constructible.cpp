//
// Created by weining on 30/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <type_traits>

// complete guide L4144
// is_convertible: requires that the types are implicitly convertible
// is_constructible: allow explicit conversions

class X {
public:
    X() = default;
    explicit X(int) {};  // X is constructible from int
};

template<typename T>
using EnableIfCanCreateX = std::enable_if_t<std::is_constructible_v<X, T>>;

template<typename T, typename = EnableIfCanCreateX<T>>
X f(T x) {
    return X{x};
}

TEST_CASE ("") {
    X x(1);  // make sure the explicit conversion works
    CHECK_EQ(x, f(1));  // take advantage of the conditional template
}
