
// source:
// more exception item 4 P19
//
// what is trait
// a class that encapsulates a set of types and functions necessary
// for template class/function to manipulate objects of types for 
// which they are instantiated

// P20
// the idea is that a trait class is an instance of template, and is 
// used to carry extra information.
// the nice thing is that the trait class T<C> lets us record such 
// extra information about a class C, without requiring any change 
// to C

// (an example)...with user defined type, you provide suitable 
// specialization of std::char_traits<T>
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// required method: T* T::clone() const

// P31
//
// write a specialization for each clone-able class
template<class T>
class Cloneable {
public:
    static T* clone(const T* instance) { return nullptr; }
};

class SUT {
public:
    SUT* clone() const { return nullptr; }
};

template<>
class Cloneable<SUT> {
public:
    static SUT* clone(const SUT* instance) { return instance->clone(); }
};


TEST_CASE ("test_has_function_trait()") {
    SUT c;
    CHECK_NE(&c, c.clone());
}
