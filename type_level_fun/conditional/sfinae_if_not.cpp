//
// Created by weining on 17/5/20.
//

// c++ template: complete guide L14562
// sfinae out a specialization if the given type does not satisfy certain criteria
// the technique (two test() overloads) originated in 1998
// worth reading it again as it seems to work for all the modern c++ standards

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <type_traits>
#include <utility>

template< typename T,
          typename = typename std::enable_if_t< std::is_convertible_v< T, int > >,
          typename = typename std::enable_if_t< std::is_default_constructible_v< T > > >
int
op( T t, int a )
{
    return ( int )( t ) + a;
}

// see: https://en.cppreference.com/w/cpp/types/is_convertible
// for is_convertible examples (and how to make a T convertible to G)
struct Foo
{
    Foo() = delete;
    Foo( int )
    {
    }
    operator int()
    {
        return 101;
    }
};

struct Bar
{
    // adding explicit will fail the is_convertible_t<> test
    operator int()
    {
        return 202;
    }
};

TEST_CASE( "" )
{
    op( 'a', 0 );
    op( 1.123, 0 );
    op( false, 0 );
    op( 0b101L, 0 );

    // won't compile due to lack of to-int conversion
    // op("asd", 0);
    // op(std::make_pair(1, 2), 1);

    // won't compile due to lack of default ctor
    // op(Foo{1}, 1);
    op( Bar{}, 1 );
}
