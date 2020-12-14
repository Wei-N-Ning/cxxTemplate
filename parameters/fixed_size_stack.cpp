//
// Created by weining on 26/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <array>
#include <optional>

// complete guide L2309,
// can also specify that a template param is deduced from the previous param
// or to ensure that the passed value has the same type as the passed type
// template<typename T, T init = T{}>
template< auto init, std::size_t Maxsize, typename T = decltype( init ) >
class Stack
{
public:
    Stack() = default;
    void fill()
    {
        std::fill_n( elements.begin(), numElems = Maxsize, init );
    }

    std::optional< T > pop()
    {
        if ( numElems == 0 )
        {
            return std::optional< T >{};
        }
        return std::optional< T >{ elements[ --numElems ] };
    }

    std::optional< T > top()
    {
        if ( numElems > 0 )
        {
            return std::optional< T >( elements[ numElems - 1 ] );
        }
        return std::optional< T >{};
    }

    std::optional< std::size_t > push( const T& v )
    {
        if ( numElems == Maxsize )
        {
            return std::optional< std::size_t >{};
        }
        elements[ numElems++ ] = v;
        return std::optional< std::size_t >{ numElems };
    }

    bool empty()
    {
        return numElems == 0;
    }

private:
    std::array< T, Maxsize > elements = {};
    std::size_t numElems = 0;
};

TEST_CASE( "fix-sized stack using std::optional" )
{
    Stack< 10, 2 > st;
    CHECK( st.push( 123 ).has_value() );
    CHECK_EQ( st.push( 234 ), 2 );
    CHECK_FALSE( st.push( 345 ).has_value() );
    CHECK_EQ( st.top(), 234 );
    CHECK_EQ( st.pop(), 234 );
    CHECK_EQ( st.pop(), 123 );
    CHECK_FALSE( st.pop().has_value() );
    CHECK( st.empty() );

    st.fill();
    CHECK_EQ( st.top(), 10 );

    // complete guide L2275: those two instances are different types,
    // there is NO implicit conversion defined
    static_assert( !std::is_same_v< Stack< 1, 2 >, Stack< 1, 3 > >, "fail" );
}

// complete guide L2363
// non-type param has restriction (no floating point, no object...)
// commonly they are merely some integral types
enum class PaymentType
{
    deferred,
    immediate,
    bank_transfer,
};

template< auto pt, typename T = decltype( pt ) >
class TypeTester
{
};

TEST_CASE( "type tester" )
{
    // complete guide L2468
    // can use auto to let the compiler find out the type of the param
    TypeTester< PaymentType::deferred > tt1;
    TypeTester< 1 > tt2;
}
