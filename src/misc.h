#pragma once
#include <stdint.h>


namespace misc {
    constexpr float tuning {440.f};
#ifdef AUDIO_SAMPLE_RATE_EXACT
    constexpr uint16_t samplerate {(uint16_t) AUDIO_SAMPLE_RATE_EXACT};
#else
    constexpr uint16_t samplerate {48000U};
#endif
    constexpr uint32_t random_seed {42U}; // must be non-zero!!

    float m_to_f(const uint8_t note, const float tuning=tuning);
    uint32_t m_to_incr(const uint8_t note);

    uint16_t sr_to_us(const uint16_t sr=samplerate);

    inline int32_t u32_to_s32(const uint32_t x) {
        return x + INT32_MIN;
    }

    inline uint32_t s32_to_u32(const int32_t x) {
        return (uint32_t) x - (uint32_t) INT32_MIN;
    }

    inline uint16_t s32_to_u12(const int32_t x) {
        return misc::s32_to_u32(x) >> (32 - 12);  // (x - INT32_MIN) >> 20 === (x >> 20) + 0x800
    }

    inline int16_t s32_to_s16(const int32_t x) {
        return x >> (32 - 16);
    }

    inline float s32_to_float(const int32_t x) {
        return (float) x / (float) INT32_MAX;
    }

    uint32_t fast_rand();
    float fast_float_rand();
    uint8_t random_note(uint8_t min=0, uint8_t max=127);

    // PolyBLEP is normally calculated for phases going from 0 to 1
    // This is an integer version so it will work for phases from 0..max
    // Change max and types to your needs.
    inline uint32_t polyblep(uint32_t p, uint32_t dp) {
        constexpr uint32_t max {UINT32_MAX};

        if (p < dp) {
            p /= dp;
            return -(p * p * max)/2 + p * max - max/2;

        } else if (max - p < dp) {
            p -= max;
            p /= dp;
            return (p*p*max)/2 + p*max + max/2;
        }
        return 0;
    }
}
