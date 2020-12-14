#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// source
// more exception item 10 P63
//
// template specialization lets templates deal with special cases;
// sometime a generic algorithm can work much more efficiently for a
// certain kind of sequence (e.g. with random-access iterator), so it
// makes sense to specialize it for that case
//
// performance is a common reason to specialize but not the only one;
// you might also specialize a template to work with certain objects
// that do not conform to the normal interface expected.
//
// these special cases can be handled using two forms of template
// specialization: explicit specialization and partial specialization

// explicit specialization lets you write a specific implementation
// for a particular combination of template parameters

TEST_CASE( "nothing" )
{
    CHECK(1);
}
