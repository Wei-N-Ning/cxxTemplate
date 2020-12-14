#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// use custom type and stl container with universal reference;
// the tricky part is to retrieve the ::value_type while T is
// a reference

// NOTE where to put typename keyword

#include <vector>
#include <type_traits>
#include <utility>

class A
{
};

template< typename T >
void
process( T&& container )
{
    using actual = typename std::remove_reference< T >::type::value_type;
    static_assert( std::is_same< actual, A >::value );
}

TEST_CASE( "" )
{
    std::vector< A > v;
    process( v );
}
