#include "filter.h"


int32_t filter::LP::process(int32_t input) {
    sample = input / 2 + sample / 2;
    return sample;
}
