//
//  BrickBot.cpp
//  BrickBot_ArduinoTest
//
//  Created by Shannon Young on 10/7/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "BrickBot.h"

void BrickBot::attach(BrickBotBrainProtocol *brain, int leftMotorPin, int rightMotorPin) {
    attachComm(brain);
    attachServoPins(leftMotorPin, rightMotorPin);
}

void BrickBot::attach(BrickBotBrainProtocol *brain,
                      BrickBotServoProtocol *servoLeft,
                      BrickBotServoProtocol *servoRight) {
    attachComm(brain);
    attachServos(servoLeft, servoRight);
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

void BrickBot::attachComm(BrickBotBrainProtocol *brain) {
    
    // assign pointers
    this->brain = brain;
    
    // write the sketch id to the scratch bank for this library
    // This is used by the remote to confirm the sketch is valid and to get the version
    uint8_t data[] = "BrickBot_1.0.0";
    uint8_t length = sizeof(data);
    this->brain->setScratchData(BBReservedScratchBankSketchId, data, length);
}

void BrickBot::sleep() {

    // stop the motors
    stopMotors();
    
    // turn off the lights
    if (hasLights) {
        this->lights->setEnabled(false);
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
        if (previouslyEnabled) {
            sleep();
        }
        
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
            // Read the motor calibration from the scratch banks
            resetMotorCalibration();
        }
        else if (controlFlag == BBControlFlagMotorCalibration) {
            // Set the motor calibration for each motor state
            for (; ii < rec_length && ii < BBMotorCalibrationStateCount; ii++) {
                updateMotorCalibration(ii - 1, rec_buffer[ii]);
                updateMotorState();
            }
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

void BrickBot::attachServoPins(int leftPin, int rightPin) {
    attachServos(new BrickBotServo(leftPin), new BrickBotServo(rightPin));
}

void BrickBot::attachServos(BrickBotServoProtocol *servoLeft, BrickBotServoProtocol *servoRight) {
    this->servoLeft = servoLeft;
    this->servoRight = servoRight;

    // Stop the motors
    this->servoLeft->write(BB_MOTOR_STOP);
    this->servoRight->write(BB_MOTOR_STOP);
    
    // reset Calibration
    resetMotorCalibration();
}

uint8_t BrickBot::getMotorSpeed(int motor) {
    BrickBotServoProtocol *servo = (motor == BB_MOTOR_LEFT) ? servoLeft : servoRight;
    return servo->read();
}

void BrickBot::setMotorValue(int motor, int spd) {
    
    BrickBotServoProtocol *servo = (motor == BB_MOTOR_LEFT) ? servoLeft : servoRight;
    int currentSpd = servo->read();
    
    // If this is a switch from forward/backward then send the
    // stop signal and set a delay
    if ((spd > BB_MOTOR_STOP && currentSpd < BB_MOTOR_STOP) ||
        (spd < BB_MOTOR_STOP && currentSpd > BB_MOTOR_STOP)) {
        servo->write(BB_MOTOR_STOP);
        delay(50);
    }
    
    // write to the appropriate motor
    servo->write(spd);
}

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
        setMotorValue(BB_MOTOR_RIGHT, BB_MOTOR_STOP);
        setMotorValue(BB_MOTOR_LEFT, BB_MOTOR_STOP);
    }
    else if (_dir == 0) {
        if (_steer == 0) {
            setMotorValue(BB_MOTOR_RIGHT, BB_MOTOR_STOP);
            setMotorValue(BB_MOTOR_LEFT, BB_MOTOR_STOP);
        }
        else {
            setMotorValue(BB_MOTOR_RIGHT, _steer * BB_MOTOR_SLOW + 90);
            setMotorValue(BB_MOTOR_LEFT, _steer * BB_MOTOR_SLOW + 90);
        }
    }
    else {
        for (int mm=BB_MOTOR_LEFT; mm <= BB_MOTOR_RIGHT; mm++) {
            int spd =_dir * motorCalibration[_steer + 1][mm] + 90;
            setMotorValue(mm, spd);
        }
    }
}

void BrickBot::resetMotorCalibration() {
    ScratchData data = brain->readScratchData(BBReservedScratchBankMotorCalibration);
    if (data.length >= BBMotorCalibrationStateCount) {
        for (int ii=0; ii < BBMotorCalibrationStateCount; ii++) {
            updateMotorCalibration(ii, (uint8_t)data.data[ii]);
        }
    }
    else {
        for (int ii=0; ii < BBMotorCalibrationStateCount; ii++) {
            updateMotorCalibration(ii, (ii + 1) * BB_MOTOR_CENTER / 2);
        }
    }
}

void BrickBot::updateMotorCalibration(int idx, uint8_t rec) {
    // If the normalized value is negative, then change LEFT, else change RIGHT
    int offset = (int)rec - BB_MOTOR_CENTER;
    motorCalibration[idx][BB_MOTOR_LEFT] = offset < 0 ? 90 + offset : 90;
    motorCalibration[idx][BB_MOTOR_RIGHT] = offset > 0 ? -90 + offset : -90;
}


// ---------------------------------------------------------------------------------------------
// GravitySwitch
// ---------------------------------------------------------------------------------------------

bool BrickBot::isRobotUpright() {

    // Get the current orientation of the robot
    int16_t accelZ = brain->getAccelerationZ();
    
    return  ((zAxisOrientationSide < zAxisOrientationUp) && (accelZ > zAxisOrientationSide)) ||
            ((zAxisOrientationSide > zAxisOrientationUp) && (accelZ < zAxisOrientationSide));
}


