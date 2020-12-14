//
// Created by weining on 18/5/20.
//

// mentioned in c++ template: complete guide L16132
//
// a function that takes a T and returns a T
// std::conditional_t() (IfThenElse()) is a good example

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <type_traits>

template<typename T>
struct RParamT {
    using Type =
        std::conditional_t<
            sizeof(T) <= 2 * sizeof(void *) &&
            std::is_trivially_constructible_v<T> &&
            std::is_trivially_move_constructible_v<T>,
            T,
            const T &
        >;
};

template<typename T>
using RParam = typename RParamT<T>::Type;

template<typename T>
struct TT;

TEST_CASE ("") {
    static_assert(
        std::is_same_v<int, RParam<int>>
        );

    static_assert(
        std::is_same_v<int const (&)[3], RParam<int[3]>>
        );
}
