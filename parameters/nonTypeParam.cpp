#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

/*
source
https://stackoverflow.com/questions/499106/what-does-template-unsigned-int-n-mean

You can have several kinds of template parameters

Type Parameters.
Types
Templates (only classes and alias templates, no functions or variable templates)

Non-type Parameters
Pointers
References
Integral constant expressions

 */

template< unsigned int S >
struct Vector
{
    unsigned char bytes[ S ];
};

TEST_CASE( "" )
{
    // pass 3 as argument.
    Vector< 3 > test{ 1, 1, 1 };
    static_assert( 3 == sizeof( test ), "fail" );
}
