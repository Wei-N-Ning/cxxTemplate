//
// Created by weining on 17/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <utility>
#include <type_traits>

// c++ template: complete guide L15330
// use the technique for other kinds of expressions and even combine multiple
// expressions, for example we can test whether given T1 and T2, there is a
// suitable < operator defined

struct Foo{};

template<typename...>
using VoidT = void;

template<typename, typename, typename = std::void_t<>>
struct HasLessT : std::false_type {};

template<typename T1, typename T2>
struct HasLessT<
    T1, T2,
    std::void_t<decltype(std::declval<T1>() < std::declval<T2>())>
> : std::true_type {};

// borrowed from the impl of std::is_same_v<>
template<typename T1, typename T2>
inline constexpr bool has_less_v = HasLessT<T1, T2>::value;

TEST_CASE ("") {
    static_assert(has_less_v<int, int>);
    static_assert(! has_less_v<Foo, int>);
    static_assert(has_less_v<std::pair<int, int>, std::pair<int, int>>);
}
