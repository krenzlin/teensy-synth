#include "misc.h"
#include <math.h>


float misc::m_to_f(const uint8_t note, const float tuning) {
    return pow(2.f, (note - 69.f)/12.f) * tuning;
}

uint32_t misc::m_to_incr(const uint8_t note) {
    return misc::m_to_f(note) / (float) misc::samplerate * UINT32_MAX;
}

uint32_t misc::f_to_incr(const float freq) {
    return freq / (float) misc::samplerate * UINT32_MAX;
}

uint16_t misc::sr_to_us(const uint16_t sr) {
    return 1000000U / sr;
}

/* Fast random implementation
see https://en.wikipedia.org/wiki/Lehmer_random_number_generator

X_k+1 = a * X_k mod m

common parameters

m = 2^31 − 1 = 2,147,483,647 (Mersenne prime M31) = 0x7fffffff
a = 7^5 = 16,807
update: a = 48271

important: random seed must not be zero
*/
uint32_t misc::fast_rand() {
    static uint32_t X_k {misc::random_seed};
    const uint32_t a {48271U};
    const uint32_t m {2147483647U};

    X_k = (a * X_k) % m;
    return X_k;
}

// range [0..1.0)
float misc::fast_float_rand() {
    static uint32_t X_k {misc::random_seed};
    constexpr uint32_t a {48271U};
    constexpr float m_1 {4.6566129e-010f}; // 1/(2^31-1) = 1/2147483647

    X_k *=  a;
    return (float) X_k * m_1 / 2.f;
}

uint8_t misc::random_note(uint8_t min, uint8_t max) {
    uint8_t range = max - min + 1;
    return min + misc::fast_float_rand() * range;
}
