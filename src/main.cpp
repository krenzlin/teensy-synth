#include "IntervalTimer.h"
#include <stdint.h>
#include "dac.h"
#include "misc.h"


hal::DAC dac;
IntervalTimer timer;
uint32_t m_to_incr[127];


class Saw {
    uint32_t phase{0};
    uint32_t p_incr {0};
    int32_t sample{0};

    public:

        void note_on(uint8_t note, uint8_t /*velocity*/) {
            p_incr = m_to_incr[note];
        }

        int32_t process() {
            sample = misc::u32_to_s32(phase);

            phase += p_incr; // no need to wrap phase as uint32 overflow does that for us

            return sample;
        }
};


Saw saw{};


void audio_loop() {
    dac.write(saw.process());
}


extern "C" int main(void) {
    for (auto i=0; i<127; i++) {
        m_to_incr[i] = misc::m_to_incr(i);
    }

    saw.note_on(72, 127);

    timer.begin(audio_loop, misc::sr_to_us());
}
