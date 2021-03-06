#include "Audio.h"
#include "osc.h"
#include "voices.h"
#include "misc.h"

#define AUDIO_BLOCK_SAMPLES 128


template<typename T>
class AudioObject : public AudioStream, public T {
    public:
        AudioObject() : AudioStream(0, NULL) {};

        void update(void) {
            auto block = allocate();
            if (block == NULL) return;

            for (auto i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
                block->data[i] = misc::s32_to_s16(T::process());
            }

            transmit(block);
            release(block);
        }
};

using AudioPolySaw = AudioObject<osc::PolySaw>;
