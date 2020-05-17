//
// Created by weining on 17/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <type_traits>
#include <vector>
#include <utility>

// c++ template: complete guide L15162

// helper to ignore any member of template parameters
template<typename...>
using VoidT = void;

// primary template
template<typename, typename = VoidT<>>
struct HasSizeTypeT : std::false_type {};

// partial specialization, maybe sfinae out
template<typename T>
struct HasSizeTypeT<T, VoidT<typename T::size_type>> : std::true_type {};

template<typename T>
using has_size_type = HasSizeTypeT<T>;

TEST_CASE ("") {
    static_assert(! has_size_type<int>());
    static_assert(has_size_type<std::vector<int>>());
}

struct Foo {
    void clear() {}

    bool size() { return false; }
};

////////////////////////////////////////////
// fallback
template<typename, typename = VoidT<>>
struct has_clear_func : std::false_type {};

// "concept requirement"
template<typename T>
using HasClear = std::enable_if_t<std::is_same_v<decltype(std::declval<T>().clear()), void>>;

// wrap up
template<typename T>
struct has_clear_func<T, HasClear<T>> : std::true_type {};

////////////////////////////////////////////
// fallback
template<typename, typename = VoidT<>>
struct has_size_func : std::false_type {};

// "concept requirement", note the use of decltype and is_same_v
template<typename T>
using HasSize = std::enable_if_t<std::is_same_v<decltype(std::declval<T>().size()), std::size_t>>;

// wrap up
template<typename T>
struct has_size_func<T, HasSize<T>> : std::true_type {};

TEST_CASE ("has member function of type") {
    // nop
    static_assert(! has_clear_func<int>());
    // yes (impersonator wins)
    static_assert(has_clear_func<Foo>());
    // yes
    static_assert(has_clear_func<std::vector<int>>());

    // yes
    static_assert(has_size_func<std::vector<int>>());
    // nop! impersonator does not have the expected type signature
    static_assert(! has_size_func<Foo>());
}
