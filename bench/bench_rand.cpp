#include "picobench/picobench.hpp"
#include <stdint.h>
#include "misc.h"

PICOBENCH_SUITE("benchmark fast random implementations");

static void fast_rand(picobench::state& s)
{
     for (auto _ : s) {
         misc::fast_rand();
     }
}
PICOBENCH(fast_rand);


static void fast_float_rand(picobench::state& s)
{
     for (auto _ : s) {
         misc::fast_float_rand();
     }
}
PICOBENCH(fast_float_rand);


static void uint32_rand(picobench::state& s)
{
     for (auto _ : s) {
         misc::fast_float_rand() * UINT32_MAX;
     }
}
PICOBENCH(uint32_rand);
