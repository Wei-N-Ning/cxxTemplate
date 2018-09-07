
// exceptional P61
// function template can be overloaded by another function template
// recall what is a primary template

// TODO: see again guideline P63

// P64
// it is a lot less intuitive to specialize function templates
//  - you can not partially specialize them; you overload them instead,
//  - function specializations don't overload. This means that any 
//   specializations you write will not affect which template gets 
//   used,
//
// if you are writing a function template, prefer to write it as a 
// single function template that should never be specialized or 
// overloaded 
// use functor idiom

#include <functional>
#include <cassert>

template<typename T>
int sut(T val) {
    return 1;
}

template<>
int sut<int*>(int* ptr) {
    return 11;
}

template<typename T>
int sut(T* prt) {
    return 2; 
}

// exceptional P63
// considered a better approach
// to support functor/callable partial specialization
// recall std::forward
template<typename T, int goal>
struct FImpl {
    int operator() (T&& t) {
        return goal; 
    }
};

int sut(double v) {
    return 0xBEEF;
}

void RunTinyTests();

// TODO: document why the seemingly perfect candidate is not chosen
void test_expect_candidate() {
    assert(2 == sut((int *)nullptr));
    
    // exceptional P63 guideline:
    // if you want to be sure it will always be used in the case of 
    // an exact match, that is what a plain function is for, so just 
    // make it a function instead of a specialization
    
    // 2) if you do provide overloads of a function template, avoid 
    // also providing specializations
    assert(0xBEEF == sut(1.0));
}

int main() {
    RunTinyTests();
    return 0;
}
