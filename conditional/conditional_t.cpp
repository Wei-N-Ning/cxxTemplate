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
