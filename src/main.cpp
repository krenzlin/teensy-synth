#include "IntervalTimer.h"
#include <stdint.h>
#include "dac.h"
#include "misc.h"


hal::DAC dac;
IntervalTimer timer;
uint16_t m_to_incr[127];

void audio_loop() {
    static uint32_t phase{0};

    dac.write(phase);

    phase += m_to_incr[69];
}


extern "C" int main(void) {
    for (auto i=0; i<127; i++) {
        m_to_incr[i] = misc::m_to_incr(i);
    }

    timer.begin(audio_loop, misc::sr_to_us());
}
