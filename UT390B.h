/*
  Test.h - Test library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef UT390B_h
#define UT390B_h


#include "Arduino.h"

// library interface description
class UT390B
{
  // user-accessible "public" interface
  public:
    UT390B(HardwareSerial &serial = Serial) : serial(&serial) {
        serial.begin(115200);
    }

    long measure() {
        this->triggerMeasurement();
        while(!measurementAvailable()) {} //just wait until there is a measurement
        return readMeasurement();
    }

    /**
     * Tests if there is a new sesor measurement available in the current stream buffer.
     * If there is a measurement available, the stream is advanced unil just before the
     * message (just before the '*' sign). If there is nor measurement available, the stream
     * is advanced til there is nothing in the buffere any more.
     */
    bool measurementAvailable() {
        while(serial->available()) {
            if(serial->peek() == '*')
                return true;
            else
                serial->read();
//                Serial.println("skipping " + serial->read());
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

        if(messageLength < 2) return -1; //No Idea what is going on then

        byte commandtype = readNumber(2);

        switch(commandtype) {
        case 40: // single measurement
            return readNumber(8);
            break;
        case 45: // burst measurement
            readNumber(4); //there is a running index in those messages. We parse it but we do not use it right now
            return readNumber(8);
            break;
        default: // we have no idea what is going on
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
        serial->print("*004040#");
    }

  // library-accessible "private" interface
  private:
    Stream* serial;
    long latestMeasurement;
    unsigned long latestMeasurementTime;

    long readNumber(int numDigits) {
        char buffer[numDigits+1];
        buffer[numDigits] = '\0';
        serial->readBytes(buffer, numDigits);
        return atol(buffer);
    }
};

#endif

