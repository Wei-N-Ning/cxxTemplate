//
// Created by weining on 4/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>

// inspired by mut_reference.cpp and c++ stl cookbook (the original problem)
// to prove that, with safe_find() mechanism which returns a wrapper of a reference,
// the caller must decide how to consume the reference - mutable or immutable;
// but the interface can make it easier by returns a pair of const-iterators to enforce the
// immutability, if the value type is of some container type

TEST_CASE ("") {
    using KeyT = std::string;
    using ValueT = std::vector<std::string>;
    using MapT = std::map<KeyT, ValueT>;
    using FoundT = std::optional<std::reference_wrapper<ValueT>>;
    MapT m{
        {"1", {"there"}},
    };
    auto safe_find = [&m](const KeyT &k) -> FoundT {
        if (auto it = m.find(k); it != m.end()) {
            return std::ref(it->second);
        }
        return {};
    };

    if (auto found = safe_find("1"); found.has_value()) {
        const ValueT &v = found.value();
        CHECK_EQ(1, v.size());

        ValueT &mv = found.value();
        mv.emplace_back("is");
        CHECK_EQ(2, v.size());
    } else {
        CHECK(false);
    }

    auto safe_its = [&m](const KeyT &k) -> std::pair<ValueT::const_iterator, ValueT::const_iterator> {
        if (auto it = m.find(k); it != m.end()) {
            return {it->second.cbegin(), it->second.cend()};
        }
        return {ValueT::const_iterator{}, ValueT::const_iterator{}};
    };
    {
        auto[it, end] = safe_its("1");
        // can not call non-const method: immutability is guaranteed
        // it->replace(it->begin(), 'a', 'b');
        std::copy(it, end, std::ostream_iterator<std::string>{std::cout, " "});
        std::cout << std::endl;
    }
    {
        // even in the case of "not found", the caller can still pass the returned iterators to the algorithms
        auto[it, end] = safe_its("10000");
        std::copy(it, end, std::ostream_iterator<std::string>{std::cout, " "});
        std::cout << std::endl;

        // or use explicit if statement
        if (auto [it, end] = safe_its("10000"); it != end) {
            CHECK(false);
        }
    }
}
