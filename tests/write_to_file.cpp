#ifndef ARDUINO

#include <iostream>
#include <stdio.h>
#include <string>

#include "osc.h"
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

    auto osc = osc::Saw();

    auto writer = WavWriter(1, misc::samplerate, 10); // channels, sr, duration in s
    writer.Open(argv[1]);

    auto note = 88;
    while (!writer.done()) {
        osc.note_on(note);
        for (auto i=0; i<misc::samplerate/4; i++) {
            int32_t sample = osc.process();
            float f_sample = misc::s32_to_float(sample);
            //printf("%d -> %f\n", sample, f_sample);
            writer.Write(&f_sample, 1);
        }
        //note += 1;
    }

}

#endif
