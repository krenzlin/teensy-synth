# Teensy Synth

A simple hardware synthesizer for the Teensy 4 with Audio Shield.

The vision is to abstract most of the boilerplate code and
focus on minimalistic and easy to understand DSP implementations.

> The current state of this project is *experimental*.
> So don't expect a fully working synth, but rather ideas where to start.

## Getting Started

### Prerequisites

You need to have [Teensyduino](https://www.pjrc.com/teensy/td_download.html) installed.

```
wget https://downloads.arduino.cc/arduino-1.8.13-linux64.tar.xz
wget https://www.pjrc.com/teensy/td_153/TeensyduinoInstall.linux64
wget https://www.pjrc.com/teensy/49-teensy.rules
sudo cp 49-teensy.rules /etc/udev/rules.d/
tar -xf arduino-1.8.13-linux64.tar.xz
chmod 755 TeensyduinoInstall.linux64
./TeensyduinoInstall.linux64 --dir=arduino-1.8.13
```


### Installing

Clone the repository and its submodules

```
git clone --recurse-submodules https://github.com/krenzlin/teensy-synth
```

Point `ARDUINOPATH` in `teensy4.mk` to your Teensyduino installation.

Run `make build` to compile and `make upload` to flash your connected Teensy.


## Repository structure

All source code is in `src` (implementations and headers), third party libraries in `libs` and tests and stuff in `tests`.

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
## Running the tests, benchmarks and code checks


### Tests

Run `make test` to execute the test suite.

### Benchmark

This repository has a set of benchmarks to compare DSP implementations.

`make bench`

### Code checks

`make check` runs `cppcheck` on all source files.


## Contributing

Please feel free to open up an issue or pull request.

## Versioning

As this project is still in exploration phase it has no versioning besides the git commits.

In the future [SemVer](http://semver.org/) might be used.

## Authors

* [Konrad](https://github.com/krenzlin)


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* [doctest](https://github.com/onqtam/doctest)
* [picobench](https://github.com/iboB/picobench)
* [Teensy Audio Library](https://www.pjrc.com/teensy/td_libs_Audio.html)
* [ADSR implementation](https://github.com/FortySevenEffects/arduino_midi_library) by earlevel.com
* [Arduino MIDI Library](https://github.com/FortySevenEffects/arduino_midi_library) by FortySevenEffects
