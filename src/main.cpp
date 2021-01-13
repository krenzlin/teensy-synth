#include "WProgram.h"
#include "IntervalTimer.h"
#include <stdint.h>
#include "dac.h"
#include "misc.h"
#include "osc.h"


hal::DAC dac;
IntervalTimer timer;
osc::Saw saw{};
osc::Saw saw2{};


void audio_loop() {
    dac.write((saw.process() >> 1) + (saw2.process() >> 1));
}

extern "C" int main(void) {
    saw.note_on(69, 127);
    saw2.note_on(69+5, 127);


    timer.begin(audio_loop, misc::sr_to_us());

    static uint8_t note {69};
    while(1) {
        delay(1000);
        note = misc::random_note(50, 80);
        saw.note_on(note);
        saw2.note_on(note+5);
    }
}
