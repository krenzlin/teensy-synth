#include "WProgram.h"
#include "misc.h"

constexpr int sr = 44100;
constexpr uint16_t max_dac = 1 << 12;

inline uint16_t wrap(const uint16_t phase, uint16_t max = max_dac) {
    if (phase > max) {
        return phase - max;
    }
    return phase;
}


IntervalTimer timer;
uint16_t m_to_incr[127];


void audio_loop() {
    static uint16_t phase_1{0};
	static uint16_t phase_2{0};

    analogWriteDAC0((phase_1 + phase_2) >> 1);

    phase_1 += m_to_incr[69];
    phase_2 += m_to_incr[58];

    phase_1 = wrap(phase_1);
    phase_2 = wrap(phase_2);

}


extern "C" int main(void) {

    for (auto i=0; i<127; i++) {
        m_to_incr[i] = misc::m_to_f(i) / sr * max_dac;
    }

    analogWriteResolution(12);

    constexpr int update_us = 1000000 / sr;

    timer.begin(audio_loop, update_us);
}
