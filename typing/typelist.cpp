//
// Created by weining on 19/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

// c++ template: complete guide L18944

template<typename... Elements>
class TypeList {};

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

TEST_CASE ("") {
    static_assert(std::is_same_v<Front<SignedIntTypes>, signed char>);
    static_assert(std::is_same_v<Front<PopFront<SignedIntTypes>>, short>);
    static_assert(std::is_same_v<Front<PushFront<SignedIntTypes, char>>, char>);
}
