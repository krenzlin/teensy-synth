#include "IntervalTimer.h"
#include <stdint.h>
#include "dac.h"
#include "misc.h"


hal::DAC dac;
IntervalTimer timer;
uint16_t m_to_incr[127];

void audio_loop() {
    static uint16_t phase_1{0};
	static uint16_t phase_2{0};

    dac.write((phase_1 + phase_2) >> 1);

    phase_1 += m_to_incr[69];
    phase_2 += m_to_incr[59];

    phase_1 = misc::wrap(phase_1);
    phase_2 = misc::wrap(phase_2);
}


extern "C" int main(void) {
    for (auto i=0; i<127; i++) {
        m_to_incr[i] = misc::m_to_incr(i);
    }

    timer.begin(audio_loop, misc::sr_to_us());
}
