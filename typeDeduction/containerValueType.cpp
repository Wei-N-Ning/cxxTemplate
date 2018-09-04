
// use custom type and stl container with univsersal reference;
// the tricky part is to retrieve the ::value_type while T is 
// a reference

// NOTE where to put typename keyword 

#include <vector>
#include <type_traits>

class A {
};

void RunTinyTests();

template<typename T>
void _process(T&& container) {
    using actual = typename std::remove_reference<T>::type::value_type;
    static_assert(std::is_same<actual, A>::value, "");
}

void test_retrieve_value_type() {
    std::vector<A> v;
    _process(v);
}

int main() {
    RunTinyTests();
    return 0;
}
