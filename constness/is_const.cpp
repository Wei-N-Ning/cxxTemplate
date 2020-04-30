//
// Created by weining on 30/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>

// complete guide L4461
// to disable passing constant objects to non-constant references
// I can also use std::enable_if<> to disable this case completely
template<typename T>
void modify(T& arg) {
    static_assert(!std::is_const_v<T>,
            "out param of modify<T>(T &) is const");
}

TEST_CASE ("") {
    const std::string s{"there is"};
    // disallowed; it will trigger static_assert and IDE will throw an error
    // modify(s);

    // disallowed; arg is a prvalue
    // modify(std::string{});

    std::string ls{"a"};
    modify(ls);
}
