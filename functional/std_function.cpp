//
// Created by weining on 19/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <algorithm>

// c++ template: complete guide L18070
// the interface is described entirely within a class template partial
// specialization, which serves to break the template argument (a func
// type) into its component pieces (result and argument types)
//
// type-eraser, type-erasure

template<typename Signature>
struct FunctionPtr;

// each instance of FuncBridge is an abstract class, so its derived classes
// are responsible for providing actual impl for its virtuals
// we can accomplish this - to support the complete range of potential func
// objects - by parameterizing the derived class on the type of the function
// object it stores
template<typename R, typename... Args>
struct FuncBridge {
    virtual ~FuncBridge() = default;

    virtual FuncBridge *clone() const = 0;

    virtual R invoke(Args... args) const = 0;
};

// the impl contains a single non-static member variable, bridge, which will be
// responsible for both storage and manipulation of the stored function object
// ownership of this pointer is tied to the FunctionPtr object, so most of the
// implementation provided merely manages this pointer
template<typename R, typename... Args>
struct FunctionPtr<R(Args...)> {
    FuncBridge<R, Args...> *bridge;

    FunctionPtr() : bridge(nullptr) {}

    template<typename F>
    FunctionPtr(F &&f);

    FunctionPtr(const FunctionPtr &other) :
        bridge(nullptr) {
        if (other.bridge) {
            bridge = other.bridge->clone();
        }
    }

    FunctionPtr(FunctionPtr &other) :
        FunctionPtr(static_cast<const FunctionPtr &>(other)) {};

    FunctionPtr(FunctionPtr &&other) noexcept:
        bridge(other.bridge) {
        other.bridge = nullptr;
    }

    FunctionPtr &operator=(const FunctionPtr &other) {
        if (&other != this) {
            FunctionPtr tmp(other);
            std::swap(*this, tmp);
        }
        return *this;
    }

    FunctionPtr &operator=(FunctionPtr &&other) noexcept {
        delete bridge;
        bridge = other.bridge;
        other.bridge = nullptr;
        return *this;
    }

    template<typename F>
    FunctionPtr &operator=(F &&f) {
        FunctionPtr tmp(std::forward<F>(f));
        std::swap(*this, tmp);
        return *this;
    }

    ~FunctionPtr() {
        delete bridge;
    };

    friend void swap(FunctionPtr &fp1, FunctionPtr &fp2) {
        std::swap(fp1.bridge, fp2.bridge);
    }

    explicit operator bool() const {
        return bridge == nullptr;
    }

    // invoke the underlying f
    R operator()(Args... args) const {
        return bridge->invoke(std::forward<Args>(args)...);
    }
};

TEST_CASE ("") {
    ;
}
