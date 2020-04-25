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
