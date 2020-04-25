#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <numeric>
#include <vector>

// c++ templates guide L/954
// to support default function parameter, declare a default type
// for the template parameter
template<
    typename T = int,
    typename Alloc,
    template<typename, typename> typename Container>
T do_sum(const Container<T, Alloc> &xs, T init = 0) {
    return std::accumulate(xs.begin(), xs.end(), init);
}

TEST_CASE ("") {
    CHECK_EQ(10, do_sum(std::vector<int>{1, 2, 3, 4}));
}
