#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <algorithm>
#include <vector>
#include <list>

// complete guide L3208
// the default assignment op requires that both sides of the assignment
// op have the same type, which is not the case if stack have different
// element types
// by defining an assignment op as a template, you can enable conversion
template<typename A>
struct Stack {
    A elems{};

    template<typename B>
    Stack &operator=(const Stack<B> &other) {
        this->elems.resize(other.elems.size());
        std::copy(this->elems.begin(), this->elems.end(), other.elems.begin());
        return *this;
    }
};

TEST_CASE ("") {
    Stack<std::list<int>> st1;
    st1.elems = std::list<int>{1, 2, 3};
    Stack<std::vector<float>> st2;
    st2.elems = std::vector<int>{4, 5, 6};
    // won't compile without the template assignment op
    st1 = st2;
}

