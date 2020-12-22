#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <functional>
#include <vector>

TEST_CASE( "lambda" )
{
    std::function< double( std::vector< double > ) > func =
      []( const std::vector< double >& vd ) -> double {
        double result = 0;
        for ( const auto& elem : vd )
        {
            result += elem;
        }
        return result;
    };
    // c++ template: complete guide L18033
    // lambda can be converted to a std::function<> object, to be
    // used with value semantics
    // std::function<> is a generalized form of a C++ function pointer, providing
    // the same fundamental operations
    const std::function< double( std::vector< double > ) >& f = func;
    CHECK_EQ( 3, func( { 1, 2 } ) );
    CHECK_EQ( 3, f( { 1, 2 } ) );
}

// complete guide: L3433
// generic lambda (c++14) is a shortcut for member (operator()) template
// don't have to define a default-constructed object with an operator() method
TEST_CASE( "generic lambda" )
{
    auto f = []( auto x, auto y ) { return x + y; };
    CHECK_EQ( f( 1u, 2u ), 3u );
    CHECK_EQ( f( std::string{ "there" }, std::string{ "is" } ),
              std::string{ "thereis" } );
}

TEST_CASE( "constexpr lambda" )
{
    // C++ 17 in detail P/38
    // lambda expressions that follow the rules of standard constexpr functions are
    // implicitly declared as constexpr!

    // c++ 17 the complete guide
    // since c++17, lambdas are implicitly constexpr if possible
    // to find out at compile time whether a lambda is valid for a compile-
    // time context, you can declare it as `constexpr`
    auto f = []( auto x, auto y ) constexpr { return x + y; };
    static_assert( f( 1, 2 ) == 3 );

    // constexpr function requirements
    // if you want your function or lambda to be executed at compile-time then
    // the body of this function shouldn't invoke any code that is not constexpr
    // for example, you can not allocate memory dynamically
    // if you violate the rules of constexpr functions (while declaring it as
    // constexpr) you will get a compile-time error.
}