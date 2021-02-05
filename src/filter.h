#pragma once
#include <stdint.h>

namespace filter {
    struct LP {
        int32_t sample {};

        int32_t process(int32_t input);
    };
}
