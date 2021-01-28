#include "picobench/picobench.hpp"

#include "osc.h"

PICOBENCH_SUITE("benchmark Saw and PolyBLEPSaw");

// Benchmarking function written by the user:
static void saw(picobench::state& s)
{
    osc::Saw saw;
    saw.note_on(69);

    s.start_timer(); // Manual start
    for (auto _ : s) {
        saw.process();
    }
    s.stop_timer(); // Manual stop
}

PICOBENCH(saw).baseline(); // Register the above function with picobench as baseline

static void two_saws(picobench::state& s)
{
    osc::Saw saw1;
    osc::Saw saw2;

    saw1.note_on(69);
    saw2.note_on(69);


    s.start_timer(); // Manual start
    for (auto _ : s) {
        saw1.process();
        saw2.process();
    }
    s.stop_timer(); // Manual stop
}

PICOBENCH(two_saws);

static void note_on(picobench::state& s)
{
    osc::Saw saw;

    s.start_timer();
    saw.note_on(69);
    for (auto _ : s) {
        saw.process();
    }
    s.stop_timer();
}

PICOBENCH(note_on);


// PolyBLEPSaw

static void polyblep_saw(picobench::state& s)
{
    osc::PolyBLEPSaw saw;

    s.start_timer();
    saw.note_on(69);
    for (auto _ : s) {
        saw.process();
    }
    s.stop_timer();
}

PICOBENCH(polyblep_saw);
