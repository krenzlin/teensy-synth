#pragma once
#include <stdint.h>
#include "misc.h"

namespace luts {

    const auto m_to_incr = []() {
        uint32_t lut[128];
        for (auto i=0; i<=127; i++) {
            auto f = misc::m_to_f(i);
            lut[i] = misc::f_to_incr(f);
        }
        return lut;
    }();
}
