//
// Created by weining on 23/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <type_traits>
#include <vector>

// c++ 17 the complete guide P/248
// std::void_t<> yield `void` for any variadic list of template parameters (
// as long as the parameters are valid, not triggering SFINAE). This is used
// where we only want to deal with types solely in an argument list.

// the major application is the ability to check fo conditions when defining
// new type traits.

// Note: it usually involves this two-step dance:

template< typename, typename = std::void_t<> > // works for any T
struct HasProperties : std::false_type
{
};

template< typename T > // works for T that meets the criteria
struct HasProperties< T,
                      //
                      std::void_t< decltype( std::declval< T >().begin() ),
                                   typename T::difference_type,
                                   typename T::iterator > > : std::true_type
{
};

// the partial specialization is only used when all the corresponding
// type-level expressions are valid for a T; otherwise it triggers SFINAE
// and only the primary template is available, which derives from the
// false type.

// this pattern can be used for all kind of condition checking centered on
// a given T (or Ts)

template< typename T >
constexpr bool has_properties_v = HasProperties< T >::value;

TEST_CASE( "test has_properties meta function" )
{
    static_assert( !has_properties_v< int > );
    static_assert( has_properties_v< std::vector< int > > );
}
