//
// Created by weining on 19/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

// c++ template: complete guide L19291

template<typename... Elements>
struct TypeList {
};

using Primitives = TypeList<char, short, int, long>;

// +++++++++++ begin helper +++++++++++

template<typename List>
struct IsEmpty {
    static constexpr bool value = false;
};

template<>
struct IsEmpty<TypeList<>> {
    static constexpr bool value = true;
};

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

// +++++++++++ end helper +++++++++++

template<typename List,
    template<typename T> typename MetaFun,
    bool Empty = IsEmpty<List>::value>
struct TransformT;

// recursion, transform: (x:xs) -> f -> (f x : transform xs)
template<typename List,
    template<typename T> typename MetaFun>
struct TransformT<List, MetaFun, false> {
    using Type =
        PushFront<typename TransformT<PopFront<List>, MetaFun>::Type,
                  typename MetaFun<Front<List>>::Type>;
};

// base case, transform: [] -> f -> []
template<typename List,
    template<typename T> typename MetaFun>
struct TransformT<List, MetaFun, true> {
    using Type = List;
};

template<typename List, template<typename T> typename MetaFun>
using Transform = typename TransformT<List, MetaFun>::Type;

template<typename T>
struct AddConstT {
    using Type = const T;
};

TEST_CASE ("transform / fmap") {
    // test f
    static_assert(std::is_same_v<const int, AddConstT<int>::Type>);

    // test singleton typelist
    static_assert(std::is_same_v<
        TypeList<const int>, Transform<TypeList<int>, AddConstT>
    >);

    // test typelist holding multiple type elements
    static_assert(std::is_same_v<
        TypeList<const char, const short, const int, const long>,
        Transform<Primitives, AddConstT>
    >);
}
