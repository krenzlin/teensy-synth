#pragma once
#include <stdint.h>
#include "misc.h"
#include "ADSR.h"

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

        void set_env(float value) {
            for (auto &voice: voices) {
                voice.set_env(value);
            }
        }
    };

    template<typename T>
    class Env : public T {
        ADSR env;

        public:
        bool is_active() {
            return env.getState();
        }

        void note_on(const int note, const int velocity=127) {
            env.reset();
            env.gate(true);
            T::note_on(note, velocity);
        }

        void note_off(uint8_t note, uint8_t velocity=127) {
            env.gate(false);
            T::note_off(note, velocity);
        }

        void set_ADSR(float attack, float decay, float sustain, float release) {
            env.setAttackRate(attack * misc::samplerate);
            env.setDecayRate(decay * misc::samplerate);
            env.setSustainLevel(sustain);
            env.setReleaseRate(release * misc::samplerate);
        }

        int32_t process() {
            if (!is_active()) {
                return 0;
            }
            return T::process() * env.process();
        }

        // one-knob ADSR
        void set_env(float value) {
            set_ADSR(value, 0, 1.0, value);
        }
    };

    using PolySaw = VoiceManager<Env<PolyBLEPSaw>>;
}
