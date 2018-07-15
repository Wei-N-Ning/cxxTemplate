//
// Created by wein on 5/26/18.
//
// source: EMC++ Item 3 P23

#include <cassert>
#include <vector>

namespace Item3 {

void logAccess() {
    ;
}

#define MUTABLE (10)
#define CONSTANT (-10)
#define INDEX (1)

struct Dumm {
    Dumm() :m_value(MUTABLE), m_value_const(CONSTANT) {};
    int &operator[](int index) {
        return m_value;
    }
    int operator[](int index) const {
        return m_value_const;
    }
    int m_value;
    int m_value_const;
};

template<typename Container, typename Index>
decltype(auto) access(Container &&c, Index i) {
    logAccess();
    return std::forward<Container>(c)[i];
}

void test_returnTypes_lvalueContainer() {
    std::vector<int> v{0, 0, 0};

    // classic operator[], returns a mutable ref
    int &elem = v[2];
    elem = 10;

    // use access() template
    // CLion does not seem to understand decltype(auto)
    access(v, 2) = 1;

    assert(1 == v[2]);
}

void test_returnTypes_rvalueContainer() {
    Dumm d;
    const Dumm &dRef = d;
    const Dumm dConst;

    assert(MUTABLE == access(Dumm(), INDEX));
    assert(MUTABLE == access(d, INDEX));
    assert(CONSTANT == access(dRef, INDEX));
    assert(CONSTANT == access(dConst, INDEX));

    auto createConstDumm = []() -> const Dumm {
        const Dumm tmp;
        return tmp;
    };
    assert(CONSTANT == access(createConstDumm(), INDEX));
}

void test_variables() {
    struct Some {
    };

    Some some;
    const Some &someRef = some;
    auto other = someRef;
    decltype(auto) shouldBeRef = someRef;

    assert((std::is_same<Some, decltype(other)>::value));
    assert((std::is_same<const Some &, decltype(shouldBeRef)>::value));
}

}

int main() {
    Item3::test_returnTypes_lvalueContainer();
    Item3::test_returnTypes_rvalueContainer();
    Item3::test_variables();
    return 0;
}
