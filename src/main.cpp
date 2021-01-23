#include <Audio.h>
#include "AudioObjects.h"
#include "misc.h"

AudioOutputI2S        i2s1;
Saw saw;
AudioConnection       patchCord1(saw, 0, i2s1, 0);
AudioConnection       patchCord2(saw, 0, i2s1, 1);
AudioControlSGTL5000  sgtl5000_1;


int main() {
    AudioMemory(10);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.3);

    delay(1000);

    while(1) {
        auto note = misc::random_note(60, 80);
        saw.note_on(note);
        delay(1000);
    }
}
