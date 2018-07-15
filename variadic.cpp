//
// Created by wein on 5/27/18.
//

#include <cassert>
#include <tuple>

template<typename... Ts>
void foo(Ts&&... params) {
    std::tuple<Ts...> t{params...};
    constexpr std::size_t sz = std::tuple_size<decltype(t)>::value;
    assert((4 == sz));
}

int main() {
    foo(1, 2.3, "asd", true);
    return 0;
}
