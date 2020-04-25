//
// Created by wein on 4/9/18.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

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

TEST_CASE ("test_isBool()") {
    CHECK_EQ(-10, sut(101));
    CHECK_EQ(101, sut(false));
}
