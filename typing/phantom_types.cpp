//
// Created by weining on 2/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// inspired by complete guide L7225
// this section explains function template type-deduction rules, and which type of parameter can not be
// deduced from the call arguments; this remind me the concept of phantom type in haskell (read:
// the proof of the departed ghost), a non-participating type parameter that influences a dispatching logic
// further down

enum class Case {
    Red,
    Blue,
    Invalid,
};

template<Case color, typename Val>
struct Pill {
    explicit Pill(Val v): val{v} {}
    Val val{};
};

template<Case color, typename Val, template<Case, typename> typename PillT>
Val f(PillT<color, Val> p) {
    if constexpr (color == Case::Red) {
        return p.val + 10;
    } else if constexpr(color == Case::Blue) {
        return p.val -10;
    }
    return p.val;
}

TEST_CASE ("") {
    // dispatching computation per the color enum (the phantom)
    CHECK_EQ(f(Pill<Case::Red, double>(1.0)), 11.0);
    CHECK_EQ(f(Pill<Case::Blue, int>(2)), -8);
    CHECK_EQ(f(Pill<Case::Invalid, char>('\0')), '\0');
}
