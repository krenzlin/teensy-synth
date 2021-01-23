#include "Audio.h"
#include "osc.h"
#include "misc.h"

#define AUDIO_BLOCK_SAMPLES 128


template<typename T>
class AudioObject : public AudioStream {
    private:
        T osc;

    public:
        AudioObject() : AudioStream(0, NULL) {};
        void update(void) {
            auto block = allocate();
            if (block == NULL) return;

            for (auto i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
                block->data[i] = misc::s32_to_s16(osc.process());
            }

            transmit(block);
            release(block);
        }

        void note_on(uint8_t note, uint8_t velocity=127) {
            osc.note_on(note, velocity);
        }
};

using Saw = AudioObject<osc::Saw>;