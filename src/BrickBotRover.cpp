//
//  BrickBotAutopilot.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 11/2/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "BrickBotRover.h"

const int delayMilliseconds = 50;


void BrickBotRover::loop() {
    
    // Update the brickbot state (and run robot if using remote)
    // This should be checked at the beginning of each loop to test for the
    // robot being run remotely or turtled (turned over).
    BrickBotState state = updateState();
    
    // Check for state changes
    bool shouldRun = (state.autopilotOn || state.connected) && state.enabled;
    
    // If the autopilot is ON or the robot is connected to a remote
    // then update the autopilot routine and then wait before looping again.
    if (shouldRun) {
        
        if (state.autopilotOn && !state.remoteOn) {
            // If the autopilot is on then check the range
            runAutopilot();
        }
        else {
            // Otherwise, reset the autopilot state
            resetAutopilot();
        }
        
        // use a delay rather than a Bean.sleep so that the motors stay active
        delay(delayMilliseconds);
    }
    else {
        sleep();
    }
}

void BrickBotRover::resetAutopilot() {
    // reset if using remote
    reverseCount = 0;
    forwardCount = 0;
    autoSteer = BB_STEER_LEFT;
}

void BrickBotRover::runAutopilot() {
    
    if (reverseCount > 0) {
        // count down the reverse count if backing up
        reverseCount--;
        if (reverseCount == 10) {
            // Once the robot has backed up, then turn before starting forward again
            runMotors(0, autoSteer);
            flipAutoSteer();
        }
    }
    else if (!canMoveForward()) {
        
        // stop motors
        stopMotors(true);
        
        // Object in front detected so start the reverse
        // but only if not stuck
        if (canMoveBackward()) {
            reverseCount = 20;
            runMotors(BB_DIR_BACKWARD, autoSteer);
            flipAutoSteer();
        }
    }
    else {
        // move in serpentine - this gives the rangefinder a broader scope
        // which means it does a better job of "seeing" obsticles like chair legs
        runMotors(BB_DIR_FORWARD, autoSteer);
        forwardCount++;
        if (forwardCount > 20) {
            flipAutoSteer();
        }
    }
}

void BrickBotRover::flipAutoSteer() {
    forwardCount = 0;
    autoSteer = (autoSteer == BB_STEER_LEFT) ? BB_STEER_RIGHT : BB_STEER_LEFT;
}
