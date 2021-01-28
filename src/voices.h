#pragma once
#include <stdint.h>

namespace osc {
    constexpr uint8_t n_voices {16};
    template<typename T>
    struct VoiceManager {
        std::array<T, n_voices> voices {};
        std::array<T*, 127> notes {};

        int32_t process() {
            int32_t sample = 0;

            for (auto &voice : voices) {
                if (voice.is_active()) {
                    sample += voice.process() / n_voices;
                }
            }

            return sample;
        }

        void note_on(const int note, const int velocity=127) {
            for (auto &voice : voices) {
                if (!voice.is_active()) {
                    voice.note_on(note, velocity);
                    notes[note] = &voice;
                    break;
                }
            }
        }

        void note_off(const int note, const int velocity=127) {
            if (notes[note]) {
                notes[note]->note_off(velocity, note);
                notes[note] = nullptr;
            }
        }
    };
}
