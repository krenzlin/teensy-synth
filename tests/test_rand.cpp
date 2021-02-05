#include "doctest.h"
#include "misc.h"


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

TEST_CASE("fast_rand distribution") {
    constexpr auto bits {3};
    constexpr auto n_buckets {1 << bits};
    constexpr auto iters {100000};
    constexpr int expected {iters / n_buckets};

    int buckets[n_buckets] = {};

    for (auto i=0; i<iters; i++) {
        uint32_t value = misc::fast_rand();
        uint8_t bucket = value >> (32 - bits);
        REQUIRE(bucket >= 0);
        REQUIRE(bucket < n_buckets);
        buckets[bucket]++;
    }

    for (auto n=0; n<n_buckets; n++) {
        CAPTURE(buckets[n]);
        CHECK(buckets[n] == doctest::Approx(expected).epsilon(0.01));
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
