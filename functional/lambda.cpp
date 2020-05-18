#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <functional>
#include <vector>

TEST_CASE ("lambda") {
    std::function<double(std::vector<double>)> func = 
        [](std::vector<double> vd) -> double {
            double result = 0;
            for (const auto& elem : vd) {
                result += elem;
            }
            return result;
        };
    // c++ template: complete guide L18033
    // lambda can be converted to a std::function<> object, to be
    // used with value semantics
    // std::function<> is a generalized form of a C++ function pointer, providing
    // the same fundamental operations
    const std::function<double(std::vector<double>)> f = func;
    CHECK_EQ(3, func({1, 2}));
    CHECK_EQ(3, f({1, 2}));
}

// complete guide: L3433
// generic lambda (c++14) is a shortcut for member (operator()) template
// don't have to define a default-constructed object with an operator() method
TEST_CASE ("generic lambda") {
    auto f = [] (auto x, auto y) {
        return x + y;
    };
    CHECK_EQ(f(1u, 2u), 3u);
    CHECK_EQ(f(std::string{"there"}, std::string{"is"}), std::string{"thereis"});
}
