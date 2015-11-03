//
//  BrickBotServoDriver.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 11/2/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "BrickBotServoDriver.h"


BrickBotServoDriver::BrickBotServoDriver(int leftMotorPin, int rightMotorPin) {
    leftMotor = new Servo();
    leftMotor->attach(leftMotorPin);
    leftMotor->write(BB_MOTOR_STOP);
    
    rightMotor = new Servo();
    rightMotor->attach(rightMotorPin);
    rightMotor->write(BB_MOTOR_STOP);
    
    resetMotorCalibration();
}

uint8_t BrickBotServoDriver::getMotorSpeed(int motor) {
    Servo *servo = (motor == BB_MOTOR_LEFT) ? leftMotor : rightMotor;
    return servo->read();
}

void BrickBotServoDriver::setMotorValue(int motor, int spd) {
    
    Servo *servo = (motor == BB_MOTOR_LEFT) ? leftMotor : rightMotor;
    
    // If this is a switch from forward/backward then send the
    // stop signal and set a delay
    if ((spd > BB_MOTOR_STOP && currentSpeed[motor] < BB_MOTOR_STOP) ||
        (spd < BB_MOTOR_STOP && currentSpeed[motor] > BB_MOTOR_STOP)) {
        servo->write(BB_MOTOR_STOP);
        delay(50);
    }
    
    // write to the appropriate motor
    servo->write(spd);
    currentSpeed[motor] = spd;
}