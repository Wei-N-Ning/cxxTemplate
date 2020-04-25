#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <cassert>

// source
// exceptional P74
// 

template<typename T, typename R>
R getValue(const T& t) {
    return t.m_value;
};

class SUT {
    int m_value = -123;
    friend decltype(m_value) getValue<const SUT&, decltype(m_value)>(const SUT& sut);
};

TEST_CASE ("test_expect_friend access") {
    SUT sut;
    auto v = getValue<const SUT&, int>(sut);
    assert(-123 == v);

}
