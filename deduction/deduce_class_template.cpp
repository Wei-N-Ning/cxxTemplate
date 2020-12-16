//
// Created by weining on 16/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <utility>

// C++ 17 in detail P43

template< typename T >
class TypeTester;

TEST_CASE( "deduce class template argument automatically" )
{
    // NOTE I can not write (1, "iddqd") as the latter will be deduced to const char *
    auto pr = std::make_pair( 1, std::string{ "i" } );
    // TypeTester< decltype( pr ) >();
}