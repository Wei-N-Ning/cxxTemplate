//
// Created by weining on 19/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

// c++ template: complete guide L19408

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
    template<typename T1, typename T2> typename Compare,
    typename Element,
    bool Empty = IsEmpty<List>::value>
struct InsertSortT;

template<typename T>
struct Identity {
    using Type = T;
};

// inserts a value into an already sorted list at the first point that
// will keep the list sorted
// to decide whether the element to be inserted should go at the beginning
// of the list or later in the list
template<typename List,
    template<typename T1, typename T2> typename Compare,
    typename Element>
struct InsertSortT<List, Compare, Element, false> {
    using NewTail = typename std::conditional_t<
        Compare<Element, Front<List>>::value,
        Identity<List>,  // Element > Head
        InsertSortT<PopFront<List>, Compare, Element>  // Element < Head
    >::Type;
    using NewHead = std::conditional_t<
        Compare<Element, Front<List>>::value,
        Element,  // Element > Head
        Front<List>  // Element < Head
    >;
    using Type = PushFront<NewTail, NewHead>;
};

// base
template<typename List,
    template<typename T1, typename T2> typename Compare,
    typename Element>
struct InsertSortT<List, Compare, Element, true> {
    using Type = PushFront<List, Element>;
};

template<typename List,
    template<typename T1, typename T2> typename Compare,
    bool Empty = IsEmpty<List>::value>
struct InsertionSortT;

template<typename List,
    template<typename T1, typename T2> typename Compare>
struct InsertionSortT<List, Compare, false> {
    using Head = Front<List>;
    using Rest = typename InsertionSortT<PopFront<List>, Compare>::Type;
    using Type = typename InsertSortT<Rest, Compare, Head>::Type;
};

// base
template<typename List,
    template<typename T1, typename T2> typename Compare>
struct InsertionSortT<List, Compare, true> {
    using Type = List;
};

template<typename T1, typename T2>
struct LargerT {
    static constexpr bool value = sizeof(T1) > sizeof(T2);
};

struct Foo {
    char a{};
    char b{};
    char c{};
};

TEST_CASE ("do sort") {
    using TL = TypeList<short, long, int, char, Foo, std::size_t>;
    static_assert(
        std::is_same_v<
            InsertionSortT<TL, LargerT>::Type,
            TypeList<std::size_t, long, int, Foo, short, char>
        >
    );
}

