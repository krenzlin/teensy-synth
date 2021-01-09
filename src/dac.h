#pragma once
#include <stdint.h>

namespace hal {
    class DAC {
        public:
            DAC();
            void write(uint16_t);
            void write(int32_t);
    };
}
