//
// Created by wein on 5/6/18.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iostream>

#define ALIGNMENT_MAX 16

template< int N, int C = 1 >
struct RoundUpPow2
{
    enum { value = RoundUpPow2< N/2, C*2 >::value };
};

template< int C >
struct RoundUpPow2< 0, C >
{
    enum { value = ( C > ALIGNMENT_MAX ) ? ALIGNMENT_MAX : C };
};

template< typename T, int W >
struct Align
{
    enum { value = RoundUpPow2< sizeof( T ) * W - 1 >::value };
};

template< typename T >
struct Align< T, 0 >
{
    enum { value = sizeof( T ) };
};

TEST_CASE ("") {
    struct Align<char, 7> unnamed;
    std::cout << unnamed.value << std::endl;
    // char, 15 -> 16
    // char, 7 -> 8
    // uint8_t, 3 -> 4
    // uint32_t, 3 -> 16

    // the resulting value is available at compile time
    char ignore[unnamed.value];
}

class Foo {};

class Bar : private Foo {};
class FooBar : private Bar {};

TEST_CASE ("") {
    using namespace std;

    // even empty classes, however, have non-zero size
    // for many platforms this prints 1
    // a few systems impose more strict alignment requirements on class types
    // and may print another small integer
    cout << sizeof(Foo{}) << endl;
    // it prints the same size for every class, but none of these has
    // size zero
    // this means that within class Bar, the class Foo is not given any space
    cout << sizeof(Bar{}) << endl;
    cout << sizeof(FooBar{}) << endl;
}
