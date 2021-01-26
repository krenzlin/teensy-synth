#include "osc.h"
#include "luts.h"
#include "misc.h"


void osc::Saw::note_on(uint8_t note, uint8_t /*velocity*/) {
    note_ = note;
    p_incr = luts::m_to_incr[note];
    active = true;
}

void osc::Saw::note_off(uint8_t note, uint8_t /*velocity*/) {
    if (note == note_) {
        active = false;
    }
}

int32_t osc::Saw::process() {
    if (!active) {
        return 0;
    }
    sample = misc::u32_to_s32(phase);

    phase += p_incr; // no need to wrap phase as uint32 overflow does that for us

    return sample;
}

void osc::PolyBLEPSaw::note_on(uint8_t note, uint8_t /*velocity*/) {
    p_incr = luts::m_to_incr[note];
}

int32_t osc::PolyBLEPSaw::process() {
    sample = misc::u32_to_s32(phase);
    sample -= misc::polyblep(phase, p_incr);

    phase += p_incr; // no need to wrap phase as uint32 overflow does that for us

    return sample;
}
