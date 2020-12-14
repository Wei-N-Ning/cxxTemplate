//
// Created by weining on 20/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

// c++ template: complete guide L19535
// compile-time value (CTValue)
// this follows the research done on typelist and related algorithms.

// L19533
// using CTValue template, we can express a typelist containing integer values

// c++ template: complete guide L20697
// 42_c yields CTValue<int, 42>
// see Boost.Hana, a metaprogramming library suited for computations on both
// types and values

// see also
// c++ template: complete guide L18574
// use constexpr to compute ratio (such as chrono time units)

template<typename T, T Value>
struct CTValue {
    static constexpr T value = Value;
};

template<typename... Elements>
struct TypeList {
};

using Primes = TypeList<
    CTValue<int, 2>, CTValue<int, 3>, CTValue<int, 5>,
    CTValue<int, 7>, CTValue<int, 11>
>;

template<typename T1, typename T2>
struct MultiplyT;

template<typename T, T Value1, T Value2>
struct MultiplyT<CTValue<T, Value1>, CTValue<T, Value2>> {
    using Type = CTValue<T, Value1 * Value2>;
};

template<typename T1, typename T2>
using Multiply = typename MultiplyT<T1, T2>::Type;

// L19566
// introduce an alias template CTTypeList that provides a homogeneous list
// of values
// (NOTE the position of ... - it indicates that there are multiple CTValue<>)
template<typename T, T... Values>
using CTTypeList = TypeList<CTValue<T, Values>...>;

// more concise definition of Primes
using Primes_ = CTTypeList<int, 2, 3, 5, 7, 11>;

// use ValueList for better error message
// it is still a homogeneous list of values of T
template<typename T, T... Values>
struct ValueList {
};

using PrimeValues = ValueList<int, 2, 3, 5, 7, 11>;

TEST_CASE ("test mult") {
    static_assert(
        std::is_same_v<
            CTValue<int, 15>,
            Multiply<CTValue<int, 3>, CTValue<int, 5>>
        >
    );
}
