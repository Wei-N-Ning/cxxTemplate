//
// Created by weining on 5/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <type_traits>
#include <vector>
#include <array>
#include <iterator>

// inspired by master c++ stl P/29
//

template<std::size_t Size, typename Elem>
class Container {
public:
    using C = std::conditional_t<(Size > 8), std::vector<Elem>, std::array<Elem, Size>>;
    using Iter = typename C::iterator;
    using ConstIter = typename C::const_iterator;
    using iterator_category = std::random_access_iterator_tag;
    using value_type = Elem;

    Container(std::initializer_list<Elem> &&il) {
        std::copy(std::begin(il), std::end(il), c.begin());
    }

    Iter begin() {
        return c.begin();
    }

    Iter end() {
        return c.end();
    }

    ConstIter cbegin() {
        return c.cbegin();
    }

    ConstIter cend() {
        return c.cend();
    }

private:
    C c{};
};

TEST_CASE ("") {
    Container<4, int> container{1, 1, 1, 1};
    Container<64, int> c2{};
    static_assert(std::is_same_v<decltype(container)::C, std::array<int, 4>>);
    static_assert(std::is_same_v<decltype(c2)::C, std::vector<int>>);
    for (auto &elem : container) {
        CHECK_EQ(1, elem);
    }
    for (const auto &elem : container) {
        CHECK_EQ(1, elem);
    }
}

// c++ template: complete guide L15605
// using std::conditional_t to implement a safe make_unsigned trait
// L15543
// the instantiation of UnsignedT<bool> is still undefined behavior because
// the compiler will still attempt to form the type form:
// typename std::make_unsigned<T>::type
// to address this problem, we need to add an additional level of indirection
// so that the conditional_t<> arguments are themselves uses of type
// functions that wrap the result
template<typename T>
struct IdentityT {
    using Type = T;
};

template<typename T>
struct MakeUnsignedT {
    using Type = typename std::make_unsigned<T>::type;
};

template<typename T>
struct UnsignedT {
    using Type =
        typename std::conditional_t<
            std::is_integral_v<T> && !std::is_same_v<T, bool>,
            MakeUnsignedT<T>,
            IdentityT<T>
        >::Type;  // ::Type is guaranteed to work
        // this relies entirely on the fact that the not-selected wrapper type
        // in the conditional_t<> construct is never fully instantiated
        // (meaning that, ::Type won't work inside the parameter list)
};

template<typename T>
using to_unsigned = typename UnsignedT<T>::Type;

TEST_CASE ("") {
    static_assert(
        std::is_same_v<unsigned int, to_unsigned<int>>
        );

    static_assert(
        std::is_same_v<unsigned char, to_unsigned<char>>
    );

    static_assert(
        std::is_same_v<bool, to_unsigned<bool>>
    );

    static_assert(
        std::is_same_v<std::vector<int>, to_unsigned<std::vector<int>>>
    );
}
