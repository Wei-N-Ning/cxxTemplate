//
// Created by weining on 1/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <utility>
#include <functional>
#include <vector>
#include <numeric>
#include <iostream>

template<typename Callable, typename... Args>
decltype(auto) log_call(Callable &&op, Args&&... args) {
    using namespace std;
    cout << typeid(op).name() << ": ";
    (cout << ... << typeid(args).name());
    cout << endl;
    return invoke(forward<Callable>(op), forward<Args>(args)...);
}

int f(int a, int b) {
    return a + b;
}

TEST_CASE ("") {
    log_call(f, 1, 2);
    std::vector<int> v{1, 2, 3};
}
