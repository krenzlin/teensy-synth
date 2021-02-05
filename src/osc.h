#pragma once
#include <stdint.h>
#include "delay.h"


namespace osc {
    class Saw {
        uint32_t phase {(uint32_t) INT32_MIN};
        uint32_t p_incr {0};
        int32_t sample{0};
        uint8_t note_ {0};

        public:
            void note_on(uint8_t note, uint8_t velocity=127);
            void note_off(uint8_t note, uint8_t velocity=127);
            int32_t process();
    };

    class PolyBLEPSaw {
        uint32_t phase {(uint32_t) INT32_MIN};
        uint32_t p_incr {0};
        int32_t sample{0};
        uint8_t note_ {0};

        public:
            void note_on(uint8_t note, uint8_t velocity=127);
            void note_off(uint8_t note, uint8_t velocity=127);
            int32_t process();
    };

    class KarplusStrong {
        Delay<uint32_t, 110> forward;
        Delay<uint32_t, 1> backward;

        public:
            void note_on(uint8_t note, uint8_t velocity=127);
            void note_off(uint8_t note, uint8_t velocity=127);
            int32_t process();
    };
}
