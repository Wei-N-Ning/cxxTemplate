//
// Created by weining on 28/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// complete guide: L3097
// how to specifically deal with raw arrays
template<typename T, std::size_t N, std::size_t M>
bool less(T (&a)[N], T(&b)[M]) {
    for (int i = 0; i < N && i < M; ++i) {
        if (a[i] < b[i]) return true;
        if (b[i] < a[i]) return false;
    }
    return N < M;
}

TEST_CASE ("") {
    int arr[] = {1, 2, 3};
    int ary[] = {1, 2, 3, 4, 5};
    int arw[] = {10, 2};
    // T: int, N: 3, M: 5
    CHECK(less(arr, ary));
    CHECK_FALSE(less(arw, arr));
    CHECK_FALSE(less("", ""));
    CHECK(less("there", "there is acow"));
}
