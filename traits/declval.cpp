//
// Created by weining on 17/5/20.
//

// c++ template: complete guide L/14500
// to get the value type even if the type itself can not be
// default-constructed
// the expression declval<T>() produces a value of type T without requiring
// a default ctor
// this function template is intentionally left undefined because it is only
// meant to be used within decltype, sizeof or some other context where no
// definition is ever needed

// NOTE:
// with the power of declval(), I can just write the expression naturally
// without using a temporary lambda

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <type_traits>
#include <utility>

struct Foo {
    Foo() = delete;
    explicit Foo(int) {}

    template<typename T>
    Foo operator+(const T &other) { return *this; }

    template<typename T>
    friend Foo operator+(const T &other, const Foo &self) { return self; }
};

struct Bar {
    Bar() = delete;
};

TEST_CASE ("") {
    using namespace std;

    static_assert(
        is_same_v<decltype(Foo(1) + 1), Foo>
    );
    static_assert(
        is_same_v<decltype(1 + Foo(1)), Foo>
    );

    auto op = [](Foo foo, int i) { return foo + i; };
    static_assert(
        is_same_v<Foo, result_of_t<decltype(op)(Foo, int)>>
    );
    // with the power of declval, I can just write the expression naturally
    // without using a temporary lambda like above
    static_assert(
        is_same_v<Foo, decltype(declval<Foo>() + declval<int>())>
    );
}