#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <cassert>

// source
// exceptional P74
//

#include <iostream>

template<typename T, typename R>
R getValue(const T& t) {
    return t.m_value;
};

class SUT {
    int m_value = -123;
    friend decltype(m_value) getValue<const SUT&, decltype(m_value)>(const SUT& sut);
};

// complete guide L7836
// node that the class template (referred to be the friend) must be visible
// at the point
template<typename T>
class Node {
public:
    explicit Node(T&& v): v{v} {}
    // to verify that operator<< indeeds take const ref (instead of copying)
    Node(const Node &other) = delete;
    Node &operator=(const Node &other) = delete;

    // Option 1. declare a function template friend
    // Beware that, using T_ to avoid name-clashing with the class template's parameter T
    // template<typename T_>
    // friend std::ostream &operator<<(std::ostream &, const Node<T_> &);

    // Option 2. define a non-template friend function
    // another option is to mark the **definition** of a function friend
    inline friend std::ostream &operator<<(std::ostream &os, const Node<T> &node) {
        return os << "Node<" << node.v << ">";
    }
private:
    T v{};
};

// this T is independent to the class template parameter T above
// this T will resolve to the class template argument at the call site
//template<typename T>
//std::ostream &operator<<(std::ostream &os, const Node<T> &node) {
//    return os << "Node<" << node.v << ">";
//}

TEST_CASE ("test_expect_friend access") {
    SUT sut;
    auto v = getValue<const SUT&, int>(sut);
    assert(-123 == v);
}

TEST_CASE ("ensure operator<< is a friend of Node template") {
    Node n1{1};
    Node n2{'a'};
    Node n3{10.1};

    std::cout << n1 << n2 << n3 << std::endl;
}
