#ifndef ARDUINO

#include <iostream>
#include <stdio.h>
#include <string>

#include "osc.h"
#include "voices.h"
#include "misc.h"

#include "wav_writer.h"
using stmlib::WavWriter;


int16_t bitcrush(int16_t x, uint8_t depth) {
    uint8_t reduce_by {16 - depth};
    return (x >> reduce_by) << reduce_by;
}


int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("error: no output file name");
        return -1;
    }

    auto osc = osc::PolySaw();

    auto writer = WavWriter(1, misc::samplerate, 10); // channels, sr, duration in s
    writer.Open(argv[1]);

    float env = 0.f;

    while (!writer.done()) {
        osc.set_env(env);

        osc.note_on(70);
        osc.note_on(75);
        for (auto i=0; i<misc::samplerate/2; i++) {
            int32_t sample = osc.process();
            float f_sample = misc::s32_to_float(sample);
            writer.Write(&f_sample, 1);
        }

        osc.note_off(70);
        osc.note_off(75);
        for (auto i=0; i<misc::samplerate/2; i++) {
            int32_t sample = osc.process();
            float f_sample = misc::s32_to_float(sample);
            writer.Write(&f_sample, 1);
        }
        env += 0.1f;
    }

}

#endif
