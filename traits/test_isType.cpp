//
// Created by wein on 4/9/18.
//

#include <cassert>

namespace IsBoolTest {

template<typename T>
struct is_bool {
    static const bool value = false;
};

template<>
struct is_bool<bool> {
    static const bool value = true;
};

template<typename T>
int sut(T t) {
    if (is_bool<T>::value) {
        return 101;
    }
    return -10;
}

void test_isBool() {
    assert(-10 == sut(101));
    assert(101 == sut(false));
}

}

int main(int argc, char **argv) {
    IsBoolTest::test_isBool();
    return 0;
}
