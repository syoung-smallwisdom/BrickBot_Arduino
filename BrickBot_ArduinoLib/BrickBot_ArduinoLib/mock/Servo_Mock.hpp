//
//  Servo_Mock.h
//  BrickBot_ArduinoTest
//
//  Created by Shannon Young on 10/7/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

// Mock Servo included for unit testing using Objective-C

#ifndef Servo_h
#define Servo_h

#include <iostream>

class Servo
{
public:
    uint8_t attach(int pin);           // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
    void write(int value);             // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds
    
protected:
    int _pin;
    int _value;
};

#endif /* Servo_ObjCMock_hpp */
