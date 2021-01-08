#include "WProgram.h"

const uint16_t max_dac = 1 << 12;

extern "C" int main(void) {
    analogWriteResolution(12);

	static uint16_t phase_1{0};
	static uint16_t phase_2{0};


	while (1) {
        analogWriteDAC0((phase_1 + phase_2) >> 1);

        phase_1 += 2;
        phase_2 += 6;
        if (phase_1 > max_dac) {
            phase_1 -= max_dac;
        }
		if (phase_2 > max_dac) {
            phase_2 -= max_dac;
        }
	}
}
