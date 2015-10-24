//
//  BrickBot.h
//  BrickBot_Arduino
//
//  Created by Shannon Young on 10/7/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef BrickBot_hpp
#define BrickBot_hpp

#include "BrickBotArduino.h"
#include "BrickBotShared.h"
#include "BrickBotBrain.h"
#include "BrickBotServo.h"
#include "BrickBotVoiceBox.h"
#include "BrickBotLights.h"

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
    bool enabled = false;
} BrickBotState;

class BrickBot {
public:
    
    /**
     * Must either attach using pins and default motors and range finders or attach your own.
     */
    void attach(BrickBotBrainProtocol *brain, int leftMotorPin, int rightMotorPin);
    void attach(BrickBotBrainProtocol *brain, BrickBotServoProtocol *servoLeft, BrickBotServoProtocol *servoRight);
    
    /**
     * Get state information about connection
     */
    BrickBotState updateState();
    
    /**
     * Put the robot to sleep (which will also stop the motors and reset state)
     */
    void sleep();
    
    /**
     * Wakeup the robot (which will reset state to "setup" conditions)
     */
    void wakeup();
    
    /**
     * Stop the motors
     */
    void stopMotors(bool hasObjectInFront = false);
    
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
     * Is the robot upright
     */
    bool isRobotUpright();
    
    /**
     * Default orientation values. Allow Arduino sketch to modify these.
     */
    int zAxisOrientationSide = 60;
    int zAxisOrientationUp = 220;
    
    /**
     * Attach a voicebox to the robot (optional)
     */
    void attachVoiceBox(BrickBotVoiceBox *voiceBox);
    
    /**
     * Attach lights to the robot (optional)
     */
    void attachLights(BrickBotLights *lights);

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
    int motorCalibration[BBMotorCalibrationStateCount][2];
    void attachServoPins(int leftPin, int rightPin);
    void attachServos(BrickBotServoProtocol *servoLeft, BrickBotServoProtocol *servoRight);
    void updateMotorCalibration(int idx, uint8_t rec);
    void updateMotorState();
    void setMotorValue(int motor, int spd);
     
    // Voice
    bool hasVoiceBox = false;
    BrickBotVoiceBox *voiceBox;
    
    // Lights
    bool hasLights = false;
    BrickBotLights *lights;
};

#endif /* BrickBot_hpp */
