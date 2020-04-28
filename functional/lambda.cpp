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
    CHECK_EQ(3, func({1, 2}));
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
