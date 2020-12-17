//
// Created by weining on 30/4/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <type_traits>
#include <string>

// inspired by complete guide L/4081

// NOTE:
// as shown in FP in C++, the meta-programming chapter, the common technique to use when
// I need to selectively handle some T but not other T, is to implement a base, cover-all
// template, and then I can specialize the template for the T that meet my criteria.

enum class Case
{
    Red,
    Blue,
};

template< typename T, typename = std::void_t<> >
struct F
{
    Case static f()
    {
        return Case::Red;
    }
};

template< typename T >
struct F< T, std::enable_if_t< std::is_convertible_v< T, std::string > > >
{
    Case static f()
    {
        return Case::Blue;
    }
};

template< typename T >
class TT;

TEST_CASE( "test is convertible to T" )
{
    static_assert( std::is_convertible_v< std::string, std::string > );
    static_assert( std::is_convertible_v< const char*, std::string > );
    static_assert( std::is_convertible_v< char[], std::string > );

    // enable_if_t<> (void) if the condition is true, is a better match to the compiler;
    // if the condition is false, the compile falls back to the base one, which matches
    // everything.
    auto o1 = F< char[] >::f();
    CHECK_EQ( o1, Case::Blue );
    auto o2 = F< int >::f();
    CHECK_EQ( o2, Case::Red );
}
