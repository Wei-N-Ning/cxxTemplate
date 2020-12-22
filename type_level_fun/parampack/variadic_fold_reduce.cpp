//
// Created by weining on 22/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <unordered_set>
#include <tuple>
#include <string>
#include <type_traits>
#include <functional>

// c++ 17 the complete guide P/110
// combining hash functions

// this example shows a lighter way to implement the `reduce` (or accumulate)
// with fold expression;

// I can go full-on with the mini-framework documented in variadic_map_filter_acc
// but it's too verbose;

// the key in this example is how to model mutability (aggregating the results
// from individual steps) without relying on the 32 built-in operators or a
// custom Accumulator function object.

template< typename T >
void
hashCombine( std::size_t& io_seed, const T& val )
{
    io_seed ^= std::hash< T >()( val ) + 0x9e3779b9 + ( io_seed << 6 ) + ( io_seed >> 2 );
}

template< typename... Ts >
std::size_t
hashAll( Ts&&... xs )
{
    std::size_t seed = 0;
    ( ..., hashCombine( seed, std::forward< Ts >( xs ) ) );
    return seed;
}

TEST_CASE( "demo hash-combine function in unordered set" )
{
    using Item = std::tuple< int, std::string, int >;
    auto hashFunc = []( const Item& item ) {
        return hashAll(
          std::get< 0 >( item ), std::get< 1 >( item ), std::get< 2 >( item ) );
    };

    // by specifying the type of the key and its hash function, I can use the default
    // ctor to construct an uset, see:
    // see: https://en.cppreference.com/w/cpp/container/unordered_set/unordered_set
    // the bucket count is implementation-defined
    std::unordered_set< Item, decltype( hashFunc ) > xs;

    {
        auto [ _, wasAdded ] = xs.emplace( 1, "e1m1", 10 );
        CHECK( wasAdded );
    }
    {
        auto [ _, wasAdded ] = xs.emplace( 1, "e1m1", 10 );
        CHECK_FALSE( wasAdded );
    }
}

// extending this example to a generic reduce/accumulate function
// use an output parameter;
// (it is technically not a reduce, but an left-fold)
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

template< typename R, typename Function, typename... Ts >
R
computeAll( Function compute, R&& init, Ts&&... xs )
{
    R r = std::forward< R >( init );
    ( ..., compute( r, std::forward< Ts >( xs ) ) );
    return r;
}

TEST_CASE( "generic reduce with fold expression" )
{
    {
        // simple, integral computation
        auto f = []( int& o_count, const auto& x ) { o_count++; };
        auto n = computeAll( f, 0, '1', '2', '3', '4' );
        CHECK_EQ( n, 4 );
    }
    {
        // complex, container based computation (get unique elements)
        auto f = []( std::set< std::string >& s, const auto& str ) { s.emplace( str ); };
        auto s = computeAll( f, std::set< std::string >{}, "a", "ab", "a", "bc" );
        CHECK_EQ( s.size(), 3 );
    }
}
