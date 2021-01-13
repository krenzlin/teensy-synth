#include "catch.hpp"
#include <stdint.h>
#include "dac.h"
#include "mocks/core_pins.h"

bool called_analogWriteResolution {false};
uint32_t analogWriteResolution(uint32_t bits) {
    called_analogWriteResolution = true;
    return bits;
}

int mock_analogWriteDAC0_val {0};
void analogWriteDAC0(int val) {
    mock_analogWriteDAC0_val = val;
}

TEST_CASE("writing signed 32 bit to DAC", "[dac]") {
    hal::DAC dac;

    REQUIRE(called_analogWriteResolution);
    REQUIRE(mock_analogWriteDAC0_val == 0);

    dac.write(INT32_MAX);
    REQUIRE(mock_analogWriteDAC0_val == UINT16_MAX >> 4);

    dac.write(INT32_MIN);
    REQUIRE(mock_analogWriteDAC0_val == 0);
}
