//
//  BrickBot.h
//  BrickBot_Arduino
//
//  Created by Shannon Young on 10/7/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef BrickBot_hpp
#define BrickBot_hpp

#ifndef BrickBot_Simulator
#include <Servo.h>
#include <Arduino.h>
#else
#include "Arduino_Mock.hpp"
#endif

#include "BrickBotShared.h"
#include "BrickBotBrain.h"
#include "BrickBotServo.h"
#include "BrickBotRangeFinder.h"

#define BB_MOTOR_LEFT 0
#define BB_MOTOR_RIGHT 1

#define BB_MOTOR_STOP 90
#define BB_MOTOR_CENTER 90
#define BB_MOTOR_SLOW 20

typedef struct {
    bool connected = false;
    bool autopilotOn = true;
    bool remoteOn = false;
    bool isRobotUpright = true;
} BrickBotState;

class BrickBot {
public:
    
    /**
     * Must either attach using pins and default motors and range finders or attach your own.
     */
    void attach(BrickBotBrainProtocol *brain, int leftMotorPin, int rightMotorPin, int triggerPin, int echoPin);
    void attach(BrickBotBrainProtocol *brain, BrickBotServoProtocol *servoLeft, BrickBotServoProtocol *servoRight, BrickBotRangeFinderProtocol *rangeFinder);
    
    /**
     * Get state information about connection
     */
    BrickBotState updateState();
    
    /**
     * Put the robot to sleep (which will also stop the motors and reset state)
     */
    void sleep();
    
    /**
     * Stop the motors
     */
    void stopMotors();
    
    /**
     * Send a command to run the motors with the current dir and steer settings.
     */
    void runMotors(int dir, int steer);
    
    /**
     * Get the current motor speed
     */
    uint8_t getMotorSpeed(int motor);
    
    /**
     * Reset the motor calibration to the default.
     */
    void resetMotorCalibration();
    
    /**
     * Change autopilot state
     */
    void setAutopilotOn(bool on);
    
    /**
     * Is there an object within range
     */
    bool hasObjectInFront();
    
    /**
     * Is the robot upright
     */
    bool isRobotUpright();
    
    /**
     * Default orientation values. Allow Arduino sketch to modify these.
     */
    int zAxisOrientationSide = 60;
    int zAxisOrientationUp = 220;

protected:
    
    // Remote
    BrickBotBrainProtocol *brain;
    BrickBotState state;
    void attachComm(BrickBotBrainProtocol *brain);
    void checkRemote();

    // Motor control
    BrickBotServoProtocol *servoLeft;
    BrickBotServoProtocol *servoRight;
    int _dir = 0;
    int _steer = 0;
    uint8_t motorSpeed[2] = {BB_MOTOR_STOP, BB_MOTOR_STOP};
    int motorCalibration[BBMotorCalibrationStateCount][2];
    int defaultMotorCalibration[BBMotorCalibrationStateCount][2] = {
        {BB_MOTOR_CENTER/2, -1*BB_MOTOR_CENTER},    // left
        {BB_MOTOR_CENTER, -1*BB_MOTOR_CENTER},      // straight
        {BB_MOTOR_CENTER, -1*BB_MOTOR_CENTER/2}};   // right
    void attachServoPins(int leftPin, int rightPin);
    void attachServos(BrickBotServoProtocol *servoLeft, BrickBotServoProtocol *servoRight);
    void updateMotorCalibration(int idx, uint8_t rec);
    void updateMotorState();
    void setMotorValue(int motor, int spd);
    
    // Range finder
    BrickBotRangeFinderProtocol *rangeFinder;
    void attachRangeFinderPins(int triggerPin, int echoPin);
    void attachRangeFinder(BrickBotRangeFinderProtocol *rangeFinder);
};

#endif /* BrickBot_hpp */
