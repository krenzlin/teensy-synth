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
    backward.clear();
}

void osc::KarplusStrong::note_off(uint8_t /*note*/, uint8_t /*velocity*/) {
}

int32_t osc::KarplusStrong::process() {
    uint32_t output = forward.read();
    uint32_t input = output / 2 + backward.read() / 2;

    backward.write(output);
    forward.write(input);

    return misc::u32_to_s32(output);
}
