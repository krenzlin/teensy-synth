#include "dac.h"
#include "core_pins.h"


hal::DAC::DAC() {
    analogWriteResolution(12);
}

void hal::DAC::write(uint16_t sample) {
    analogWriteDAC0(sample);
}
