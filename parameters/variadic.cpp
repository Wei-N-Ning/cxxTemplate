//
// Created by wein on 5/27/18.
//

// used this in wkou code base
// recall EMC++ variadic parameter and perfect forwarding

#include <cassert>
#include <tuple>
#include <string>
#include <cstring>
#include <cstdio>

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

// verify that the output pointer stays an output pointer
int bar_impl(const std::string& i_s, std::string* o_str) {
    *o_str = i_s;
    return 3;
}

// verify that the output reference stays an output reference
int bar_impl(const std::string& i_s, std::string& o_str) {
    o_str = i_s;
    return 4;
}

// EMC++ P167
// "perfect forwarding (constructor)" P180
// std::forward<decltype(params)>(params)...
// without effective/perfect forwarding - i.e. if the wrap takes
// arguments by value, bar(Ts... params) - it creates temporary objects 
// from the references (const or not) then passes the temporary objects 
// to the impl functions
template<typename... Ts>
int bar(Ts&&... params) {
    return bar_impl(std::forward<decltype(params)>(params)...);
}

int main() {
    foo(1, 2.3, "asd", true);
    std::string name("13");
    assert(1 == bar(name));
    assert(2 == bar(1, 1.0));
    
    // output parameter is a pointer
    std::string receiver;
    assert(3 == bar(name, &receiver));
    assert(0 == strcmp(name.c_str(), receiver.c_str()));
    
    // output parameter is a mutable reference
    std::string answer;
    assert(4 == bar(name, answer));
    assert(0 == strcmp(name.c_str(), answer.c_str()));
    return 0;
}
