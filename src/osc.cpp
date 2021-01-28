#include "osc.h"
#include "luts.h"
#include "misc.h"

bool osc::Saw::is_active() {
    return active;
}

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
    if (!is_active()) {
        return 0;
    }
    sample = misc::u32_to_s32(phase);

    phase += p_incr; // no need to wrap phase as uint32 overflow does that for us

    return sample;
}

bool osc::PolyBLEPSaw::is_active() {
    return active;
}

void osc::PolyBLEPSaw::note_on(uint8_t note, uint8_t /*velocity*/) {
    note_ = note;
    p_incr = luts::m_to_incr[note];
    active = true;
}

void osc::PolyBLEPSaw::note_off(uint8_t /*note*/, uint8_t /*velocity*/) {
    active = false;
}

int32_t osc::PolyBLEPSaw::process() {
    if (!is_active()) {
        return 0;
    }
    sample = misc::u32_to_s32(phase);
    sample -= misc::polyblep(phase, p_incr);

    phase += p_incr; // no need to wrap phase as uint32 overflow does that for us

    return sample;
}
