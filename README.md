UT390B Laser Distance Meter Library for Arduino
===============================================

This is a library to interface with the cheap but good UT390B Laser Distance Meter using an Arduino.
It supports simple blocking measurements and more advanced asynchronous measurements for time critical projects.
It is based mostly on information gathered from [this blog post](http://blog.qartis.com/arduino-laser-distance-meter/) and its two follow-ups.

Installation
------------
To install the library just download the .zip file and look [here](http://arduino.cc/en/Guide/Libraries) for further instructions.
You can also just clone this git repository into you libraries folder:
```Bash
cd <yoursketchbook>/libraries/
git clone https://github.com/ernestum/UT390B_Arduino_Library.git
```
After a restart of the arduino IDE you are done!

Usage
-----
Just have a look at the two examples. They are fairly self explaining.

Connecting to an Arduino
------------------------
Be aware, that the UT390B runs at 2.7V. A 5V Arduino or even a 3.3V would fry it when connected directly. Actually somebody else had [trouble getting it to work with 3.3V at all](https://github.com/ernestum/UT390B_Arduino_Library/issues/2#issuecomment-163421915). This is how I connected mine to a 5V Arduino:
![scan 1](https://cloud.githubusercontent.com/assets/1250234/9354402/5a5db5d6-4670-11e5-9d61-9cdacc2f461e.jpeg)
* The 2.7V can be left free.
* The 2.7V of TX at the UT390B are just enough to trigger a logical 1 at the Arduinos RX. Therefore it can be connected directly.
* The 5V of the TX at the Arduino would fry our UT390B. Therefore we use a simple voltage divider with two equal, high resistors, to step down the TX voltage coming from the arduino to 2.5V which is enough to trigger a logical 1 at the UT390B side. I would recommend a rather high resitance (around 10kΩ) but mainly make sure that R1 and R2 have the same resistance.
* Check [here](http://blog.qartis.com/arduino-laser-distance-meter/) to find out where the RX, TX and GND pins are on the UT390B.
* When you connect something to the main RX, TX pins, you can not use Serial any more for debuggin/sending data to the computer. I therefore recommend an Arduino with more than one hardware serial (like the mega). Unfortunately I remember having trouble with software serial. Therefore this library does not support it.

Possible Improvements
---------------------
* Burst mode
* Error codes (look here http://blog.qartis.com/ut390b-error-numbers/). Especially low battery warnings.
* Switching the laser on and off
