#include "misc.h"
#include <math.h>


float misc::m_to_f(const uint8_t note, const float tuning) {
    return pow(2.0, (note - 69.0)/12.0) * tuning;
}

uint16_t misc::m_to_incr(const uint8_t note) {
    return misc::m_to_f(note) / (float) misc::samplerate * misc::max_dac_value;
}

uint16_t misc::sr_to_us(const uint16_t sr) {
    return 1000000 / sr;
}
