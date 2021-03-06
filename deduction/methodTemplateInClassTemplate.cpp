//
// Created by wein on 6/11/18.
//

// note:
// met this problem in wt's code base
// the "method" is a function template in a class template, making it
// harder to figure out the path of instantiation - i.e. how the
// compiler deduces the types...
// NOTE:
// there are a couple of ways to check that:
// use decltype (in combination of std::declval<>) to probe the type of the expression
// use type-tester
// write a lot of static_assert() inside the body

// since the wt code base is C++98, the example here uses boost type_traits
// and static assert instead of the standard library version
// UPDATE: I modified it to use C++11's type_traits - the callsite has
// no difference

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <type_traits>

template< typename ValueT, int _Rows >
class SUT
{
public:
    ValueT v;
    static const int rows = _Rows;

    template< typename T0, typename T1 >
    SUT( const T0& arg1, const T1& arg2 )
      : v( static_cast< ValueT >( arg1 + arg2 ) ){};

    template< typename T0, typename T1 >
    void foo( const ValueT& v )
    {
        static_assert( std::is_same< int, T0 >::value );
        static_assert( std::is_same< int, T1 >::value );
        this->v = v;
    }
};

TEST_CASE( "deduction" )
{
    using MySut = SUT< int, 3 >;
    static_assert( 3 == MySut::rows );

    // T0, T1 are deduced from parameters
    MySut mySut( 23.1, 2 );
    CHECK_EQ( 25, mySut.v );
    static_assert( std::is_same_v< decltype( MySut( 23.1, 2 ) ), SUT< int, 3 > > );
    static_assert( std::is_same_v< decltype( mySut.v ), int > ); // ValueT is int, narrowing cast

    // T0, T1 are explicitly defined by the caller
    // this can not happen in the ctor
    mySut.foo< int, int >( 1213 );
    CHECK_EQ( 1213, mySut.v );

    // this won't compile
    // no matching function for call to ‘SUT<int, 3>::foo(int)’
    // mySut.foo(2058);
}