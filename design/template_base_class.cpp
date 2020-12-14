//
// Created by weining on 28/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

template< typename T >
struct ComputeBase
{
    T generate()
    {
        return T{};
    }
};

template< typename T >
struct Compute : ComputeBase< T >
{
    // compute guide L3088
    // we recommend that you always qualify any symbol that is declared in a
    // based that is somehow dependent on a template parameter
    T generatex2()
    {
        // can not resolve symbol
        // generate()
        // do:
        // return this->generate() * 2;
        // or:
        return ComputeBase< T >::generate() * 2;
    }
};

TEST_CASE( "base class and derived class" )
{
    ComputeBase< int > cb;
    CHECK_EQ( 0, cb.generate() );
    Compute< int > c;
    CHECK_EQ( 0, c.generatex2() );
}