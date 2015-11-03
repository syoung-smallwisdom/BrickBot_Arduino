//
//  BrickBot.cpp
//  BrickBot_ArduinoTest
//
//  Created by Shannon Young on 10/7/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "BrickBot.h"

BrickBot::BrickBot(BrickBotBrain *brain, BrickBotDriver *driver, BrickBotRangeFinder *rangeFinder) {
    this->brain = brain;
    this->driver = driver;
    this->rangeFinder = rangeFinder;
}

void BrickBot::attachVoiceBox(BrickBotVoiceBox *voiceBox) {
    this->voiceBox = voiceBox;
    hasVoiceBox = true;
}

void BrickBot::attachLights(BrickBotLights *lights) {
    this->lights = lights;
    hasLights = true;
}

// ---------------------------------------------------------------------------------------------
// Remote Control
// ---------------------------------------------------------------------------------------------

// This flag will only be false when first connected
static bool connectedOn = false;

void BrickBot::sleep(uint32_t duration_ms) {

    // stop the motors
    if (_dir != 0 || _steer != 0) {
        runMotors(0, 0);
    }
    
    // turn off the lights
    if (hasLights) {
        this->lights->setEnabled(false);
    }
    
    if (duration_ms > 0) {
        this->brain->sleep(duration_ms);
    }
}

void BrickBot::wakeup() {
    
    // reset state
    connectedOn = false;
    state.autopilotOn = true;
    state.remoteOn = false;
    state.connected = false;
    
    // stop the motors
    stopMotors();
    
    if (hasVoiceBox) {
        this->voiceBox->sayHello();
    }
    
    if (hasLights) {
        this->lights->setEnabled(true);
    }
}

BrickBotState BrickBot::updateState() {
    
    bool previouslyEnabled = state.enabled;
    state.enabled = brain->enabled();
    
    // Check if this is a change in the state from enabled (on) and disabled (off)
    if (!state.enabled) {
        // EXIT EARLY if the robot is disabled.
        return state;
    }
    else if (state.enabled && !previouslyEnabled) {
        wakeup();
    }

    // get whether or not the robot is upright
    bool isRobotUpright = this->isRobotUpright();
    bool robotChangedOrientation = (state.isRobotUpright != isRobotUpright);
    state.isRobotUpright = isRobotUpright;
    
    // Handle the connection state
    state.connected = brain->getConnectionState();
    if (state.connected) {
        if (!connectedOn && state.enabled) {
            // If this is the first connect, turn off the autopilot by default
            // The connected devise can turn it back on manually.
            state.autopilotOn = false;
        }
        checkRemote();
    }
    else {
        // If not connected, then the remote is OFF
        state.remoteOn = false;
    }
    
    // If the remote is not on AND the autopilot is not on, make sure that the motors are stopped
    if (!state.remoteOn && !state.autopilotOn) {
        stopMotors();
    }
    
    // If the robot has changed orientation then update the motor state
    if (robotChangedOrientation) {
        updateMotorState();
    }
    
    // no matter what, step the lights (as long as the robot is enabled)
    if (hasLights) {
        this->lights->step();
    }
    
    return state;
}

void BrickBot::checkRemote() {
    
    // Set the length to number of bytes recieved
    size_t rec_length = 64;
    char rec_buffer[rec_length];
    rec_length = brain->readSerialBytes(rec_buffer, rec_length);
    if (rec_length == 0) {
        return; // EXIT EARLY if no bytes
    }

    int ii=0;
    while (ii < rec_length) {
        uint8_t controlFlag = rec_buffer[ii]; ii++;
        if (controlFlag == BBControlFlagRemote) {
            BBControlStruct control;
            state.remoteOn = (rec_buffer[ii] != 0);
            if (state.remoteOn) {
                // If the remote is on then run the motors
                memcpy(&control, &rec_buffer[ii], sizeof(control));
                runMotors((int)control.dir - 1, (int)control.steer - 1);
            }
            ii++;
        }
        else if (controlFlag == BBControlFlagAutopilot) {
            // Update the autopilot
            state.autopilotOn = (rec_buffer[ii] != 0); ii++;
        }
        else if (controlFlag == BBControlFlagResetCalibration) {
            driver->resetMotorCalibration();
        }
        else if (controlFlag == BBControlFlagSaveCalibration) {
            // save the motor calibration to the scratch banks
            driver->saveMotorCalibration();
            brain->setCalibrationData(driver->getDefaultCalibrationData());
        }
        else if (controlFlag == BBControlFlagMotorCalibration) {
            // Set the motor calibration for each motor state
            for (; ii < rec_length && (ii - 1) < BBMotorCalibrationStateCount; ii++) {
                driver->updateMotorCalibration(ii - 1, rec_buffer[ii]);
            }
            updateMotorState();
        }
        else if (controlFlag == BBControlFlagSetName && ii < rec_length) {
            String name = "";
            for (; ii < rec_length && (rec_buffer[ii] != 0x00); ii++) {
                name += rec_buffer[ii];
            }
            brain->setName(name);
        }
    }
    
    // No matter what, copy back the message to indicate that it was received
    uint8_t buffer[rec_length];
    memcpy(buffer, rec_buffer, rec_length);
    brain->writeSerialBytes(buffer, rec_length);
}


// ---------------------------------------------------------------------------------------------
// Motor Control
// ---------------------------------------------------------------------------------------------

void BrickBot::stopMotors(bool hasObjectInFront) {
    runMotors(0, 0);
    if (hasObjectInFront && hasVoiceBox) {
        this->voiceBox->sayUhOh();
    }
}

void BrickBot::runMotors(int dir, int steer) {
    _dir = (dir < -1) ? -1 : (dir > 1) ? 1 : dir;
    _steer = (steer < -1) ? -1 : (steer > 1) ? 1 : steer;
    updateMotorState();
}

void BrickBot::updateMotorState() {
    if (!state.isRobotUpright || !state.enabled) {
        driver->runMotors(0, 0);
    }
    else {
        driver->runMotors(_dir, _steer);
    }
}


// ---------------------------------------------------------------------------------------------
// Sensors
// ---------------------------------------------------------------------------------------------

bool BrickBot::canMoveForward() {
    return !this->rangeFinder->hasObjectInFront();
}

bool BrickBot::canMoveBackward() {
    return true;
}

bool BrickBot::isRobotUpright() {

    // Get the current orientation of the robot
    int16_t accelZ = brain->getAccelerationZ();
    
    return  ((zAxisOrientationSide < zAxisOrientationUp) && (accelZ > zAxisOrientationSide)) ||
            ((zAxisOrientationSide > zAxisOrientationUp) && (accelZ < zAxisOrientationSide));
}


