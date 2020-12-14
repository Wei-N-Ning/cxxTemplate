//
// Created by weining on 27/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <vector>
#include <list>
#include <array>
#include <algorithm>
#include <iostream>
#include <iterator>

template< typename Container >
struct Stack
{
    // complete guide L2963
    // to clarify that an identifier inside a template is a type
    // in this case: value_type is a type defined within class T
    // in general, typename has to be used whenever a name that depends
    // on a template parameter is a type
    using ElemT = typename Container::value_type;
};

TEST_CASE( "" )
{
    // won't compile because int has no member type ::value_type
    // Stack<int> s;
    Stack< std::vector< int > > s;
    CHECK( std::is_same_v< decltype( s )::ElemT, int > );
}

// complete guide: L2989
// to access type const_iterator of template type Container, you have to
// qualify it with a leading typename
template< typename Container >
std::ostream&
dump( const Container& c, std::ostream& os )
{
    typename Container::const_iterator pos = c.cbegin();
    std::copy_n( pos,
                 c.size() - 1,
                 std::ostream_iterator< typename Container::value_type >{ os, ", " } );
    os << c.back();
    return os;
}

TEST_CASE( "" )
{
    dump( std::vector< int >{ 1, 2 }, std::cout ) << std::endl;
    dump( std::list< int >{ 3, 4 }, std::cout ) << std::endl;
    dump( std::array< int, 2 >{ 5, 6 }, std::cout ) << std::endl;
}
