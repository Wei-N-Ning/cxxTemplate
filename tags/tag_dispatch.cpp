//
// Created by weining on 17/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>
#include <string_view>

// c++ template: complete guide L14397

namespace Lock {
    template<typename T>
    int getQuantity(T val, std::true_type) { return 10; }

    template<typename T>
    int getQuantity(T val, std::false_type) { return -10; }
}

template<typename T>
int getLockedQuantity(T val) {
    // the robustness of tag-dispatching relies on how many type does
    // is_same<T, int> support
    // std::variant() could be a better option here
    return Lock::getQuantity(val, std::is_same<T, int>{});
}

TEST_CASE ("substr") {
    using namespace std;

    string s{"A123"};
    CHECK_EQ(s.substr(1, std::string::npos), "123");
}

TEST_CASE ("") {
    CHECK_EQ(-10, getLockedQuantity('c'));
    CHECK_EQ(10, getLockedQuantity(1));
}
