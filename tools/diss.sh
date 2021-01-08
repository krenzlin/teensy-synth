#!/bin/bash

objdump=arduino-1.8.13/hardware/tools/arm/bin/arm-none-eabi-objdump
#objs="build/{clock,drums,hal,misc,osc,pattern}.cpp.o"
objs=*.elf
eval $objdump $objs -d | c++filt | grep -vE '^\s+\.'
