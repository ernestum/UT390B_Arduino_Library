UT390B Laser Distance Meter Library for Arduino
===============================================

This is a library to interface with the cheap but good UT390B Laser Distance Meter using an Arduino.
It supports simple blocking measurements and more advanced asynchronous measurements for time critical projects.
It is based mostly on information gathered from [this blog post](http://blog.qartis.com/arduino-laser-distance-meter/) and its two follo ups.

Installation
------------
To install the library just download the .zip file and look [here](http://arduino.cc/en/Guide/Libraries) for further instructions.
You can also just clone this git repository into you libraries folder:
```Bash
cd <yoursketchbook>/libraries/
git clone https://github.com/erniejunior/UT390B-Arduino-Library.git
```
After a restart of the arduino IDE you are done!

Usage
-----
Just have a look at the two examples. They are fairly self explaining.

Possible Improvements
---------------------
* Burst mode
* Error codes (look here http://blog.qartis.com/ut390b-error-numbers/). Especially low battery warnings.
* Switching the laser on and off
