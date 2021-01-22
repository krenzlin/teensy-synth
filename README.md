# Teensy Synth

Started as experiments on the Teensy LC and now is evolving into using the Teensy 4.0 with the Audio Board.


## install Teensyduino
c.f. https://forum.pjrc.com/threads/62671-teensyduino-linux-installer-issue?p=250603&viewfull=1#post250603

```
wget https://downloads.arduino.cc/arduino-1.8.13-linux64.tar.xz
wget https://www.pjrc.com/teensy/td_153/TeensyduinoInstall.linux64
wget https://www.pjrc.com/teensy/49-teensy.rules
sudo cp 49-teensy.rules /etc/udev/rules.d/
tar -xf arduino-1.8.13-linux64.tar.xz
chmod 755 TeensyduinoInstall.linux64
./TeensyduinoInstall.linux64 --dir=arduino-1.8.13
cd arduino-1.8.13
```

## edit paths and libraries

`teensy4.mk` is the Makefile for building and uploading this project to the Teensy 4.0 and is called from the main `Makefile`.
Change paths and flags to your needs, esp. the `ARDUINOPATH` to the Teensyduino installation.

```
TARGET = synth  # name of hex file and where it will be stored
SRCDIR = src    # directory of your source files
BUILDDIR = build  # where to put object files
LOCALLIBDIR = libs  # directory with local libraries, e.g. via git submodules or just copied
ARDUINOPATH = arduino-1.8.13 # path to the teensyduino installation
ARDUINOLIBS = SD SPI SerialFlash Wire # which Arduino libs to compile
```

## build and upload

To build the final hex run `make build` and to upload `make upload`. Or in a single command with just `make`.

## testing, benchmarking and cppcheck

This project has tests and benchmarks to be run on the host.
See `Makefile` for details.

`make test`

`make bench`

