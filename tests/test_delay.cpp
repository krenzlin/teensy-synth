#include "doctest.h"
#include <stdint.h>
#include "delay.h"


TEST_CASE("create delay with length") {
    Delay<int32_t, 41> delay;

    REQUIRE(delay.length() == 41);
}

TEST_CASE("empty delay returns zero") {
    Delay<int32_t, 41> delay;

    REQUIRE(delay.update() == 0);
}

TEST_CASE("delay returns input after N updates") {
    constexpr size_t N = 3;
    Delay<int32_t, N> delay;

    for (size_t i=0; i<N*2; i++) {
        CAPTURE(N);
        CAPTURE(i);
        if (i<N) {
            REQUIRE(delay.update(i) == 0);
        } else {
            REQUIRE(delay.update(i) == i - N);
        }
    }
}
