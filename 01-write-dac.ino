#include "Arduino.h"


void setup() {
    analogWriteResolution(12);
}

void loop() {
    static uint16_t phase{0};

    analogWriteDAC0(phase);

    phase += 5;
    if (phase >= 4095) {
        phase -= 4095;
    }
}
