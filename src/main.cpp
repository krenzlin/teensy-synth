// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
//
// Part 1-2: Test Hardware
//
// Simple beeping is pre-loaded on the Teensy, so
// it will create sound and print info to the serial
// monitor when plugged into a PC.
//
// This program is supposed to be pre-loaded before
// the workshop, so Teensy+Audio will beep when
// plugged in.

#include <Audio.h>

AudioSynthWaveform    waveform1;
AudioOutputI2S        i2s1;
AudioConnection       patchCord1(waveform1, 0, i2s1, 0);
AudioConnection       patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000  sgtl5000_1;


int main() {
    AudioMemory(10);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.3);
    waveform1.begin(WAVEFORM_SINE);

    delay(1000);

    while(1) {
        waveform1.frequency(440);
        waveform1.amplitude(0.9);
        delay(250);
        waveform1.amplitude(0);
        delay(1750);
    }
}
