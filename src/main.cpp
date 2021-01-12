#include "WProgram.h"
#include "IntervalTimer.h"
#include <stdint.h>
#include "dac.h"
#include "misc.h"
#include "osc.h"


hal::DAC dac;
IntervalTimer timer;
osc::Saw saw{};


void audio_loop() {
    dac.write(saw.process());
}


extern "C" int main(void) {
    saw.note_on(69, 127);

    timer.begin(audio_loop, misc::sr_to_us());
}
