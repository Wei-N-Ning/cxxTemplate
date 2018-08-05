//
// Created by wein on 5/27/18.
//

// used this in wkou code base
// recall EMC++ variadic parameter and perfect forwarding
// TODO: 
// 1. verify that for bar_impl(const std::string&), the callee indeed
// gets a reference (not reconstructed)
// 2. verify that Ts... params can work with any reference types
// 3. forward() is indeed perfect (when using Ts&&...)

#include <cassert>
#include <tuple>
#include <string>

template<typename... Ts>
void foo(Ts&&... params) {
    std::tuple<Ts...> t{params...};
    constexpr std::size_t sz = std::tuple_size<decltype(t)>::value;
    assert((4 == sz));
}

int bar_impl(const std::string& i_s) {
    return 1;
}

int bar_impl(int i, double d) {
    return 2;
}

template<typename... Ts>
int bar(Ts... params) {
    return bar_impl(params...);
}

int main() {
    foo(1, 2.3, "asd", true);
    std::string name("13");
    assert(1 == bar(name));
    assert(2 == bar(1, 1.0));
    return 0;
}
