#include "misc.h"
#include <math.h>


float misc::m_to_f(const uint8_t note, const float tuning) {
    return pow(2.0, (note - 69.0)/12.0) * tuning;
}

uint16_t misc::f_to_incr(const float frequency, const uint16_t sr, const uint16_t max) {
    return (uint16_t) frequency / (float) sr * max;
}

uint16_t misc::m_to_incr(const uint8_t note) {
    return misc::f_to_incr(misc::m_to_f(note));
}

uint16_t misc::sr_to_us(const uint16_t sr) {
    return 1000000 / sr;
}
