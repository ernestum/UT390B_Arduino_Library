#include <UT390B.h>

/** 
 * This examle shows how to do asynchronous measurements. Because the measurements can take quite long,
 * the simple measure() method can be impractical in some situations. For example if you want to do one 
 * task continously (e.g. sending "Hello World!" via the serial interface like in this example) and take
 * a measurement from time to time. Therefore an alternative method is to first trigger a measurement 
 * and "pick it up" as soon as it is available.
 */
 
// create a laser object
UT390B laser(Serial1);

void setup() {
  // start communication with the computer
  Serial.begin(9600);
}

long lastMeasurement = -10000;

void loop() {
  if(millis() - lastMeasurement > 10000) { // if the last measurement is more than 10 seconds ago
    laser.triggerMeasurement(); // trigger a new measurement
    lastMeasurement = millis(); // remember when we made the measurement
  }
  
  // Note that measurementAvailable() should be called frequently ( a couple of ms delay is ok but not too much)
  // otherwise some measurements seem to get lost
  if(laser.measurementAvailable()) { // if the measurement is ready
    //print it to the serial interface
    Serial.print("Length is "); Serial.print(laser.readMeasurement()); Serial.println("mm");
  }

  // Print "Hello World!" every now and then
  if(millis() % 500 == 0)
    Serial.println("Hello World!");
}
