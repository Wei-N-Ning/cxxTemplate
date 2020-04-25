#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <vector>
#include <iterator>
#include <numeric>
#include <optional>
#include <initializer_list>

// std::optional
// read: https://en.cppreference.com/w/cpp/utility/optional
// None is expressed as std::optional{}

template<typename T>
class Stack {
public:
    // c++20 concept can make it part of the language
    static_assert(std::is_default_constructible<T>::value,
        "class Stack required default-constructible element");

    Stack() = default;
    Stack(std::initializer_list<T> il) : vec(il) {}

    // c++ templates guide L/1508
    // copy and assignment can omit parameter T
    Stack(const Stack &other) = default;
    Stack& operator=(const Stack &other) = default;

    void push(const T &elem) { vec.push_back(elem); }

    std::optional<T> pop() {
        if (vec.empty()) {
            return std::optional<T>{};
        }
        std::optional<T> v{vec.back()};
        vec.pop_back();
        return v;
    }

    std::optional<T> top() {
        return vec.empty() ? std::optional<T>{} : std::optional<T>{vec.back()};
    }

    auto empty() { return vec.empty(); }

    // following the guide in C++ templates: complete guide L1716
    // I got this warning:
    // Clang-Tidy: Redundant 'operator<<' declaration
    // after searching around I found a post that suggested inline
    // definition:
    // see: https://stackoverflow.com/questions/4039979/some-compiler-errors-concerning-an-overloaded-operator-on-a-template-in-c
    // A common pattern for friend free functions in templates is defining the function in place:
    friend std::ostream &operator<<(std::ostream &os, const Stack<T> &st) {
        std::copy(st.vec.cbegin(), st.vec.cend(), std::ostream_iterator<T>{os, " "});
        return os;
    }

private:
    std::vector<T> vec;
};

TEST_CASE ("push pop") {
    Stack<int> s{1, 2};
    CHECK_FALSE(s.empty());
    CHECK_EQ(s.pop(), 2);

    // also test the assign op
    auto s2 = s;
    CHECK_EQ(s2.top(), 1);
    CHECK_EQ(s2.pop(), 1);
    CHECK(s2.empty());

    // also test the assign op: the original copy is untouched
    CHECK_FALSE(s.empty());
}

TEST_CASE ("effect") {
    Stack<int> s;
    CHECK_FALSE(s.pop().has_value());
    s.push(1);
    s.push(10);
    if (auto v = s.pop(); v.has_value()) {
        CHECK_EQ(v, 10);
    }
}

class C {
public:
    C() = delete;
};

TEST_CASE ("the concept constraint") {
    // this will trigger the static_assert
    // Stack<C> s;

    // this is fine: array is default constructible
    Stack<std::array<int, 1>> s;
}

TEST_CASE ("friend function template example") {
    Stack<int> s{1, 2, 3};
    std::cout << s << std::endl;
}

// C++ templates: complete guide L/1981
template<typename T>
using StackFamily = Stack<T>;
TEST_CASE ("use type alias to express a family of types") {
    StackFamily<char> sch{'i', 'd', 'd', 'q', 'd'};
    std::cout << sch << std::endl;
}

template<typename T>
class TypeTester;

// C++ templates: complete guide L/1994
// alias templates are useful to define shortcuts for types that are
// members of class templates
template<typename T>
using VecIt = typename std::vector<T>::const_iterator;
TEST_CASE ("use type alias to ") {
    auto f = [](VecIt<int> start, VecIt<int> end) {
        return std::accumulate(start, end, 0);
    };

    std::vector<int> v{1, 2, 3};
    // similarly if f() needs mutable iterator, the alias templates
    // must express that: typename std::vector<T>::iterator
    CHECK_EQ(6, f(v.cbegin(), v.cend()));

    // L/2015: C++14 this is standard library shortcuts for all
    // type traits that yield a type
    using T = std::add_const_t<int>;
    T t{1};
    // TypeTester<T> tt;  t is of const int
}
