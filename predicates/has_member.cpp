//
// Created by weining on 17/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <type_traits>
#include <vector>
#include <utility>

// c++ template: complete guide L15162
// note: based on the example in the book and some previously documented patterns
// in /traits, I added a couple of new examples showing how to implement predicate
// to check whether a member function exists
// it is very complicated, because I have to account for the type signature of
// the function - its arguments, return type etc.
// it might be better to use simpler dispatching mechanism (such as adding some
// tags to the input types) or std::variant's patten matching

// L15195
// also beware: a reference type has no member, but whenever we use references
// the resulting expressions have the underlying type
// as a workaround, use std::remove_reference
// L15264
// detecting nontype members
// this is the ultimate workaround (based on macro) to check whether a method
// exists

// see also: has_all_methods.cpp, which formalize the method requirement and
// extend it to multiple methods

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
//
// what if I don't care the return type?
// L15330, the example in the book answers this:
//
// std::void_t<decltype(std::declval<T>().begin())>>
// pluggin it into the predicate:
//
// struct HasBeginT<T, std::void_t<decltype(std::declval<T>().begin())>>>
// : std::true_type {}
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
