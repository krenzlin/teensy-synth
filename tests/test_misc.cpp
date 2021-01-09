#include "catch.hpp"
#include "misc.h"


TEST_CASE("midi to freq", "[misc]") {
    REQUIRE(misc::m_to_f(69) == 440.0);
}

TEST_CASE("samplerate to microseconds", "[misc]") {
    REQUIRE(misc::sr_to_us(44100) == 22);
}

TEST_CASE("signed 32 bit to unsigned 12 bit", "[misc]") {
    REQUIRE(misc::s32_to_u12(0) == 2048);
    REQUIRE(misc::s32_to_u12(INT32_MAX) == 4095);
    REQUIRE(misc::s32_to_u12(INT32_MIN) == 0);
    REQUIRE(misc::s32_to_u12(-1) == 2047);
    REQUIRE(misc::s32_to_u12(1<<20) == 2049); // next step is only after 20 bits set
}
