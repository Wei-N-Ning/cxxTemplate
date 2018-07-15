//
// Created by wein on 6/11/18.
//

// note:
// met this problem in wt's code base
// the "method" is a function template in a class template, making it
// harder to figure out the path of instantiation - i.e. how the
// compiler deduces the types...

// since the wt code base is C++98, the example here uses boost type_traits
// and static assert instead of the standard library version


#include <cassert>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

template<typename ValueT, int _Rows>
class SUT {
public:
    ValueT v;
    static const int rows = _Rows;

    template<typename T0, typename T1>
    SUT(const T0& arg1, const T1& arg2)
        : v(static_cast<ValueT>(arg1 + arg2)) {
    };

    template<typename T0, typename T1>
    void foo(const ValueT& v) {
        BOOST_STATIC_ASSERT(boost::is_same<int, T0>::value);
        BOOST_STATIC_ASSERT(boost::is_same<int, T1>::value);
        this->v = v;
    }
};

int main() {
    typedef SUT<int, 3> MySut;
    BOOST_STATIC_ASSERT(3 == MySut::rows);

    // T0, T1 are deduced from parameters
    MySut mySut(23.1, 2);
    assert(25 == mySut.v);

    // T0, T1 are explicitly defined by the caller
    // this can not happen in the ctor
    mySut.foo<int, int>(1213);
    assert(1213 == mySut.v);

    // this won't compile
    // no matching function for call to ‘SUT<int, 3>::foo(int)’
    // mySut.foo(2058);

    return 0;
}