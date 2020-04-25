//
// Created by wein on 4/29/18.
//
// see:
// https://stackoverflow.com/questions/34519073/inherit-singleton
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <type_traits>
#include <cassert>

namespace impl {
template<class T>
class ISingleton
{
protected:
    ISingleton() noexcept = default;
    ISingleton(const ISingleton &) = delete;
    ISingleton &operator=(const ISingleton &) = delete;
    virtual ~ISingleton() = default;

public:
    inline static T& instance() noexcept(std::is_nothrow_constructible<T>::value) {
        // Guaranteed to be destroyed.
        // Instantiated on first use.
        // Thread safe in C++11
        static T instance;
        return instance;
    }
};
}

class VIP : public impl::ISingleton<VIP> {

    friend class impl::ISingleton<VIP>;

public:
    void setCredit(int &&c) {
        m_credit = c;
    }
    int credit() {
        return m_credit;
    }

private:
    VIP() :m_credit(0) {};
    ~VIP() = default;
    int m_credit;
};

TEST_CASE ("") {
    CHECK_EQ(0, VIP::instance().credit());
    VIP::instance().setCredit(130);
    CHECK_EQ(130, VIP::instance().credit());
}
