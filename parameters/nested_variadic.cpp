//
// Created by weining on 1/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// complete guide L7109
// although a type parameter pack (variadic param) can not be expanded in its
// own parameter clause, nested templates can create a similar good solution

template<typename... Ts>
struct ArgList {
    template<Ts... vals>
    struct Vals {

    };
};

TEST_CASE ("") {
    ArgList<int, char, char>::Vals<3, 'x', 'y'> v;
    // ^^^ type level          ^^^ term/data level
    using TypeLevel = ArgList<int, char, char>;
    using TermLevel = TypeLevel::Vals<3, 'x', 'y'>;
    TermLevel x;
}
