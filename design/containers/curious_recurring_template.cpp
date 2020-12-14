//
// Created by weining on 18/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <cstddef>

// c++ template: complete guide L17363
// to give the template a chance to test the given T (which is the derived class) in
// order to customize the behaviour at compile time.

template< typename CountedType >
class ObjectCounter
{
public:
    static std::size_t value()
    {
        return count;
    }

protected:
    ObjectCounter()
    {
        ++count;
    }

    ObjectCounter( const ObjectCounter< CountedType >& )
    {
        ++count;
    }

    ObjectCounter( ObjectCounter< CountedType >&& ) noexcept
    {
        ++count;
    }

    ~ObjectCounter()
    {
        --count;
    }

private:
    inline static std::size_t count{ 0 };
};

template< typename CharT >
class String : public ObjectCounter< String< CharT > >
{
};

TEST_CASE( "test template" )
{
    String< char > s1, s2;
    String< wchar_t > ws1;

    CHECK_EQ( 2, String< char >::value() );
    CHECK_EQ( 1, ws1.value() );
}
