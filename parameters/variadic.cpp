//
// Created by wein on 5/27/18.
//

// used this in wkou code base
// recall EMC++ variadic parameter and perfect forwarding

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <cassert>
#include <tuple>
#include <string>
#include <cstring>
#include <iostream>

template<typename... Ts>
void foo(Ts&&... params) {
    std::tuple<Ts...> t{params...};
    constexpr std::size_t sz = std::tuple_size<decltype(t)>::value;
    assert((4 == sz));
}

int bar_impl(const std::string& i_s) {
    return 1;
}

int bar_impl(int i, double d) {
    return 2;
}

// verify that the output pointer stays an output pointer
int bar_impl(const std::string& i_s, std::string* o_str) {
    *o_str = i_s;
    return 3;
}

// verify that the output reference stays an output reference
int bar_impl(const std::string& i_s, std::string& o_str) {
    o_str = i_s;
    return 4;
}

// EMC++ P167
// "perfect forwarding (constructor)" P180
// std::forward<decltype(params)>(params)...
// without effective/perfect forwarding - i.e. if the wrap takes
// arguments by value, bar(Ts... params) - it creates temporary objects 
// from the references (const or not) then passes the temporary objects 
// to the impl functions
template<typename... Ts>
int bar(Ts&&... params) {
    return bar_impl(std::forward<decltype(params)>(params)...);
}

TEST_CASE ("") {
    foo(1, 2.3, "asd", true);
    std::string name("13");
    CHECK_EQ(1, bar(name));
    CHECK_EQ(2, bar(1, 1.0));
    
    // output parameter is a pointer
    std::string receiver;
    CHECK_EQ(3, bar(name, &receiver));
    CHECK_EQ(0, strcmp(name.c_str(), receiver.c_str()));
    
    // output parameter is a mutable reference
    std::string answer;
    CHECK_EQ(4, bar(name, answer));
    CHECK_EQ(0, strcmp(name.c_str(), answer.c_str()));
}

// complete guide: L2548
// `Ts.. args` is a function parameter pack
template<typename... Ts>
std::ostream &do_print(std::ostream &os, Ts... args) {
    // L2638
    // use fold expression
    // compute the result of `using a binary op` over all the arguments of a
    // parameter pack (with an optional init value)
    return (os << ... << args);
}

// complete guide L2536
// without the bottom case to stop the recursion the compiler will throw an error:
// error: no matching function for call to ‘recur_print()’
// the bottom case MUST BE SEEN by the compiler before the definition of the recursive
// template
void recur_print() {}

// complete guide L2760
// note how to use reference with variadic template
// reference ensures NO decay and NO copy
// this enables perfect forwarding
template<typename T, typename... Ts>
void recur_print(T head, const Ts&... tail) {
    // L2611
    // C++ 11 also introduced a new sizeof...() op for variadic templates
    // it expands to the number of elements a parameter pack contains
    // L2624
    // this approach (of doing conditional branching based on sizeof...())
    // doesn't work because in general both branches of all if statements
    // are instantiated (runtime decision vs compile time decision)
    // the call to the non-existing function is still instantiated, leading
    // to a compilation error
    // use the compile-time if expression, added to the language since c++17
    std::cout << head << "(" << sizeof...(Ts) << ")";
    recur_print(tail...);
}

template<typename T>
class TypeTester;

TEST_CASE ("test variadic function template") {
    do_print(std::cout, 1, " , ", 2u, " , ", 'c') << std::endl;
    do_print(std::cout) << std::endl;

    recur_print(1, 2u, 'c');
}

template<typename... Ts>
auto do_sum(Ts... args) {
    // c++ templates: complete guide L/2650
    // left fold
    // return (... + args);  // ((s1 + s2) + s3) ...
    // right fold
    return (args + ...);
}

TEST_CASE ("fold expression") {
    // s is of type long (widest type)
    auto s = do_sum(1u, 1l, '1', true);
    CHECK(std::is_same_v<decltype(s), long>);

}
