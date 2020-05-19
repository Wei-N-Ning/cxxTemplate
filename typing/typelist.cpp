//
// Created by weining on 19/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <tuple>

// c++ template: complete guide L18944

template<typename... Elements>
// define my own TypeList
class TypeList {};
// or use std::tuple as the TypeList
// most algorithms below work for both definitions
// !!!HOWEVER the LargestTypeT recursion will not!!!
//using TypeList = std::tuple<Elements...>;

using SignedIntTypes = TypeList<signed char, short, int, long long>;

template<typename List>
class FrontT;

template<typename Head, typename... Tail>
class FrontT<TypeList<Head, Tail...>> {
public:
    using Type = Head;
};

template<typename List>
using Front = typename FrontT<List>::Type;

template<typename List>
class PopFrontT;

template<typename Head, typename... Tail>
class PopFrontT<TypeList<Head, Tail...>> {
public:
    using Type = TypeList<Tail...>;
};

template<typename List>
using PopFront = typename PopFrontT<List>::Type;

template<typename List, typename NewElement>
class PushFrontT;

template<typename... Elements, typename NewElement>
class PushFrontT<TypeList<Elements...>, NewElement> {
public:
    using Type = TypeList<NewElement, Elements...>;
};

template<typename List, typename NewElement>
using PushFront = typename PushFrontT<List, NewElement>::Type;

// c++ templates: complete guide L19006
// type list algorithms
// indexing
template<typename List, unsigned N>
struct NthElementT : public NthElementT<PopFront<List>, N - 1> {};

// base case
template<typename List>
struct NthElementT<List, 0> : public FrontT<List> {};

template<typename List, unsigned N>
using NthElement = typename NthElementT<List, N>::Type;

// c++ template: complete guide L19063
// finding the largest type within the typelist
template<typename List>
struct LargestTypeT;

// recursive case
template<typename List>
struct LargestTypeT {
    using First = Front<List>;
    using Rest = typename LargestTypeT<PopFront<List>>::Type;
    using Type =
        std::conditional_t<(sizeof(First) > sizeof(Rest)), First, Rest>;
};

// base case
template<>
struct LargestTypeT<TypeList<>> {
    using Type = char;
};

template<typename List>
using LargestType = typename LargestTypeT<List>::Type;

TEST_CASE ("push pop") {
    static_assert(std::is_same_v<Front<SignedIntTypes>, signed char>);
    static_assert(std::is_same_v<Front<PopFront<SignedIntTypes>>, short>);
    static_assert(std::is_same_v<Front<PushFront<SignedIntTypes, char>>, char>);
}

TEST_CASE ("indexing") {
    static_assert(
        std::is_same_v<long long, NthElement<SignedIntTypes, 3>>
        );
}

TEST_CASE ("largest type") {
    static_assert(
        std::is_same_v<long long, LargestType<SignedIntTypes>>
    );
}
