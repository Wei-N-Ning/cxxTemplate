//
// Created by weining on 2/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// c++ stl cookbook P/36
// a function that tells whether some range contains at least one of the values
// provided as variadic parameters

#include <vector>
#include <tuple>
#include <algorithm>

template<typename R,
         typename... Ts,
         typename Require = std::enable_if_t<(sizeof...(Ts) > 0)>>
auto matches(R &&range, Ts... ts) {
    return (std::count(std::begin(range), std::end(range), ts) + ...);
}

TEST_CASE ("") {
    auto m1 = matches(std::vector<int>{1, 2, 3, 4, 5, 6, 7}, 1, 3);
    CHECK_EQ(m1, 2);

    // won't compile because of the requirement, which triggers SFINAE when
    // the parameter pack is empty
    // auto m2 = matches(std::vector<int>{1, 2, 3, 4, 5, 6, 7});
    auto m2 = matches(std::vector<int>{1, 2, 3, 4, 5, 6, 7}, '9');
    CHECK_EQ(0, m2);

    // won't compile because std::begin/end does not accept tuple nor pair
    // auto m3 = matches(std::make_tuple(1, 'c', 3.14, nullptr), nullptr);
    // auto m3 = matches(std::make_pair(1, nullptr), nullptr);
    int arr[10] = {1};
    auto m3 = matches(arr, 1);
    CHECK_EQ(1, m3);
    CHECK_EQ(1, matches("iddqd", 'i'));
}
