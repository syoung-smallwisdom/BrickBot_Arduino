//
//  BrickBotServo.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/8/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef BrickBotServo_hpp
#define BrickBotServo_hpp

#ifndef BrickBot_Simulator
#include <Servo.h>
#else
#include "Servo_Mock.hpp"
#endif

class BrickBotServoProtocol
{
public:
    virtual void write(int value) = 0;
    virtual int read() { return 0; }
};

class BrickBotServo : public BrickBotServoProtocol
{
public:
    BrickBotServo(int pin);
    void write(int value);
    int read();
    
protected:
    Servo motor;
};

#endif /* BrickBotServo_hpp */
