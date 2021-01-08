#include "misc.h"
#include <math.h>


float misc::m_to_f(uint8_t note, float tuning) {
    return pow(2.0, (note - 69.0)/12.0) * tuning;
}
