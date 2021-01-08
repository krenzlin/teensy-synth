#include "catch.hpp"
#include "misc.h"


TEST_CASE("midi to freq", "[Misc]") {
    REQUIRE(misc::m_to_f(69) == 440.0);
}

