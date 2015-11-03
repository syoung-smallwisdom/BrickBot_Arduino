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
#include "BrickBotDriver.h"
#include "BrickBotVoiceBox.h"
#include "BrickBotLights.h"
#include "BrickBotRangeFinder.h"

typedef struct {
    bool connected = false;
    bool autopilotOn = true;
    bool remoteOn = false;
    bool isRobotUpright = true;
    bool enabled = false;
} BrickBotState;

class BrickBot {
public:
    
    BrickBot(BrickBotBrain *brain, BrickBotDriver *driver, BrickBotRangeFinder *rangeFinder);
    
    /**
     * Get state information about connection
     */
    BrickBotState updateState();
    
    /**
     * Put the robot to sleep (which will also stop the motors and reset state)
     */
    void sleep(uint32_t duration_ms = 500);
    
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
     * Is the robot upright
     */
    bool isRobotUpright();
    
    /**
     * Is the robot stuck
     */
    bool canMoveForward();
    bool canMoveBackward();
    
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
    BrickBotBrain *brain;
    BrickBotState state;
    void checkRemote();

    // Motor control
    BrickBotRangeFinder *rangeFinder;
    BrickBotDriver *driver;
    void updateMotorState();
    int _dir = 0;
    int _steer = 0;
    
    // Voice
    bool hasVoiceBox = false;
    BrickBotVoiceBox *voiceBox;
    
    // Lights
    bool hasLights = false;
    BrickBotLights *lights;
};

#endif /* BrickBot_hpp */
