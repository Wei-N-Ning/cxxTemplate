//
// Created by wein on 1/09/18.
//

// source
// Eli Bendersky's website:
// https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c
//
// his inspirational article compensates Scott Meyer's Effect Modern C++
// and provides more explanation on when to use forwarding.

#include <vector>
#include <string>
#include <cassert>

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

    static std::string actions;
private:
    Canvas m_canvas;
    Area m_area;
};

std::string Texture::actions;

void emplace_construct() {
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
    assert(std::string("AMD") == Texture::actions);

    // NOTE: vector needs to allocate new storage space for the newly
    // created element - this result in a different code path to the
    // emplace-construction code path
    // with GCC 7, it calls insert(end(), std::forward<...>()...)
    // therefore it still creates a temporary object (so that insert()
    // can work)
    Texture::actions.clear();
    textures.emplace_back(canvas, Area{1, 1, 2, 2});
    assert(std::string("AMD") == Texture::actions);

    // At this time, the storage space is enough for emplace-construction,
    // so the action sequence is reduced to a single call to the ctor
    textures.reserve(4);
    Texture::actions.clear();
    textures.emplace_back(canvas, Area{4, 5, 8, 9});
    assert(std::string("A") == Texture::actions);
    //Area smallArea{1, 1, 2, 2};

}

int main() {
    emplace_construct();
    return 0;
}