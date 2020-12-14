//
// Created by weining on 20/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iostream>
#include <unordered_map>
#include <functional>
#include <utility>

using CacheT = std::unordered_map< int, int >;

int
fib( int n, CacheT* cache = nullptr ) noexcept
{
    if ( !cache )
    {
        if ( n == 0 or n == 1 )
            return 1;
        return fib( n - 1 ) + fib( n - 2 );
    }
    else
    {
        if ( cache->find( n ) == cache->end() )
        {
            if ( n == 0 or n == 1 )
            {
                ( *cache )[ n ] = 1;
                return 1;
            }
            ( *cache )[ n ] = fib( n - 1, cache ) + fib( n - 2, cache );
        }
        return ( *cache )[ n ];
    }
}

template< typename F, typename... Args >
void
prof( F&& f, Args&&... args )
{
    using timeunit_t = std::chrono::microseconds;
    using _clock_t = std::chrono::high_resolution_clock;

    auto start = _clock_t::now();
    std::invoke( std::forward< F >( f ), std::forward< Args >( args )... );
    auto end = _clock_t::now();
    std::cout << std::chrono::duration_cast< timeunit_t >( end - start ).count() << " ms"
              << std::endl;
}

TEST_CASE( "forwarding in application: memoization" )
{
    CacheT cache;
    CHECK_EQ( fib( 38 ), fib( 38, &cache ) );
    prof( fib, 38, nullptr );
    prof( fib, 38, &cache );
}
