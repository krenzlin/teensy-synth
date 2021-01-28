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
}
