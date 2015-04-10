/**
 * This example shows how to do a simple measurement on the laser distance meter.
 */

#include <UT390B.h>

//Create a new laser distance meter object. Give him the serial to use as an argument.
//Here we use the Serial1 of e.g. an Arduino Mega because we still want to use the default
//serial to communicate with the computer.
UT390B laser(Serial1);

void setup() {
  Serial.begin(9600);
}

void loop() {
  //This call to measure() will block until the measurement is done.
  //Be careful, this can quite long!
  int distance = laser.measure();
  
  //Report the distance back to the computer
  Serial.print("The distance is ");
  Serial.print(distance);
  Serial.println(" mm");
}


