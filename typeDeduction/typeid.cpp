//
// Created by weining on 1/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iostream>

template<typename T>
class TypeTester {};

// mentioned in complete guide L5323
// typeid() prints a string that describes the type of the expression passed
// to it.
// the c++ standard doesn't actually say the name() must return something meaningful

// this requires TypeTester<T> to be fully instantiated (and T is known to me)
// this can not replace my usual debugging approach where T is unknown to me
TEST_CASE ("") {
    TypeTester<int> tt;
    // typeid() returns a type_info struct
    // /usr/include/c++/9/typeinfo
    std::cout << typeid(tt).name() << std::endl;
}
