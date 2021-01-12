#pragma once
#include <stdint.h>


namespace misc {
    constexpr float tuning {440.f};
    constexpr uint16_t samplerate {50000U};
    constexpr uint32_t random_seed {42U}; // must be non-zero!!

    float m_to_f(const uint8_t note, const float tuning=tuning);
    uint32_t m_to_incr(const uint8_t note);

    uint16_t sr_to_us(const uint16_t sr=samplerate);

    inline int32_t u32_to_s32(const uint32_t x) {
        return x + INT32_MIN;
    }

    inline uint32_t s32_to_u32(const int32_t x) {
        return x - INT32_MIN;
    }

    inline uint16_t s32_to_u12(const int32_t x) {
        return misc::s32_to_u32(x) >> (32 - 12);  // (x - INT32_MIN) >> 20 === (x >> 20) + 0x800
    }

    uint32_t fast_rand();
    float fast_float_rand();
}
