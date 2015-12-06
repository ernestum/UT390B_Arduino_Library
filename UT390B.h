/*
  Test.h - Test library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef UT390B_h
#define UT390B_h


#include "Arduino.h"

// library interface description
template<typename Serial_T>
class UT390B
{
  // user-accessible "public" interface
  public:
    UT390B(Serial_T &serial = Serial) : serial(&serial) {
        serial.begin(115200);
    }

    long measure(int retries = 0, int timeout = 2000) {
        long measurement = -1;
        while(measurement <= 0 && retries >= 0) {
            this->triggerMeasurement();
            unsigned long starttime = millis();
            while(!measurementAvailable() && millis() - starttime < timeout) {} //just wait until there is a measurement
            measurement = readMeasurement();
            retries--;
        }
        return measurement;
    }

    /**
     * Tests if there is a new sesor measurement available in the current stream buffer.
     * If there is a measurement available, the stream is advanced unil just before the
     * message (just before the '*' sign). If there is nor measurement available, the stream
     * is advanced til there is nothing in the buffere any more.
     */
    bool measurementAvailable() {
        while(serial->available()) {
            if(serial->peek() == '*') {
                Serial.println("There is a new measurement available!");
                return true;
            }
            else {
//                serial->read();
                Serial.print("Skipping " + serial->read());
                Serial.println(" to reach the start of a new message indicated by '*'");
            }
        }
        return false;
    }

    /** Here we parse the value 653 from the following string: *0006400000065305#
     * TODO: make him cope with the rapid fire packages that look like *00084500120000065425#
     * TODO: check the checksum
     */
    long readMeasurement(int timeout = 2000) {
        serial->setTimeout(timeout);
        if(!measurementAvailable()) return -1;


        serial->read(); //read the '*'

        //Read the first 4 digits. They contain the length of the message
        int messageLength = readNumber(4);
        Serial.print("The message length seems to be ");
        Serial.println(messageLength);

        if(messageLength < 2) {
            Serial.println("Message length less than 2 is not expected, return -1");
            return -1; //No Idea what is going on then
        }

        byte commandtype = readNumber(2);
        Serial.print("Command Type seems to be ");
        Serial.println(commandtype);

        int distance;
        switch(commandtype) {
        case 40: // single measurement
            Serial.println("That indicates a single measurement");
            distance = readNumber(8);
            break;
        case 45: // burst measurement
            Serial.println("That indicates a burst measurement");
            {
                int idx = readNumber(4); //there is a running index in those messages. We parse it but we do not use it right now
                Serial.print("The running index of the message seems to be");
                Serial.println(idx);
            }
            break;
        default: // we have no idea what is going on
            return -1;
        }
        Serial.print("The distance seems to be ");
        Serial.println(distance);
        if(distance > 0) {
            latestMeasurement = distance;
            latestMeasurementTime = millis();
            return distance;
        } else { //TODO: why does this even happen? This should be investigated!
            Serial.println("That is an invalid distance!");
            return -1;
        }
    }

    long getLatestMeasurement() {
        return latestMeasurement;
    }

    unsigned long getLatestMeasurementTime() {
        return latestMeasurementTime;
    }

    void triggerMeasurement() {
        latestTriggerTime = millis();
        serial->print("*004040#");
    }

    bool continousMeasurement() {
        if(measurementAvailable()) {
            readMeasurement(50);
            triggerMeasurement();
            return true;
        } else if(millis() - latestTriggerTime > 1300) {
            triggerMeasurement();
        }
        return false;
    }

  // library-accessible "private" interface
  private:
    Serial_T* serial;
    long latestMeasurement;
    unsigned long latestMeasurementTime;
    unsigned long latestTriggerTime;

    long readNumber(int numDigits) {
        char buffer[numDigits+1];
        buffer[numDigits] = '\0';
        serial->readBytes(buffer, numDigits);
        Serial.print(">"); Serial.println(buffer);
        return atol(buffer);
    }
};

#endif

