//
// Created by weining on 8/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <sstream>
#include <string>
#include <tuple>
#include <functional>

// c++ stl cookbook P/351
//

template<typename X, typename... Xs>
void do_print(std::ostream &os, const X &x, const Xs &...xs) {
    os << x;
    // c++ stl cookbook P/155
    // we can not just write os.operator<<(xs) ... using the ... notation
    // what we can do is constructing a list of values using std::initializer_list,
    // which has a variadic constructor,
    // an expression such as return std::initializer_list<int>{f(xs)...} does the
    // job
    // to fix the return value mismatch problem it does the following things to
    // achieve that:
    // 1. it does not return the init list, but it casts the whole expr to void
    // 2. within the init expr, it wraps f(xs)... into an (f(xs), 0)... expr
    //    which leads to the return value being thrown away, while 0 is put into
    //    the init list
    // 3. f(x) in the (f(xs), 0)... expr is again cast to void, so the return
    //   value is really not processed anywhere if it has any
    (void)std::initializer_list<int>{
        ((os << "" <<xs), 0)...
    };
}

// this works too
template<typename ... Xs>
void print_(std::ostream &os, const Xs &... xs) {
    std::cout << __PRETTY_FUNCTION__  << std::endl;
    (void)std::initializer_list<int>{
        ((os << "" <<xs), 0)...
    };
}

template<typename... Ts>
std::ostream &operator<<(std::ostream &os, const std::tuple<Ts...> &tu) {
    auto prt = [&os](const auto &... xs) {
        print_(os, xs...);
    };
    // std::apply works with tuple:
    // https://en.cppreference.com/w/cpp/utility/apply
    // template <class F, class Tuple>
    // constexpr decltype(auto) apply(F&& f, Tuple&& t);
    std::apply(prt, tu);
    return os;
}

TEST_CASE ("") {
    using namespace std;
    using namespace std::string_literals;

    auto items = {
        make_tuple("e1m1", "doom1"s, 1992),
        make_tuple("e4m2", "ultimate doom"s, 1994),
    };

    stringstream ss;
    for (const auto &i : items) {
        ss << i << ", ";
    }
    CHECK_EQ("e1m1doom11992, e4m2ultimate doom1994, ", ss.str());
}