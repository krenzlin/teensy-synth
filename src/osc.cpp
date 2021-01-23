#include "osc.h"
#include "luts.h"
#include "misc.h"


void osc::Saw::note_on(uint8_t note, uint8_t /*velocity*/) {
    p_incr = luts::m_to_incr[note];
}

int32_t osc::Saw::process() {
    sample = misc::u32_to_s32(phase);

    phase += p_incr; // no need to wrap phase as uint32 overflow does that for us

    return sample;
}
