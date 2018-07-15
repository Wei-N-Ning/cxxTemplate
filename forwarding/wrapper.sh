#!/usr/bin/env bash

# an experiment to inspect how the assembly calls the forwarding
# function

# observation shows that
# main() populates the registers for the functor and its arguments
# then calls 0x400628 the wrapper template
# the wrapper, even though marked inline, as its own frame
# I can see std::forward() and std::remove_reference in the listing


setUp() {
    set -e
    rm -rf /tmp/sut
    mkdir /tmp/sut
}

buildProgram() {
    cat > /tmp/_.cpp <<EOF
#include <type_traits>
#include <utility>
class A {
public:
    int value = 11;
    bool active = false;
};
A producer(int value, bool active) {
    A a;
    a.value = value;
    a.active = active;
    return a;
}
template<typename F, typename... Ts>
inline auto wrapper(F&& f, Ts&&... params) {
    return std::forward<F>(f)(std::forward<Ts>(params)...);
}
int main() {
    auto ins = wrapper(producer, 222, true);
    if (ins.value == 222) {
        return 0;
    }
    return 1;
}
EOF
}

cxxCompile() {
    g++ -g -std=c++14 -Wall -Werror \
/tmp/_.cpp \
-o /tmp/_
}

disassemble() {
    local func=${2-"main"}
    gdb -batch \
    -ex "set disassembly-flavor intel" \
    -ex "file ${1:?missing binary path}" \
    -ex "disassemble /rs ${func}"
}

setUp
buildProgram
cxxCompile
/tmp/_
disassemble /tmp/_ 0x400628
