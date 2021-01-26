#include "doctest.h"
#include "misc.h"


TEST_CASE("midi to freq") {
    REQUIRE(misc::m_to_f(69) == 440.0);
}

TEST_CASE("samplerate to microseconds") {
    REQUIRE(misc::sr_to_us(44100) == 22);
}

TEST_CASE("signed 32 bit to unsigned 12 bit") {
    REQUIRE(misc::s32_to_u12(0) == 2048);
    REQUIRE(misc::s32_to_u12(INT32_MAX) == 4095);
    REQUIRE(misc::s32_to_u12(INT32_MIN) == 0);
    REQUIRE(misc::s32_to_u12(-1) == 2047);
    REQUIRE(misc::s32_to_u12(1<<20) == 2049); // next step is only after 20 bits set
}

TEST_CASE("unsigned 32 bit to signed 32 bit") {
    REQUIRE(misc::u32_to_s32(0) == INT32_MIN);
    REQUIRE(misc::u32_to_s32(UINT32_MAX) == INT32_MAX);
}

TEST_CASE("signed 32 bit to unsigned 32 bit") {
    REQUIRE(misc::s32_to_u32(INT32_MIN) == 0);
    REQUIRE(misc::s32_to_u32(INT32_MAX) == UINT32_MAX);
}

TEST_CASE("signed 32 bit to signed 16 bit") {
    REQUIRE(misc::s32_to_s16(INT32_MIN) == INT16_MIN);
    REQUIRE(misc::s32_to_s16(INT32_MAX) == INT16_MAX);
}

TEST_CASE("fast_rand") {
    uint32_t old {0};
    for (auto i=0; i<1000; i++) {
        auto x = misc::fast_rand();
        REQUIRE(x >= 0);
        REQUIRE(x <= UINT32_MAX);
        REQUIRE(x != old);
        old = x;
    }
}

TEST_CASE("fast_float_rand") {
    float old {0.0f};
    for (auto i=0; i<1000; i++) {
        auto x = misc::fast_float_rand();
        REQUIRE(x >= 0.f);
        REQUIRE(x < 1.f);
        REQUIRE(x != old);
        old = x;
    }
}

TEST_CASE("random note") {
    bool non_zero {false};
    for (auto i=0; i<1000; i++) {
        auto x = misc::random_note();
        REQUIRE(x >= 0);
        REQUIRE(x <= 127);
        if (x != 0) {non_zero = true;}
    }
    REQUIRE(non_zero);  // check if not all zeroes
}

TEST_CASE("random note w/ range") {
    uint8_t min {64};
    uint8_t max {79};
    bool hit_min {false};
    bool hit_max {false};

    for (auto i=0; i<1000; i++) {
        auto x = misc::random_note(min, max);
        REQUIRE(x >= 64);
        REQUIRE(x <= 79);
        if (x == min) {hit_min = true;}
        if (x == max) {hit_max = true;}
    }
    REQUIRE(hit_min);
    REQUIRE(hit_max);
}

TEST_CASE("polyblep") {
    REQUIRE(misc::polyblep(0, 42) == -(UINT32_MAX/2));
}
