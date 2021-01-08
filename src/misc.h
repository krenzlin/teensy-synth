#pragma once
#include <stdint.h>


namespace misc {
    constexpr float tuning = 440.f;
    constexpr uint16_t samplerate = 44100U;
    constexpr uint16_t max_dac_value = (1 << 12);

    float m_to_f(const uint8_t note, const float tuning=tuning);
    uint16_t f_to_incr(const float f, const uint16_t sr=samplerate, const uint16_t max=max_dac_value);
    uint16_t m_to_incr(const uint8_t note);

    uint16_t sr_to_us(const uint16_t sr=samplerate);

    inline uint16_t wrap(const uint16_t phase, const uint16_t max=max_dac_value) {
        if (phase > max) {
            return phase - max;
        }
        return phase;
    }
}
