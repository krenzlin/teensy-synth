#include <Audio.h>
#include "AudioObjects.h"
#include "misc.h"
#include "MIDI.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial4, MIDI); // Serial5 is used by Audio board

AudioOutputI2S        i2s;
AudioMixer4 mixer;
PolyBLEPSaw saw;
AudioConnection       patchCord1(saw, 0, i2s, 0);
AudioConnection       patchCord2(saw, 0, i2s, 1);
AudioConnection mixer_to_i2s_l(mixer, 0, i2s, 0);
AudioConnection mixer_to_i2s_r(mixer, 0, i2s, 1);
AudioControlSGTL5000  sgtl5000_1;


void note_on(midi::Channel channel, byte note, byte velocity) {
    saw.note_on(note, velocity);
}

void note_off(midi::Channel channel, byte note, byte velocity) {
    saw.note_off(note, velocity);
}

int main() {
    AudioMemory(10);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.3);

    MIDI.begin(MIDI_CHANNEL_OMNI);


    delay(500);

    //saw2.note_on(69);

    MIDI.setHandleNoteOn(note_on);
    MIDI.setHandleNoteOff(note_off);


    while(1) {
        MIDI.read();
		//yield();
    }
}
