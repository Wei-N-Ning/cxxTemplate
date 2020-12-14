//
// Created by wein on 4/28/18.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// this example shows static (compile-time) dispatching
// a better approach is to use pattern-match to design a generic algorithm with works
// with type classes;
// see iter_category_void_t.cpp
// recap on pattern match:
// case T of:
//     void_t<some_property_of_T> -> ...
//     _ -> ...

#include <iterator>
#include <list>
#include <vector>

namespace impl
{
template< class InputIterator, class Distance >
void
advance_dispatch( InputIterator& i, Distance n, std::input_iterator_tag )
{
    while ( n-- )
        ++i;
}

template< class BidirectionalIterator, class Distance >
void
advance_dispatch( BidirectionalIterator& i, Distance n, std::bidirectional_iterator_tag )
{
    if ( n >= 0 )
        while ( n-- )
            ++i;
    else
        while ( n++ )
            --i;
}

template< class RandomAccessIterator, class Distance >
void
advance_dispatch( RandomAccessIterator& i, Distance n, std::random_access_iterator_tag )
{
    i += n;
}
} // end of namespace impl

template< class InputIterator, class Distance >
void
advance( InputIterator& i, Distance n )
{
    typename std::iterator_traits< InputIterator >::iterator_category category;
    impl::advance_dispatch( i, n, category );
}

TEST_CASE( "" )
{
    std::vector< int > v( 0, 10 );
    auto vi = v.cbegin();
    std::list< int > l( 0, 10 );
    auto li = l.cbegin();

    // taking advantage of random access
    ::advance( vi, 3 );

    // use linear access
    ::advance( li, 3 );
}
