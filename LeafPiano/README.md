# Leaf Piano
We made a piano using a touch sensor, as well as leaves for piano keys.

## Things used in this project
### Hardware components
- Seeeduino V4.2
- Seeed Base Shield V2
- Seeed Grove - 12 Key Capacitive I2C Touch Sensor V2 (MPR121)
- Seeed Grove - MP3 v2.0
### Software apps and online services
- Arduino IDE

## Story
Touch Sensor determines touch/release status based on electrode capacitance data changes, so we can use it to make a piano with any conductive object we like as piano key.
### Hardware Connection
**Step 1: **Copy the mp3 files to a piece of SD card, name folders same as corresponding instrument's indexes and name mp3 files same as corresponding Touch Sensor channel's indexes.

**Step 2: **Plug SD card to MP3 Grove, connect MP3 Grove and Touch Sensor to port D2 and I2C port in Base Shield, connect conductive objects to Touch Sensor's channels via crocodile clips.

**Step 3: **Plug the Base Shield to Seeeduino, then connect Seeeduino to PC via a USB cable.
### Software Programming
Touch Sensor Grove's library can be found in this url:

[http://wiki.seeedstudio.com/Grove-12_Key_Capacitive_I2C_Touch_Sensor_V2-MPR121/](http://wiki.seeedstudio.com/Grove-12_Key_Capacitive_I2C_Touch_Sensor_V2-MPR121/)

MP3 Grove's library also can be found in [Seeed Wiki](http://wiki.seeedstudio.com/Grove-MP3_v2.0/), or you can simply include MP3.h in project folder.

Seeeduino's digital pin 2 and 3 as a software serial, it controll MP3 Grove by using the protol in KT403A datashell. After MP3 Grove and Touch Sensor are initialized, set Touch Sensor's sensitivity and MP3 Grove's volume.

The loop() method keep on checking if Touch Sensor is touched or not, if it is touched, play the corresponding mp3 file in current instrument folder. Current insreument can be changed by input instrument's index via hardware serial.

## Operation

## Code
