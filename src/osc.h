#pragma once
#include <stdint.h>


namespace osc {
    class Saw {
        uint32_t phase{0};
        uint32_t p_incr {0};
        int32_t sample{0};

        public:
            void note_on(uint8_t note, uint8_t velocity=127);
            int32_t process();
    };
}
