TARGET = bin/synth

SRCDIR = src
BUILDDIR = build
LOCALLIBDIR = libs
ARDUINOPATH = arduino-1.8.13
ARDUINOLIBS = SD SPI SerialFlash Wire

MCU = IMXRT1062

# derived paths
COREDIR = $(ARDUINOPATH)/hardware/teensy/avr/cores/teensy4
MCU_LD = $(COREDIR)/imxrt1062.ld
ARDUINOLIBDIR = $(ARDUINOPATH)/hardware/teensy/avr/libraries
TOOLSPATH = $(ARDUINOPATH)/hardware/tools

## get .c/.cpp files and includes for ...
# source dir
INC := -I$(SRCDIR)
C_FILES := $(wildcard $(SRCDIR)/*.c)
CPP_FILES := $(wildcard $(SRCDIR)/*.cpp)
S_FILES := $(wildcard $(SRCDIR)/*.S)

# core library
INC += -I$(COREDIR)
C_FILES += $(wildcard $(COREDIR)/*.c)
CPP_FILES += $(wildcard $(COREDIR)/*.cpp)
CPP_FILES := $(filter-out $(COREDIR)/main.cpp, $(CPP_FILES)) # remove main.cpp from core
S_FILES += $(wildcard $(COREDIR)/*.S)

# local libraries
INC += $(foreach lib,$(filter %/, $(wildcard $(LOCALLIBDIR)/*/)), -I$(lib))
INC += $(foreach lib,$(filter %/, $(wildcard $(LOCALLIBDIR)/*/utility/)), -I$(lib))

C_FILES += $(wildcard $(LOCALLIBDIR)/*/*.c)
C_FILES += $(wildcard $(LOCALLIBDIR)/*/utility/*.c)

CPP_FILES += $(wildcard $(LOCALLIBDIR)/*/*.cpp)
CPP_FILES += $(wildcard $(LOCALLIBDIR)/*/utility/*.cpp)

S_FILES += $(wildcard $(LOCALLIBDIR)/*/*.S)
S_FILES += $(wildcard $(LOCALLIBDIR)/*/utility/*.S)

# arduino libraries
ARDUINOLIBDIRS = $(foreach lib, $(ARDUINOLIBS), $(ARDUINOLIBDIR)/$(lib))
INC += $(foreach lib,$(ARDUINOLIBDIRS), -I$(lib))
INC += $(foreach lib,$(ARDUINOLIBDIRS), -I$(lib)/utility)

C_FILES += $(foreach lib,$(ARDUINOLIBDIRS), $(wildcard $(lib)/*.c))
C_FILES += $(foreach lib,$(ARDUINOLIBDIRS), $(wildcard $(lib)/utility/*.c))

CPP_FILES += $(foreach lib,$(ARDUINOLIBDIRS), $(wildcard $(lib)/*.cpp))
CPP_FILES += $(foreach lib,$(ARDUINOLIBDIRS), $(wildcard $(lib)/utility/*.cpp))

S_FILES += $(foreach lib,$(ARDUINOLIBDIRS), $(wildcard $(lib)/*.S))
S_FILES += $(foreach lib,$(ARDUINOLIBDIRS), $(wildcard $(lib)/utility/*.S))

SOURCES := $(C_FILES:.c=.o) $(CPP_FILES:.cpp=.o) $(S_FILES:.S=.o)
OBJS := $(foreach src,$(SOURCES), $(BUILDDIR)/$(src))

# names for the compiler programs
COMPILERPATH = $(ARDUINOPATH)/hardware/tools/arm/bin
CC = $(COMPILERPATH)/arm-none-eabi-gcc
CXX = $(COMPILERPATH)/arm-none-eabi-g++
OBJCOPY = $(COMPILERPATH)/arm-none-eabi-objcopy
SIZE = $(COMPILERPATH)/arm-none-eabi-size

# configurable options
OPTIONS = -DF_CPU=600000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -DUSING_MAKEFILE
# options needed by many Arduino libraries to configure for Teensy 4.0
OPTIONS += -D__$(MCU)__ -DARDUINO=10810 -DTEENSYDUINO=149 -DARDUINO_TEENSY40
# for Cortex M7 with single & double precision FPU
CPUOPTIONS = -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -mthumb
# CPPFLAGS = compiler options for C and C++
CPPFLAGS = -Wall -g -O2 $(CPUOPTIONS) -MMD $(OPTIONS) -ffunction-sections -fdata-sections
# compiler options for C++ only
CXXFLAGS = -std=gnu++14 -felide-constructors -fno-exceptions -fpermissive -fno-rtti -Wno-error=narrowing
# compiler options for C only
CFLAGS =
# linker options
LDFLAGS = -Os -Wl,--gc-sections,--relax $(SPECS) $(CPUOPTIONS) -T$(MCU_LD)
# additional libraries to link
LIBS = -larm_cortexM7lfsp_math -lm -lstdc++

all: hex

build: $(TARGET).elf

hex: $(TARGET).hex

post_compile: $(TARGET).hex
	@$(abspath $(TOOLSPATH))/teensy_post_compile -file="$(basename $<)" -path=$(CURDIR) -tools="$(abspath $(TOOLSPATH))"

reboot:
	@-$(abspath $(TOOLSPATH))/teensy_reboot

upload: post_compile reboot

$(BUILDDIR)/%.o: %.c
	@echo -e "[CC]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) -o "$@" -c "$<"

$(BUILDDIR)/%.o: %.cpp
	@echo -e "[CXX]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INC) -o "$@" -c "$<"

$(BUILDDIR)/%.o: %.S
	@echo -e "[S]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INC) -o "$@" -c "$<"

$(TARGET).elf: $(OBJS) $(MCU_LD)
	@echo -e "[LD]\t$@"
	@$(CC) $(LDFLAGS) -o "$@" $(OBJS) $(LIBS)

%.hex: %.elf
	@echo -e "[HEX]\t$@"
	@$(SIZE) "$<"
	@$(OBJCOPY) -O ihex -R .eeprom "$<" "$@"

# compiler generated dependency info
-include $(OBJS:.o=.d)

clean:
	@echo Cleaning...
	@rm -rf "$(BUILDDIR)"
	@rm -f "$(TARGET).elf" "$(TARGET).hex"
