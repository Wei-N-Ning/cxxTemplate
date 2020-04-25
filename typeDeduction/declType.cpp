//
// Created by wein on 5/26/18.
//
// source: EMC++ Item 3 P23

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <cassert>
#include <vector>

void logAccess() {
    ;
}

#define MUTABLE (10)
#define CONSTANT (-10)
#define INDEX (1)

struct Dumm {
    Dumm() :m_value(MUTABLE), m_value_const(CONSTANT) {};
    int &operator[](int index) {
        return m_value;
    }
    int operator[](int index) const {
        return m_value_const;
    }
    int m_value;
    int m_value_const;
};

template<typename Container, typename Index>
decltype(auto) access(Container &&c, Index i) {
    logAccess();
    return std::forward<Container>(c)[i];
}

TEST_CASE ("test_returnTypes_lvalueContainer") {
    std::vector<int> v{0, 0, 0};

    // classic operator[], returns a mutable ref
    int &elem = v[2];
    elem = 10;

    // use access() template
    // CLion does not seem to understand decltype(auto)
    access(v, 2) = 1;

    CHECK_EQ(1, v[2]);
}

TEST_CASE ("test_returnTypes_rvalueContainer") {
    Dumm d;
    const Dumm &dRef = d;
    const Dumm dConst;

    CHECK_EQ(MUTABLE, access(Dumm(), INDEX));
    CHECK_EQ(MUTABLE, access(d, INDEX));
    CHECK_EQ(CONSTANT, access(dRef, INDEX));
    CHECK_EQ(CONSTANT, access(dConst, INDEX));

    auto createConstDumm = []() -> const Dumm {
        const Dumm tmp;
        return tmp;
    };
    CHECK_EQ(CONSTANT, access(createConstDumm(), INDEX));
}

TEST_CASE ("test_variables") {
    struct Some {
    };

    Some some;
    const Some &someRef = some;
    auto other = someRef;
    decltype(auto) shouldBeRef = someRef;

    CHECK((std::is_same<Some, decltype(other)>::value));
    CHECK((std::is_same<const Some &, decltype(shouldBeRef)>::value));
}

template<typename A, typename B>
auto do_max(const A &a, const B &b) -> decltype(a > b ? a : b) {
    return a > b ? a : b;
}

// c++ templates guide L/1058
// there are 3 ways to deduce the result type from a non-deterministic computation
// 1. return type parameter, requires explicit (partial) template instantiation
// 2. let the compiler guess, hence decltype()
// 3. use a common type
// my take is:
// explicit is better than implicit
template<typename t>
class TypeTester;

TEST_CASE ("deduce return type of max(a, b)") {
    char c = '\45';
    double d = 12.7;
    int i = 12;
    // auto result = do_max(i, c); -> return type is int, even though the c (\45) wins
    auto result = do_max(i, d);  // return type is double as 12.7 wins
    CHECK(std::is_same<decltype(result), double>::value);
}

// inspired by c++ templates guide L/1136
// the example here ensures no reference is returned; however what if
// I want to write more concise code like below and do return a mutable
// reference ?
template<typename T>
T&& do_max_ref(T&& a, T&& b) {
    return a > b ? a : b;
}

TEST_CASE ("max(a, b) return the original reference") {
    int a = 10, b = 1100;
    ++do_max_ref(a, b);
    CHECK_EQ(1101, b);

    const int c = 1, d = 2;
    // ++do_max_ref(c, d);  -> returns a const value
}
