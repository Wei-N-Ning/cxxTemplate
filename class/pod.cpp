//
// Created by wein on 25/04/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>

template<typename T>
struct Item {
    std::string name = {};
    T value;
};

TEST_CASE ("") {
    Item<std::string> item{"map", "e1m1"};
}

