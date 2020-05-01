#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <numeric>
#include <vector>
#include <iostream>

// NOTE: gcc only
// see: https://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_demangling.html
// read: https://stackoverflow.com/questions/4465872/why-does-typeid-name-return-weird-characters-using-gcc-and-how-to-make-it-prin
// attempted cross platform solution
// https://stackoverflow.com/questions/281818/unmangling-the-result-of-stdtype-infoname
#ifdef __GNUG__
#include <cxxabi.h>
#endif

// c++ templates guide L/954
// to support default function parameter, declare a default type
// for the template parameter
// complete guide L/7024
// the parameters of template-template parameters can have default template args
// these default args apply when the corresponding parameters are not specified
// in uses of the template-template parameter
template<
    typename T = int,
    typename Alloc = std::allocator<T>,
    template<typename, typename> typename Container>
T do_sum(const Container<T, Alloc> &xs, T init = 0) {
    std::string name =
#ifdef __GNUG__
        abi::__cxa_demangle(typeid(Alloc).name(), nullptr, nullptr, nullptr);
#else
        typeid(Alloc).name();
#endif
    std::cout << name << std::endl;
    return std::accumulate(xs.begin(), xs.end(), init);
}

TEST_CASE ("") {
    CHECK_EQ(10, do_sum(std::vector<int>{1, 2, 3, 4}));
}
