
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

// source: https://stackoverflow.com/questions/87372/check-if-a-class-has-a-member-function-of-a-given-signature
// second answer with the highest vote
#include <type_traits>

// Primary template with a static assertion
// for a meaningful error message
// if it ever gets instantiated.
// We could leave it undefined if we didn't care.

template<typename, typename T>
struct has_clone {
    static_assert(
            std::integral_constant<T, false>::value,
            "Second template parameter needs to be of function type.");
};

// specialization that does the checking

template<typename C, typename Ret, typename... Args>
struct has_clone<C, Ret(Args...)> {
private:
    template<typename T>
    static constexpr auto check(T*)
    -> typename
    std::is_same<
            decltype( std::declval<T>().clone( std::declval<Args>()... ) ),
            Ret    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    >::type;  // decltype( EXPR ) returns the type of the EXPR;

    // if EXPR does not make sense to the compiler - i.e. clone() method does
    // not exist - or its type is different to Ret, this static check will
    // fail and the template will not be instantiated. SFINAE

    template<typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<C>(0)) type;

public:
    static constexpr bool value = type::value;
};

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

class X {};


TEST_CASE ("test_has_function_trait()") {
    SUT c;
    CHECK_NE(&c, c.clone());

    CHECK(has_clone<SUT, SUT*()>::value);
    CHECK_FALSE(has_clone<X, X*()>::value);
}
