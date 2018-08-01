#!/usr/bin/env bash

# utility to display function signature

setUp() {
    set -e
    rm -rf /tmp/sut
    mkdir /tmp/sut
}

buildProgram() {
    cat > /tmp/_.cpp <<EOF
#include <type_traits>
class A {};
A producer(int count, bool silent) {
    return A();
}
template<typename T>
class TypeTester;
int main() {
    TypeTester<decltype(producer)> tt;
    return 0;
}
EOF
}

cxxCompile() {
    local msg=$( g++ -g -std=c++14 -Wall -Werror \
/tmp/_.cpp \
-o /tmp/_  2>&1 )
    echo ${msg} | awk '
BEGIN {
    RS="[<>]"
}
/A\(/ {
    print
}
'
}

setUp
buildProgram
cxxCompile
