//
// Created by weining on 17/5/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// c++ template: complete guide L14142
// see also: transformation traits (that modify the given types)
// see also: adding reference (rvalue reference) L14174

template<typename T>
struct RemoveReferenceT {
    using Type = T;
};

template<typename T>
struct RemoveReferenceT<T &> {
    using Type = T;
};

template<typename T>
struct RemoveReferenceT<T &&> {
    using Type = T;
};

// L14152
// a convenience alias template makes the usage simpler
// removing the reference from a type is typically useful when the type was
// derived using a construct that sometimes produces reference types, such as
// the special deduction rule for function parameters of type T&&
template<typename T>
using RemoveReference = typename RemoveReferenceT<T>::Type;

TEST_CASE ("") {
    static_assert(
        std::is_same_v<int, RemoveReference<int &&>>
        );
}
