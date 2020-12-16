//
// Created by weining on 16/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <utility>
#include <type_traits>
#include <variant>

// C++ 17 in detail P43

template< typename T >
class TypeTester;

TEST_CASE( "deduce class template argument automatically" )
{
    // NOTE I can not write (1, "iddqd") as the latter will be deduced to const char *
    // unless I provide my own deduction rule
    auto pr = std::make_pair( 1, std::string{ "i" } );
    // TypeTester< decltype( pr ) >();
}

template< typename T >
struct Wrapper
{
    using wrapped_t = T;
    T str;
};

// C++17 in detail P/45
// the compiler uses special rules called deduction guides to work out the
// template class types.
// we have two types of rules: compiler generated (implicitly generated) and
// user-defined.
Wrapper( const char* )->Wrapper< std::string >;

// this won't work
// std::make_pair( const char*, const char* )->std::pair< std::string, std::string >;

TEST_CASE( "custom deduction rule" )
{
    auto w = Wrapper{ "idkfa" };
    static_assert( std::is_same_v< decltype( w )::wrapped_t, std::string > );
}

// type deduction rule can be used to model sum-type pattern matching using
// std::variant; see cxxFP/types/sum_type for another example
template< typename... Ts >
struct overloaded : Ts...
{
    using Ts::operator()...;
};

template< typename... Ts >
overloaded( Ts... ) -> overloaded< Ts... >;

using Product = std::variant< int, char, float, double >;
using Result = int;

TEST_CASE( "model sum-type pattern matching" )
{
    auto xs = { Product{ 1 }, Product{ 'a' }, Product{ 1.1f }, Product{ 1.11 } };
    auto f = overloaded( []( const int& x ) -> Result { return 0; },
                         []( const char& x ) -> Result { return 1; },
                         []( const float& x ) -> Result { return 2; },
                         []( const double& x ) -> Result { return 3; } );
    for ( const auto& x : xs )
    {
        std::visit( f, x );
    }
}