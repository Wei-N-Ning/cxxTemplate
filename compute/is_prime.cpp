//
// Created by weining on 30/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// complete guide L4868

template<unsigned p, unsigned d>
struct DoIsPrime {
    static constexpr bool value = ( p % d != 0 ) && DoIsPrime<p, d - 1>::value;
};

template<unsigned p>
struct DoIsPrime<p, 2> {
    static constexpr bool value = ( p % 2 != 0 );
};

// primary template
template<unsigned p>
struct IsPrime {
    // start recursion with divisor from p/2
    static constexpr bool value = DoIsPrime<p, p/2>::value;
};

// special cases (to avoid endless recursion with template instantiation)
template<>
struct IsPrime<0> {
    static constexpr bool value = false;
};

template<>
struct IsPrime<1> {
    static constexpr bool value = false;
};

template<>
struct IsPrime<2> {
    static constexpr bool value = true;
};

template<>
struct IsPrime<3> {
    static constexpr bool value = true;
};

// complete guide L4920
constexpr bool is_prime_impl(unsigned p, unsigned d) {
    return d != 2 ? (p % d != 0) && is_prime_impl(p, d - 1) : (p % 2 != 0);
}

constexpr bool is_prime(unsigned p) {
    return p < 4 ? p >= 2 : is_prime_impl(p, p / 2);
}

// complete guide L4941
// the cleaner implementation
constexpr bool is_prime_clean(unsigned int p) {
    for (unsigned int d = 2; d <= p / 2; ++d) {
        if (p % d == 0) {
            return false;
        }
    }
    return p > 1;
}

TEST_CASE ("") {
    // prime number list: https://en.wikipedia.org/wiki/List_of_prime_numbers
    static_assert(IsPrime<857>::value, "template hack failed");
    static_assert(is_prime(857), "constexpr failed");
    static_assert(is_prime_clean(857), "constexpr function failed");
}
