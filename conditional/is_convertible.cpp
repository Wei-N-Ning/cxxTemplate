//
// Created by weining on 30/4/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <type_traits>
#include <string>

// inspired by complete guide L/4081

enum class Case {
    Red,
    Blue,
};

template<typename T>
using IsConvertibleToStdString = std::enable_if_t<std::is_convertible_v<T, std::string>>;

template<typename T,
         typename = IsConvertibleToStdString<T>>
Case f(const T &x) {
    return Case::Blue;
}

TEST_CASE ("") {
    CHECK_EQ(Case::Blue, f("asd"));

    // does not have a definition
    // f(1);
}

