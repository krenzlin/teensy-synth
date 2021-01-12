tuning = 440.0
samplerate = 50_000
bits = 32
max_phase = 1 << bits

def mtof(note, tuning):
    return pow(2.0, (note - 69.0)/12.0) * tuning


def ftoincr(f, sr, max):
    return 1.0*f / sr * max


def create_c_array(name, list_):
    template = "const uint32_t {name}[{len}] = {{{values}}};"
    values = ", ".join(str(value) for value in list_)
    return template.format(name=name, len=len(list_), values=values) + "\n"

lut_mtof = [mtof(note, tuning) for note in range(128)]
lut_mtoincr = [round(ftoincr(f, samplerate, max_phase)) for f in lut_mtof]

header_template = """
// generated by generate_luts.py
// sample rate: {sr}
// tuning frequency: {tuning}
// max phase value: 1 << {bits} = {max}
#pragma once
#include <stdint.h>

namespace luts {{

{content}
}}
""".strip()

content = create_c_array("m_to_incr", lut_mtoincr)
print(header_template.format(content=content, sr=samplerate, tuning=tuning, max=max_phase, bits=bits))