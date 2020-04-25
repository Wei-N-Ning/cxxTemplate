#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <vector>
#include <optional>
#include <initializer_list>

// std::optional
// read: https://en.cppreference.com/w/cpp/utility/optional
// None is expressed as std::optional{}

template<typename T>
class Stack {
public:
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
