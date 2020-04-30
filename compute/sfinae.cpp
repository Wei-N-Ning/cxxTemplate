//
// Created by weining on 30/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// complete guide L5021
// sfinae: pronounced sfee-nay
// substitution failure is not an error
// the language rules instead say that candidates with such substitution problems
// are simply ignored
// L5134
// sfinae has become a verb
// we sfinae out a function: to apply the sfinae mechanism to ensure that function
// templates are ignored for certain constraints by instrumenting the template code
// to result in invalid code for these constraints
// example: std::thread sfinae out a case to enforce copy/move ctor

#include <utility>
#include <vector>

enum class Case {
    Red,
    Blue,
};

template<typename T, std::size_t N>
std::pair<std::size_t, Case> len(T(&)[N]) {
    return std::make_pair(N, Case::Red);
}

template<typename T>
std::pair<typename T::size_type, Case> len(const T &xs) {
    // template instantiation won't detect if T does not have a member function
    // named size(), will result in a compile-time error
    // I can use has_method_trait (see trait/has_method) to do reflection-like
    // checking at compile time
    return std::make_pair(xs.size(), Case::Blue);
}

TEST_CASE ("") {
    int arr[3] = {};
    // complete guide L5041
    // when passing a raw array or string literals, only the function template for
    // raw arrays matches
    // T::size_type results in substitution error therefore this template is ignored
    auto [sz1, c1] = len(arr);
    CHECK_EQ(c1, Case::Red);

    auto [sz2, c2] = len("iddqd");
    CHECK_EQ(c2, Case::Red);

    auto [sz3, c3] = len(std::vector<int>{});
    CHECK_EQ(c3, Case::Blue);
}

// a function that always matches but has the worst match: match with ellipsis ...
// in overload resolution
std::size_t len(...) {
    return 0;
}

TEST_CASE ("black hole function") {
    CHECK_EQ(0, len('1'));
    CHECK_EQ(0, len(12));
    CHECK_EQ(0, len(std::make_pair(1, 'c'), 1, 2, nullptr));
}
