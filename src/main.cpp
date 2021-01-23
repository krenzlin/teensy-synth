#include <Audio.h>
#include "AudioObjects.h"
#include "misc.h"

AudioOutputI2S        i2s;
AudioMixer4 mixer;
Saw saw;
Saw saw2;
AudioConnection       patchCord1(saw, 0, i2s, 0);
AudioConnection       patchCord2(saw2, 0, i2s, 1);
AudioConnection mixer_to_i2s_l(mixer, 0, i2s, 0);
AudioConnection mixer_to_i2s_r(mixer, 0, i2s, 1);
AudioControlSGTL5000  sgtl5000_1;


int main() {
    AudioMemory(10);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.3);

    delay(1000);

    while(1) {
        auto note = misc::random_note(60, 80);
        saw.note_on(note);
        saw2.note_on(misc::random_note(60, 80));
        delay(1000);
    }
}
