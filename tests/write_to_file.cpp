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

float int32_to_float(int32_t x) {
    return x / INT32_MAX;
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("error: no output file name");
        return -1;
    }

    auto osc = osc::PolyBLEPSaw();

    uint16_t bpm {120};

    auto writer = WavWriter(1, misc::samplerate, 10); // channels, sr, duration in s
    writer.Open(argv[1]);

    while (!writer.done()) {
        for (auto i=0; i<100; i++) {
            auto note = misc::random_note(60, 80);
            osc.note_on(note);
            int32_t sample = osc.process();
            float f_sample = int32_to_float(sample);
            writer.Write(&f_sample, 1);
        }
    }

}

#endif
