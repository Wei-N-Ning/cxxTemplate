//
// Created by weining on 2/5/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// complete guide L7766

// right fold
// (pack op .. op value)
// left fold
// (value op .. op pack)

// NOTE:
// op can not be a function that takes two arguments;
// I have to write a recursive function and handle the base case properly

template<typename F, typename B, typename A, typename... Ts>
B left_accumulate(F f, const B &init, const A &a, Ts... xs) {
    return init + left_accumulate(f, a, xs...);
}

template<typename F, typename B, typename A>
B left_accumulate(F f, const B &init, const A &a) {
    return f(init, a);
}

template<typename F, typename B, typename A, typename... Ts>
B right_accumulate(F f, const B &init, const A &a, Ts... xs) {
    return right_accumulate(f, f(a, init), xs...);
}

template<typename F, typename B, typename A>
B right_accumulate(F f, const B &init, const A &a) {
    return f(a, init);
}

template<typename F, typename B, typename A, typename... Ts>
B left_fold(F f, const B &init, const A &a, Ts... xs) {
    return ((init + a) + ... + xs);
}


TEST_CASE ("") {
    auto o1 = left_accumulate(
        [](auto init, auto x) -> decltype(init) {
            return init + x;
        },
        1,
        2, 3.0, 4.0, 5.0
    );
    CHECK_EQ(o1, 15);

    auto o1fold = left_fold(
        [](auto init, auto x) -> decltype(init) {
            return init + x;
        },
        1,
        2, 3.0, 4.0, 5.0
    );
    CHECK_EQ(o1fold, 15);

    auto o2 = right_accumulate(
        [](auto x, auto init) -> decltype(init) {
            return init + x;
        },
        1,
        2, 3.0, 4.0, 5.0
    );
    CHECK_EQ(o2, 15);
}
