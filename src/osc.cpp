#include "osc.h"
#include "luts.h"
#include "misc.h"
#include "AudioStream.h"

void osc::Saw::note_on(uint8_t note, uint8_t /*velocity*/) {
    p_incr = luts::m_to_incr[note];
}

int32_t osc::Saw::process() {
    sample = misc::u32_to_s32(phase);

    phase += p_incr; // no need to wrap phase as uint32 overflow does that for us

    return sample;
}

void osc::AudioSaw::update() {
    audio_block_t *block;
    block = allocate();
    if (block == NULL) return;

    for (auto i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        block->data[i] = misc::s32_to_s16(saw.process());
    }

    transmit(block);
    release(block);
}

void osc::AudioSaw::note_on(uint8_t note, uint8_t velocity) {
    this->saw.note_on(note, velocity);
}
