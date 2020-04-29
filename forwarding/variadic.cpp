//
// Created by weining on 29/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// inspired by the comments from complete guide L/3879
// perfect forwarding can also be used with variadic templates
// also read: https://stackoverflow.com/questions/45041538/variadic-templates-with-forward-reference-and-operator

// here are my experiments:
// rvalue can become const ref or rvalue-ref
// lvalue can become value or mut-ref
// const lvalue can become const ref
enum class Case {
    Value,
    Variable,
    Constant,
    Movable,
};

Case f(int &x, char &c, double &d) {
    return Case::Variable;
}

Case f(const int &x, const char &c, const double &d) {
    return Case::Constant;
}

Case f(int &&x, char &&c, double &&d) {
    return Case::Movable;
}

template<typename... Ts>
decltype(auto) pf(Ts&&... xs) {
    return f(std::forward<Ts>(xs)...);
}

TEST_CASE ("") {
    int i = 1;
    char c = '1';
    double d = 1.0;
    CHECK_EQ(Case::Variable, pf(i, c, d));
    CHECK_EQ(Case::Constant, pf(i, c, 32.0));
    CHECK_EQ(Case::Movable, pf(1, std::move(c), 32.0));
}
