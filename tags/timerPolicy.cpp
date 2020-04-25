//
// Created by wein on 4/29/18.
//
// study note taken from wkou/WKContext: PTimer
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <cstdint>

namespace tags {
using TAG = uint32_t;  // to categorize policy and impl classes
const TAG DUKE3D{0x101};
const TAG DOOM{0x99};
const TAG DUNE2{0x11};
}

namespace policy {

template<tags::TAG tag_>
class PTimer;  // to be provided by application logic

}

namespace impl {

template<tags::TAG tag_>
class Timer : public policy::PTimer<tag_> {
public:
    using timer_p = policy::PTimer<tag_>;
    using real_t = typename timer_p::real_t;  // must be fulfilled by concrete policy

    real_t now() {
        return timer_p::now();
    }
};

}

// imagine this was in a different translation unit
namespace policy {

// DOOM says now is 3.0
template<>
class PTimer<tags::DOOM> {
public:
    using real_t = double;

    static double now() {
        return 3.00;
    }
};

// DUKE3D says now is 6
template<>
class PTimer<tags::DUKE3D> {
public:
    using real_t = int;

    static int now() {
        return 6;
    }
};

}

TEST_CASE ("") {
    impl::Timer<tags::DOOM> doomTimer;
    CHECK_EQ(3.0, doomTimer.now());
    impl::Timer<tags::DUKE3D> duke3dTimer;
    CHECK_EQ(6, duke3dTimer.now());
}
