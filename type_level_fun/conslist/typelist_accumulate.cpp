//
// Created by weining on 19/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

// c++ template: complete guide L19324

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
    template<typename T1, typename T2> typename Accu,
    typename Init,
    bool Empty = IsEmpty<List>::value>
struct AccumulateT;

template<typename List,
    template<typename T1, typename T2> typename Accu,
    typename Init>
struct AccumulateT<List, Accu, Init, false> {
    using NewInit = typename Accu<Init, Front<List>>::Type;
    using Rest = PopFront<List>;
    using Type = typename AccumulateT<Rest, Accu, NewInit>::Type;
};

template<typename List,
    template<typename T1, typename T2> typename Accu,
    typename Init>
struct AccumulateT<List, Accu, Init, true> {
    using Type = Init;
};

template<typename T1, typename T2>
struct LargerT {
    using Type = std::conditional_t<
        (sizeof(T1) > sizeof(T2)),
        T1,
        T2
    >;
};

TEST_CASE ("AccumulateT with LargerT -> LargestT") {
    static_assert(std::is_same_v<
        long long,
        AccumulateT<TypeList<char, int, long long>, LargerT, short>::Type
    >);
}

TEST_CASE ("AccumulateT with PushFrontT -> ReverseT") {
    static_assert(std::is_same_v<
        TypeList<char, short, int>,
        AccumulateT<TypeList<int, short, char>, PushFrontT, TypeList<>>::Type
    >);
}
