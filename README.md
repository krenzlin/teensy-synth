# teensy-synth
exploratory repo on using the teensy (lc) as a synth and sample player

# install Teensyduino
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