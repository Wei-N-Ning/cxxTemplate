//
// Created by weining on 18/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iostream>

// c++ template: complete guide L17150

class Foo {};

class Bar : private Foo {};
class FooBar : private Bar {};

TEST_CASE ("") {
    using namespace std;

    // even empty classes, however, have non-zero size
    // for many platforms this prints 1
    // a few systems impose more strict alignment requirements on class types
    // and may print another small integer
    cout << sizeof(Foo{}) << endl;
    // it prints the same size for every class, but none of these has
    // size zero
    // this means that within class Bar, the class Foo is not given any space
    cout << sizeof(Bar{}) << endl;
    cout << sizeof(FooBar{}) << endl;
}
