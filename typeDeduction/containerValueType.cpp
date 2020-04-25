#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// use custom type and stl container with univsersal reference;
// the tricky part is to retrieve the ::value_type while T is 
// a reference

// NOTE where to put typename keyword 

#include <vector>
#include <type_traits>

class A {
};

template<typename T>
void _process(T&& container) {
    using actual = typename std::remove_reference<T>::type::value_type;
    static_assert(std::is_same<actual, A>::value, "");
}

TEST_CASE ("") {
    std::vector<A> v;
    _process(v);
}
