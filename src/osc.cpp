#include "osc.h"
#include "luts.h"
#include "misc.h"


void osc::Saw::note_on(uint8_t note, uint8_t /*velocity*/) {
    note_ = note;
    p_incr = luts::m_to_incr[note];
}

void osc::Saw::note_off(uint8_t /*note*/, uint8_t /*velocity*/) {
}

int32_t osc::Saw::process() {
    sample = misc::u32_to_s32(phase);

    phase += p_incr; // no need to wrap phase as uint32 overflow does that for us

    return sample;
}

void osc::PolyBLEPSaw::note_on(uint8_t note, uint8_t /*velocity*/) {
    note_ = note;
    p_incr = luts::m_to_incr[note];
}

void osc::PolyBLEPSaw::note_off(uint8_t /*note*/, uint8_t /*velocity*/) {
}

int32_t osc::PolyBLEPSaw::process() {
    sample = misc::u32_to_s32(phase);
    sample -= misc::polyblep(phase, p_incr);

    phase += p_incr; // no need to wrap phase as uint32 overflow does that for us

    return sample;
}

void osc::KarplusStrong::note_on(uint8_t /*note*/, uint8_t /*velocity*/) {
    for (size_t i=0; i<forward.length(); i++) {
        forward.write(misc::fast_rand());
    }
}

void osc::KarplusStrong::note_off(uint8_t /*note*/, uint8_t /*velocity*/) {
}

int32_t osc::KarplusStrong::process() {
    int32_t output = forward.read();

    int32_t input = lp.process(output);
    input *= 0.99;
    forward.write(input);

    return output;
}
