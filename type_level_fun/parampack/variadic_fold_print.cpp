//
// Created by weining on 22/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <type_traits>
#include <iostream>
#include <sstream>

// c++ 17 the complete guide P/108
// demonstrating a clean `print` function template (python-like) using the left
// fold expression (printing from left to right)
// however as explained on P/110, with the special `comma operator` and the
// strict evaluation order introduced in c++ 17, both left-fold and right-fold
// would see the statements run from left to right

template< typename OStream, typename Head, typename... Tail >
std::void_t< decltype( std::declval< OStream >() << std::declval< Head >() ) >
printTo( OStream& os, Head&& head, Tail&&... tail )
{
    os << std::forward< Head >( head );
    auto feedSpace = [ &os ]( auto&& arg ) {
        os << ' ' << std::forward< decltype( arg ) >( arg );
    };
    ( ..., feedSpace( std::forward< Tail >( tail ) ) );
    os << '\n';
}

template< typename... Ts >
void
print( Ts... params )
{
    printTo( std::cout, std::forward< Ts >( params )... );
}

TEST_CASE( "python style print statement with optional ostream" )
{
    printTo( std::cout, 1, 'c', "there is a cow", 1.013f );
    print( 1, 'c', "there is a cow", 1.013f );

    std::ostringstream oss;
    printTo( oss, 1, 'c', "there is a cow" );
    CHECK_EQ( oss.str(), "1 c there is a cow\n" );
}

struct Item
{
    int val{ 0 };

    template< typename T >
    Item& operator<<( T&& arg )
    {
        val++;
        return *this;
    }
};

TEST_CASE( "printTo fake ostream object" )
{
    Item oss;
    CHECK_EQ( oss.val, 0 );
    printTo( oss, 1, 'c', "there is a cow", 1.013f );
    //                    x x x x  x               x x    x
    // the number of calls to operator<<(), indicated by `x`
    CHECK_EQ( oss.val, 8 );
}