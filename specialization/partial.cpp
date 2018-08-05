
#include <cassert>

// source:
// more exception item 10 P64
//
// partial specialization: for class templates only, you can define 
// partial specialization that don't have to fix all the primary (
// unspecialized) class template's parameters

template<typename T1, typename T2, int tag>
struct SUT {
    T1 v1 = 101;
    T2 v2 = 202;
};

template<typename T, int tag>
struct SUT<T, T, tag> {
    T v1 = 1;
    T v2 = 2;
};

// recall EMC++ type deducation rule: how is T2* deduced 
template<typename T1, typename T2, int tag>
struct SUT<T1, T2*, tag> {
    T1 v1 = -3;
    T2* v2 = nullptr;
};

// recall EMC++ and other sources for tag dispatching
// see also tag dispatching examples in this project
template<typename T>
struct SUT<int, T, 0xDEAD> {
    int v1 = 0xBEEF;
    T v2 = 4;
    int tag = 0xDEAD;
};

void T2_is_T1() {
    // use the partial specialization 
    SUT<int, int, 1> sut;
    assert(sut.v2 == 2);
}

void T2_is_not_T1() {
    // fallback to the original template, SUT<T1, T2>
    SUT<int, long, 1> sut;
    assert(sut.v2 == 202);
}

void T2_is_any_pointer() {
    SUT<int, int*, 1> sut;
    assert(! sut.v2);
}

void T1_is_int_and_Tag_is_Dead() {
    SUT<int, unsigned char, 0xDEAD> sut;
    assert(sut.v2 == 4);
    assert(sut.v1 == 0xBEEF);
}

int main() {
    T2_is_T1();
    T2_is_not_T1();
    T2_is_any_pointer();
    T1_is_int_and_Tag_is_Dead();
    return 0;
}

