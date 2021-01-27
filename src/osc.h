#pragma once
#include <stdint.h>
#include <array>


namespace osc {
    class Saw {
        bool active {false};
        uint32_t phase {(uint32_t) INT32_MIN};
        uint32_t p_incr {0};
        int32_t sample{0};
        uint8_t note_ {0};

        public:
            bool is_active();
            void note_on(uint8_t note, uint8_t velocity=127);
            void note_off(uint8_t note, uint8_t velocity=127);
            int32_t process();
    };

    class PolyBLEPSaw {
        bool active {false};
        uint32_t phase {(uint32_t) INT32_MIN};
        uint32_t p_incr {0};
        int32_t sample{0};
        uint8_t note_ {0};

        public:
            bool is_active();
            void note_on(uint8_t note, uint8_t velocity=127);
            void note_off(uint8_t note, uint8_t velocity=127);
            int32_t process();
    };

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
