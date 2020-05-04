//
// Created by weining on 4/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <numeric>
#include <random>
#include <map>
#include <optional>
#include <functional>

// ran into some confusion while reading c++ stl cookbook P/221
// the example in this book implements a trie for searching for sentence;
// the find() method returns a wrapper of a mutable reference.
// this case study is to bring some clarity to this mechanism

// see: https://en.cppreference.com/w/cpp/utility/functional/reference_wrapper

TEST_CASE ("master copy in list and mutable reference in vector, bidirection modification") {
    std::list<int> l{1, 2, 3, 4};
    std::vector<std::reference_wrapper<int>> v(l.begin(), l.end());

    CHECK_EQ(std::list<int>{1, 2, 3, 4}, l);
    CHECK_EQ(std::vector<int>{1, 2, 3, 4}, std::vector<int>(v.begin(), v.end()));

    // modification to the master copy should reflect on the mutable refs
    for (auto &i : l) {
        i *= 2;
    }
    CHECK_EQ(std::vector<int>{2, 4, 6, 8}, std::vector<int>(v.begin(), v.end()));

    // modification to the mutable refs should reflect on the master copy
    // however I can not change int & to auto &, because the resulting type is reference_wrapper<> which
    // does not have an assignment operator
    for (int &i : v) {
        i = i / 2 * 10;
    }
    CHECK_EQ(std::list<int>{10, 20, 30, 40}, l);
}

TEST_CASE ("master copy in map, returns mutable reference") {
    using KeyT = std::string;
    using ValueT = std::vector<std::string>;
    using MapT = std::map<KeyT, ValueT>;
    MapT map{
        {"1", {}},
    };

    auto safe_find = [&map](const KeyT &key) -> std::optional<std::reference_wrapper<ValueT>> {
        if (auto it = map.find(key); it != map.end()) {
            return std::ref(it->second);
        }
        return {};
    };
    CHECK_FALSE(safe_find("...").has_value());
    if (auto found = safe_find("1"); found.has_value()) {
        // here I also need to specify, that I want to use the reference_wrapper as a mutable reference
        // using `auto &` won't work as the type is still reference_wrapper
        ValueT &mut = found.value();
        mut.emplace_back("iddqd");
    } else {
        CHECK(false);
    }
    CHECK_EQ(1, safe_find("1").value().get().size());
}
