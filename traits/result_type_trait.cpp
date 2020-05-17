//
// Created by weining on 17/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <vector>
#include <functional>
#include <type_traits>

// c++ template: complete guide L/14441

// list these two function templates here for reference only
template<typename T1, typename T2>
T1 op1(T1 lhs, T2 rhs) {
    return lhs + rhs;
}

template<typename T1, typename T2>
T2 op2(T1 lhs, T2 rhs) {
    return lhs + rhs;
}
// end of reference

template<typename T1, typename T2, typename Op>
std::vector<std::result_of_t<Op(T1, T2)>>
vecOp(std::vector<T1> lhs, std::vector<T2> rhs, Op op) {
    using ResultT = std::vector<std::result_of_t<Op(T1, T2)>>;
    ResultT o{};
    std::size_t sz{lhs.size() > rhs.size() ? lhs.size() : rhs.size()};
    o.reserve(sz);
    for (auto i = 0; i < sz; ++i) {
        o[i] = op(lhs[i], rhs[i]);
    }
    return o;
}

template<typename T1, typename T2, typename Op>
struct OpResult {
    explicit OpResult(Op, T1, T2) {}

    using Type = std::result_of_t<Op(T1, T2)>;
};

TEST_CASE ("std::result_of_t<> example") {
    OpResult result1(
        [](auto lhs, auto rhs) { return lhs > rhs ? lhs : rhs; }, 1, 'c');
    static_assert(
        std::is_same_v<decltype(result1)::Type, int>
        );

    OpResult result2(
        [](const auto &lhs, const auto &rhs) { return lhs > rhs ? lhs : rhs; }, 1, 'c');
    static_assert(
        std::is_same_v<decltype(result2)::Type, int>
    );

    OpResult result3(
        // either auto &&lhs (forwarding reference)
        // or auto lhs (value semantic)
        // or const auto &lhs (const reference to a temporary)
        // but not mut ref
        [](auto &&lhs, auto &&rhs) -> bool {
            return lhs > rhs;
        },
        1, 2
        );
    static_assert(
        std::is_same_v<decltype(result3)::Type, bool>
    );
}

// see microsoft's explanation on the ternary operator's return type:
// https://docs.microsoft.com/en-us/cpp/cpp/conditional-operator-q?view=vs-2019
// If both operands are of arithmetic or enumeration types, the usual arithmetic conversions
// (covered in Standard Conversions) are performed to convert them to a common type.
TEST_CASE ("A/B comparison type (ternary operator return type)") {
    std::vector<long long> v1{1, 2};
    std::vector<short> v2{30, 40};
    auto v3 = vecOp(v1, v2, [](long long v1, short v2) {
        // ternary operator performs a conversion that uses the wider
        // type of the two as the result type
        // the wider type is long long in this case
        // the actual values do not affect this decision
        return v1 > v2 ? v1 : v2;
    });
    static_assert(
        std::is_same_v<long long, decltype(v3)::value_type>
    );
}

TEST_CASE ("element type is of value") {
    std::vector<int> v1{1, 2};
    std::vector<char> v2{'a', 'b'};
    auto v3 = vecOp(v1, v2, [](int lhs, char rhs) { return lhs + rhs; });
    static_assert(
        std::is_same_v<int, decltype(v3)::value_type>
    );

    auto v4 = vecOp(v1, v2, [](int lhs, char rhs) -> char { return lhs % 16 + rhs; });
    static_assert(
        std::is_same_v<char, decltype(v4)::value_type>
    );
}

TEST_CASE ("element type is of reference wrapper") {
    std::vector<int> v1orig{1, 2};
    std::vector<char> v2orig{'a', 'b'};
    std::vector<std::reference_wrapper<int>> v1{
        std::ref(v1orig[0]), std::ref(v1orig[1])};

    // to prove that v1 holds mut ref
    v1[1].get() = 20;

    std::vector<std::reference_wrapper<char>> v2{
        std::ref(v2orig[0]), std::ref(v2orig[1])
    };
    auto v3 = vecOp(v1, v2, [](auto lhs, auto rhs) { return lhs + rhs; });
    static_assert(
        std::is_same_v<int, decltype(v3)::value_type>
    );

    // to prove that v1 (again) holds mut ref
    CHECK_EQ(20, v1orig[1]);

    auto v4 = vecOp(v1, v2, [](auto lhs, auto rhs) -> char { return lhs % 16 + rhs; });
    static_assert(
        std::is_same_v<char, decltype(v4)::value_type>
    );
}
