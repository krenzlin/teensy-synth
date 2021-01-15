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


uint32_t max_us {0};
uint32_t alltime_max_us {0};

void audio_loop() {
    uint32_t start = micros();
    start = micros();

    dac.write((saw.process() >> 1) + (saw2.process() >> 1));

    uint32_t us = micros() - start;
    if (us > max_us) max_us = us;
    if (us > alltime_max_us) alltime_max_us = us;
}

extern "C" int main(void) {
    while (!Serial); // wait for serial monitor
    Serial.begin(9600);

    saw.note_on(69, 127);
    saw2.note_on(69+5, 127);


    timer.begin(audio_loop, misc::sr_to_us());

    static uint8_t note {69};
    while(1) {
        delay(1000);
        note = misc::random_note(50, 80);
        saw.note_on(note);
        saw2.note_on(note+5);
        Serial.println("----");
        Serial.print("us: ");
        Serial.print(max_us);
        Serial.print(" | ");
        Serial.println(alltime_max_us);
        max_us = 0;

    }
}
