#include "picobench/picobench.hpp"

#include "osc.h"

PICOBENCH_SUITE("benchmark Saw::process");

// Benchmarking function written by the user:
static void saw_process(picobench::state& s)
{
    osc::Saw saw;
    saw.note_on(69);

    s.start_timer(); // Manual start
    for (auto _ : s) {
        saw.process();
    }
    s.stop_timer(); // Manual stop
}

PICOBENCH(saw_process).baseline(); // Register the above function with picobench as baseline

static void two_saw_process(picobench::state& s)
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

PICOBENCH(two_saw_process);

static void note_on(picobench::state& s)
{
    osc::Saw saw;

    s.start_timer(); // Manual start
    for (auto _ : s) {
        saw.note_on(69);
    }
    s.stop_timer(); // Manual stop
}

PICOBENCH(note_on);

static void process_with_note_on(picobench::state& s)
{
    osc::Saw saw;

    s.start_timer();
    saw.note_on(69);
    for (auto _ : s) {
        saw.process();
    }
    s.stop_timer();
}

PICOBENCH(process_with_note_on);
