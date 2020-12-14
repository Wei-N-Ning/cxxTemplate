#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// nested template parameter, see:
// https://stackoverflow.com/questions/20373466/nested-c-template-parameters-for-functions
// cpp reference:
// https://en.cppreference.com/w/cpp/language/template_parameters
// template and class keywords, since C++17 are interchangeable
// https://stackoverflow.com/questions/2023977/difference-of-keywords-typename-and-class-in-templates

#include <list>
#include <vector>
#include <array>
#include <numeric>

// read again the answer of https://stackoverflow.com/questions/20373466/nested-c-template-parameters-for-functions
// vector and list types requires two type parameters: element T and allocator T
template <typename T, typename Alloc, template <typename, typename> typename CollectionType>
T doSum(const CollectionType<T, Alloc> &xs, const T &init) {
    return std::accumulate(xs.cbegin(), xs.cend(), init);
}

// array type does not require allocator T but a size value
// see: /usr/include/c++/7/array
// complete guide L3611
// Because the template parameter of the template-template parameter is not used,
// it is customary to omit its name (unless it provides useful documentation)
// i.e.: template<typename Elem, std::size_t Size> can be simplified as
//       template<typename, std::size_t>
// the keyword class and typename is interchangeable here since C++17
template<typename T,
        std::size_t sz,
        template<typename Elem, std::size_t Size> typename CollectionType>
T doSum(const CollectionType<T, sz> &xs, const T &init) {
    typename CollectionType<T, sz>::value_type v{};
    return std::accumulate(xs.cbegin(), xs.cend(), init + v);
}

TEST_CASE ("conainer type depends on element type") {
    std::vector<long> v(10, 10);
    std::list<int> l(10, 10);
    std::array<unsigned char, 3> arr{10, 0, 0};

    CHECK_EQ(100, doSum(v, 0L));
    CHECK_EQ(100, doSum(l, 0));
    CHECK_EQ(10, doSum(arr, static_cast<unsigned char>(0)));
}
