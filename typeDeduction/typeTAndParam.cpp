//
// Created by wein on 5/26/18.
//
// source:
// Effective Modern C++ P11 (Item 1)
//
// UPDATE
// auto and auto& (similarly const auto and const auto&) are completely two different things!!
// If I want to use value/object semantics, make sure I pay greater attention to this
// a getter that returns mutable reference is useless because heavy_obj is a copy
// not a reference
// auto heavy_obj = get_heavy_obj();

#include <cassert>
#include <type_traits>

// if t is a reference, ignore the reference part
// Type_ is T;
// ParamType_ is the type of t/param

namespace case1 {

template<typename Type_, typename ParamType_, typename T>
void processRef(T &param) {
    assert((std::is_same<T, Type_>::value));
    assert((std::is_same<T&, ParamType_>::value));
}

template<typename Type_, typename ParamType_, typename T>
void processConstRef(const T &param) {
    assert((std::is_same<T, Type_>::value));
    assert((std::is_same<const T&, ParamType_>::value));
}

template<typename Type_, typename ParamType_, typename T>
void processPointer(T *param) {
    assert((std::is_same<T, Type_>::value));
    assert((std::is_same<T*, ParamType_>::value));
}

void verifyTAndParamType() {
    int value = 27;
    const int constValue = value;
    const int &constRef = value;
    const int *ptrToConst = &value;

    processRef<int, int &>(value);
    processRef<const int, const int &>(constValue);
    processRef<const int, const int &>(constRef);

    processConstRef<int, const int &>(value);
    processConstRef<int, const int &>(constValue);
    processConstRef<int, const int &>(constRef);

    processPointer<int, int *>(&value);
    processPointer<const int, const int *>(ptrToConst);  // ptrToT, T is const int
}

}

namespace case2 {

template<typename Type_, typename ParamType_, typename T>
void processUniversalRef(T &&param) {
    assert((std::is_same<T, Type_>::value));
    assert((std::is_same<T&&, ParamType_>::value));
}

void verifyTAndParamType() {
    int value = 27;
    const int constValue = value;
    const int &constRef = value;

    processUniversalRef<int &, int &>(value);
    processUniversalRef<int, int &&>(13);  // 13 is a rvalue, ParamType_ is a rvalue-reference;
                               // case1's reference-stripping rule still applies
    processUniversalRef<const int &, const int &>(constValue);
    processUniversalRef<const int &, const int &>(constRef);
}

}

namespace case3 {

template<typename ParamType_, typename T>
void processValue(T param) {
    assert((std::is_same<T, ParamType_>::value));
}

void verifyTAndParamType() {
    int value = 27;
    int &ref = value;
    const int &constRef = value;
    volatile int vv = value;

    processValue<int>(value);
    processValue<int>(ref);  // param will be a new object hence this rule
    processValue<int>(constRef);
    processValue<int>(vv);
}

}

namespace case_array {

// source: EMC++ Item 1 P16
// note the unusual ref-to-array parameter: T (&)[sz]

template<typename Type_, typename ParamType_, typename T>
void processRef(T &param) {
    assert((std::is_same<T, Type_>::value));
    assert((std::is_same<T&, ParamType_>::value));
}

// interestingly, the ability to declare references to arrays
// enables creation of a template that deduces the number of
// elements that an array contains
//
// return size of an array as a compile-time constant
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept {
    return N;
}

void verifyTAndParamType() {
    int arr[] = {0, 0, 0, 0, 0};
    processRef<int[5], int (&)[5]>(arr);

    assert(5 == arraySize(arr));

    int bar[arraySize(arr)];  // better version, std::array<int, arraySize(arr)>;
    std::size_t count = 0;
    for (const auto &elem : bar) {
        count++;
    }
    assert(5 == count);
}

}

int main() {
    case1::verifyTAndParamType();
    case2::verifyTAndParamType();
    case3::verifyTAndParamType();
    case_array::verifyTAndParamType();
    return 0;
}