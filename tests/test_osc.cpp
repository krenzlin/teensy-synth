#include "doctest.h"
#include "osc.h"

TEST_CASE("raising saw") {
    osc::Saw saw;

    saw.note_on(69);

    int32_t old = saw.process();
    REQUIRE(saw.process() > old);
}

TEST_CASE("test values of Saw") {
    osc::Saw saw;

    saw.note_on(69);

    REQUIRE(saw.process() == 0);
}


TEST_CASE("two saws") {
    // Sanity checks that two different notes have different phase increments
    osc::Saw saw1;
    osc::Saw saw2;

    saw1.note_on(69);
    saw2.note_on(70);

    int32_t phase = saw1.process();
    uint32_t p_incr_1 = saw1.process() - phase;

    phase = saw2.process();
    uint32_t p_incr_2 = saw2.process() - phase;

    REQUIRE(p_incr_1 != p_incr_2);
    REQUIRE(p_incr_1 > 0);
    REQUIRE(p_incr_2 > 0);
    REQUIRE(p_incr_2 > p_incr_1);
}

TEST_CASE("stupid test for PolyBLEPSaw") {
    osc::PolyBLEPSaw saw;

    saw.note_on(69);

    // due to polyblep residual first sample is not zero but above
    // so first sample will be higher than the next one

    int32_t old = saw.process();
    REQUIRE(saw.process() < old);  // compare this to naive saw
}
