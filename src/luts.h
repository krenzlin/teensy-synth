#pragma once
#include <stdint.h>
#include <array>
#include "misc.h"

namespace luts {

    const auto m_to_incr = []() {
        std::array<uint32_t, 128> lut;
        for (auto i=0; i<=127; i++) {
            auto f = misc::m_to_f(i);
            lut[i] = misc::f_to_incr(f);
        }
        return lut;
    }();
}
