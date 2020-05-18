//
// Created by weining on 18/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <type_traits>
#include <iterator>

// inspired by c++ template: complete guide L/16466
// also curious to see how std::iterator_traits<> is implemented,
// here is me replicating the mechanism of std::iterator_traits<> and
// showing how tag-dispatching can be built on top of it

struct Forward {};
struct Random{};

struct ForIter {
    using category = Forward;
};

struct RandAccessIter {
    using category = Random;
};

template<typename...>
using VoidT = void;

template<typename Iterator, typename = VoidT<>>
struct Traits {
    using category = Forward;
};

template<typename Iterator>
struct Traits<Iterator, VoidT<typename Iterator::category>> {
    using category = typename Iterator::category;
};

// any template can take advance of Traits, which is a total function,
// to implement tag-dispatching:
template<typename T>
void impl(T t, Forward) {}

template<typename T>
void impl(T t, Random) {}

template<typename T>
void entry_point(T t) {
    impl(t, Traits<T>::category());
}

TEST_CASE ("") {
    static_assert(
        std::is_same_v<Traits<ForIter>::category, Forward>
    );

    static_assert(
        // specialized
        std::is_same_v<Traits<RandAccessIter>::category, Random>
    );

    static_assert(
        // fallback to the default/general
        std::is_same_v<Traits<int>::category, Forward>
    );
}
