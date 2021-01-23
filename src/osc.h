#pragma once
#include <stdint.h>
#include "Audio.h"

#define AUDIO_BLOCK_SAMPLES 128

namespace osc {
    class Saw {
        uint32_t phase{0};
        uint32_t p_incr {0};
        int32_t sample{0};

        public:
            void note_on(uint8_t note, uint8_t velocity=127);
            int32_t process();
    };

    class AudioSaw : public AudioStream {
        private:
            Saw saw;

        public:
            AudioSaw() : AudioStream(0, NULL) {saw.note_on(69);};
            void update(void);
            void note_on(uint8_t note, uint8_t velocity=127);
    };
}
