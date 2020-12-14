//
// Created by weining on 14/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

enum class [[nodiscard]] Important{
    Yes,
    No,
};

struct [[nodiscard]] Answer
{
};

[[deprecated( "Use func2()" )]] void
func()
{
}

// without [[maybe_unused]] this results in compilation error
void
func2( [[maybe_unused]] int a )
{
    ;
}

TEST_CASE( "" )
{
    // -Wall will turn this into a compilation error
    auto o = []() { return Important::Yes; }();
    CHECK_EQ( o, Important::Yes );

    auto answer = []() { return Answer{}; }();
    CHECK( &answer != nullptr );

    // result in compilation error
    // func();
}
