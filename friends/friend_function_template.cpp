
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

void RunTinyTests();

void test_expect_friend() {
    SUT sut;
    auto v = getValue<const SUT&, int>(sut);
    assert(-123 == v);

}

int main() {
    RunTinyTests();
    return 0;
}
