#include "dac.h"
#include "core_pins.h"
#include "misc.h"


hal::DAC::DAC() {
    analogWriteResolution(12);
}

void hal::DAC::write(uint16_t sample) {
    //analogWriteDAC0(sample);
}

void hal::DAC::write(int32_t sample) {
    //analogWriteDAC0(misc::s32_to_u12(sample));
}

void hal::DAC::write(uint32_t sample) {
    //analogWriteDAC0(sample >> 20);
}
