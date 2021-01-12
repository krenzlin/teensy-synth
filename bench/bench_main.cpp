#define PICOBENCH_IMPLEMENT_WITH_MAIN
#include "picobench/picobench.hpp"

#include "osc.h"

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
