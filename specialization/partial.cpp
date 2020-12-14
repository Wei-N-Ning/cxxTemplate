#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// source:
// more exception item 10 P64
//
// partial specialization: for class templates only, you can define
//                         ^^^^^^^^^^^^^^^^^^^^^^^^ (i.e. it is a type-level thing)
// partial specialization that don't have to fix all the primary (
// unspecialized) class template's parameters

template< typename T1, typename T2, int tag >
struct SUT
{
    T1 v1 = 101;
    T2 v2 = 202;
};

// fix T1 T2; T1 T2 is the same T
template< typename T, int tag >
struct SUT< T, T, tag >
{
    T v1 = 1;
    T v2 = 2;
};

// fix T1 T2; T1 T2 are not the same T
// recall EMC++ type deduction rule: how is T2* deduced
template< typename T1, typename T2, int tag >
struct SUT< T1, T2*, tag >
{
    T1 v1 = -3;
    T2* v2 = nullptr;
};

// fix T1 T2; hardcoded T1 (int), T2 is any T, hardcoded tag to 0xDEAD
// recall EMC++ and other sources for tag dispatching
// see also tag dispatching examples in this project
template< typename T >
struct SUT< int, T, 0xDEAD >
{
    int v1 = 0xBEEF;
    T v2 = 4;
    int tag = 0xDEAD;
};

TEST_CASE( "T1 T2 is the same T" )
{
    // use the partial specialization
    SUT< int, int, 1 > sut;
    CHECK_EQ( sut.v2, 2 );
}

TEST_CASE( "T1 T2 are not the same T, instantiate the base template" )
{
    // fallback to the original template, SUT<T1, T2>
    SUT< int, long, 1 > sut;
    CHECK_EQ( sut.v2, 202 );
}

TEST_CASE( "T1 T2 are not the same T, " )
{
    SUT< int, int*, 1 > sut;
    CHECK_EQ( sut.v2, nullptr );
}

TEST_CASE( "T1_is_int_and_Tag_is_Dead" )
{
    SUT< int, unsigned char, 0xDEAD > sut;
    CHECK_EQ( sut.v2, 4 );
    CHECK_EQ( sut.v1, 0xBEEF );
}
