#include "catch.hpp"
#include "misc.h"


TEST_CASE("midi to freq", "[misc]") {
    REQUIRE(misc::m_to_f(69) == 440.0);
}

TEST_CASE("samplerate to microseconds", "[misc]") {
    REQUIRE(misc::sr_to_us(44100) == 22);
}

TEST_CASE("wrap phase", "[misc]") {
    REQUIRE(misc::wrap(4096) == 0);
}
