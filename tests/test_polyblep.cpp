#include "doctest.h"
#include "misc.h"

TEST_CASE("polyblep") {
    REQUIRE(misc::polyblep(0, 42) == INT32_MIN/2);
}


inline float poly_blep(float p, float dp) {
    if (p < dp) {
        p /= dp;
        return p - p*p/2.f - 0.5f;
    } else if (p > 1.0f - dp) {
        p = (p - 1.0f) / dp;
        return p*p/2.f + p + 0.5f;
    }
    return 0.0f;
}


TEST_CASE("compare int to float version") {
    uint32_t dp = misc::f_to_incr(440.0);
    float dp_f = (float) dp / (float) UINT32_MAX;
    CAPTURE(dp);
    CAPTURE(dp_f);

    uint32_t p = 0;
    for (auto i=0; i<misc::samplerate; i++) {
        float p_f = (float) p / (float) UINT32_MAX;

        int32_t blep = misc::polyblep(p, dp);
        float blep_f = (float) blep / (float) INT32_MAX;

        CAPTURE(p);
        CAPTURE(p_f);
        CAPTURE(blep);

        REQUIRE(doctest::Approx(blep_f) == poly_blep(p_f, dp_f));

        p += dp;
    }
}
