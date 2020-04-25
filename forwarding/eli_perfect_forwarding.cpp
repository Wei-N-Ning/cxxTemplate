//
// Created by wein on 1/09/18.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// source
// Eli Bendersky's website:
// https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c
//
// his inspirational article compensates Scott Meyer's Effect Modern C++
// and provides more explanation on when to use forwarding.

#include <functional>
#include <vector>
#include <string>

// to be painted by textures
class Canvas {
public:
    Canvas() = default;
    Canvas(std::size_t width, std::size_t height)
        : m_width(width), m_height(height) {};
private:
    std::size_t m_width = 0;
    std::size_t m_height = 0;
};

struct Area {
    std::size_t m_minX = 0;
    std::size_t m_maxX = 0;
    std::size_t m_minY = 0;
    std::size_t m_maxY = 0;
};

// to paint on an area (width on a canvas
class Texture {
public:
    Texture() = delete;

    Texture(Canvas canvas, Area area)
    : m_canvas(canvas), m_area(area) {
        actions += 'A';
    }

    Texture(Texture&& other) noexcept
    : m_canvas(other.m_canvas), m_area(other.m_area) {
        actions += 'M';
    }

    Texture(const Texture& other) noexcept
        : m_canvas(other.m_canvas), m_area(other.m_area) {
        actions += 'C';
    }

    ~Texture() {
        actions += 'D';
    }

    Area& area() { return m_area; }

    static std::string actions;
private:
    Canvas m_canvas;
    Area m_area;
};

std::string Texture::actions;

TEST_CASE ("push_back()") {
    std::vector<Texture> textures;
    Canvas canvas(10, 10);

    // Article
    // If you trace the execution... you will see something like:
    // > ctor for a temporary object (A)
    // > move ctor if one was defined, otherwise a copy ctor, for
    //   the object actually allocated inside the vector
    //   (M; but if move-ctor is remove, the action here will be C)
    // > dtor for the temporary (D)

    Texture::actions.clear();
    textures.push_back(Texture(canvas, Area()));
    CHECK_EQ(std::string("AMD"), Texture::actions);
}

TEST_CASE ("emplace_back_alloc()") {
    std::vector<Texture> textures;
    Canvas canvas(10, 10);
    textures.push_back(Texture(canvas, Area()));

    // NOTE: vector needs to allocate new storage space for the newly
    // created element - this result in a different code path to the
    // emplace-construction code path
    // with GCC 7, it calls insert(end(), std::forward<...>()...)
    // therefore it still creates a temporary object (so that insert()
    // can work)
    // There is a weak assumption that the compiler will not pre-allocate
    // addition space after ctor or push_back.

    Texture::actions.clear();
    textures.emplace_back(canvas, Area{1, 1, 2, 2});
    CHECK_EQ(std::string("AMD"), Texture::actions);
}

TEST_CASE ("emplace_back()") {
    std::vector<Texture> textures;
    Canvas canvas(10, 10);
    textures.reserve(4);

    // At this time, the storage space is enough for emplace-construction,
    // so the action sequence is reduced to a single call to the ctor

    Texture::actions.clear();
    textures.emplace_back(canvas, Area{4, 5, 8, 9});
    CHECK_EQ(std::string("A"), Texture::actions);
}

// Article
// Let func(E1, E2...) be an arbitrary function call with generic
// parameters E1, E2... we'd like to write a function wrapper...
// it forwards its parameters perfectly to some other function

// to scale an area
void func(Area& area, int s) {
    area.m_maxX = area.m_minX + (area.m_maxX - area.m_minX) * s;
    area.m_maxY = area.m_minY + (area.m_maxY - area.m_minY) * s;
}

// the const-area-ref version, this time scale is a mutable ref
void func(const Area& area, int& s) {
    s = static_cast<int>(area.m_maxX - area.m_minX);
}

// this will obviously not work if func accepts its parameters by
// reference, since wrapper() introduces a by-value passing step.
// if func modifies its by-reference parameter, it won't be visible
// in the caller of wrapper(), only the copy created by wrapper itself
// will be affected
// template<typename... Args>
// void wrapper(Args... args) { return func(args...); }

template<typename... Args>
void wrapper(Args&&... args) {
    func(std::forward<Args>(args)...);
}

// rvalues can not be bound to function parameters that are references,

// //////////////////////////////////////////////////
// The result is the reference collapsing rule.
// The rule is very simple. & always wins.
// So & & is &, and so are && & and & &&.
// The only case where && emerges from collapsing is && &&.
// You can think of it as a logical-OR, with & being 1 and && being 0.
// //////////////////////////////////////////////////

// One can see forward as a pretty wrapper around static_cast<T&&>(t)
// when T can be deduced to either U& or U&&, depending on the kind
// of argument to the wrapper (lvalue or rvalue). Now we get wrapper
// as a single template that handles all kinds of forwarding cleanly.

// NOTE:
// I must implement all the variations of func() so that:
// const-ref
// value
// rvalue-ref
// all can be handled
TEST_CASE ("") {

    /*
     *
    template <typename _Tp>
    constexpr _Tp&& forward(typename std::remove_reference<_Tp>::type &
    __t) noexcept {
        return static_cast<_Tp&&>(__t);
    }

    template <typename _Tp>
    constexpr _Tp&& forward(typename std::remove_reference<_Tp>::type &&
    __t) noexcept {
        static_assert(!std::is_lvalue_reference<_Tp>::value,
                      "template argument"
                      " substituting _Tp is an lvalue reference type");
        return static_cast<_Tp&&>(__t);
    }
    */

    Area area{4, 5, 4, 5};

    // area is an lvalue, therefore it calls forward<Area&>()
    // Area& forward(Area& area) noexcept {
    //   return static_cast<Area&>(area);
    // }
    // the func invoked is
    // void func(Area& area, int s)
    wrapper(area, 4);
    CHECK_EQ(area.m_maxX,  8);
    CHECK_EQ(area.m_maxY, 8);

    int scale = 4;
    // area now is a rvalue, therefore it calls forward<Area>
    // the func invoked is
    // void func(const Area& area, int& s)
    wrapper(Area{4, 5, 4, 5}, scale);
    CHECK_EQ(scale, 1);
}
