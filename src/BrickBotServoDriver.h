//
//  BrickBotServoDriver.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 11/2/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef BrickBotServoDriver_hpp
#define BrickBotServoDriver_hpp

#ifndef BrickBot_Simulator
#include <Servo.h>
#else
#include "Servo_Mock.hpp"
#endif

#include "BrickBotDriver.h"


class BrickBotServoDriver: public BrickBotDriver
{
public:
    BrickBotServoDriver(int leftMotorPin, int rightMotorPin);

    uint8_t getMotorSpeed(int motor);
    void setMotorValue(int motor, int spd);
    
protected:
    int currentSpeed[2] = {BB_MOTOR_STOP, BB_MOTOR_STOP};
    Servo *leftMotor;
    Servo *rightMotor;
};

#endif /* BrickBotServoDriver_hpp */
