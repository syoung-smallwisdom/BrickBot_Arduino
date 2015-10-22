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

void BrickBot::attachVoiceBox(BrickBotVoiceBoxProtocol *voiceBox) {
    this->voiceBox = voiceBox;
    hasVoiceBox = true;
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
    
    connectedOn = false;
    
    // reset state
    state.autopilotOn = false;
    state.remoteOn = false;
    state.connected = false;
    
    // stop the motors
    stopMotors();
}

void BrickBot::wakeup() {
    connectedOn = false;
    state.autopilotOn = true;
    if (hasVoiceBox) {
        this->voiceBox->sayHello();
    }
}

BrickBotState BrickBot::updateState() {
    
    bool previouslyEnabled = state.enabled;
    state.enabled = brain->enabled();
    
    if (!state.enabled) {
        if (previouslyEnabled) {
            sleep();
        }
        return state;
    }
    else if (state.enabled && !previouslyEnabled) {
        wakeup();
    }
    
    state.connected = brain->getConnectionState();
    
    // Get the current state
    bool isRobotUpright = this->isRobotUpright();
    bool robotChangedOrientation = (state.isRobotUpright != isRobotUpright);
    state.isRobotUpright = isRobotUpright;
    
    if (state.connected) {
        if (!connectedOn) {
            // If this is the first connect, turn off the autopilot by default
            // The connected devise can turn it back on manually.
            state.autopilotOn = false;
        }
        checkRemote();
    }
    else {
        state.remoteOn = false;
    }
    
    if (!state.remoteOn && !state.autopilotOn) {
        stopMotors();
    }
    
    // If the robot has changed orientation then update the motor state
    if (robotChangedOrientation) {
        updateMotorState();
    }
    
    return state;
}

void BrickBot::checkRemote() {
    
    //Create a buffer to recieve from LightBlue, along with length
    char rec_buffer[64];
    size_t rec_length = 64;
    
    //Set the length to number of bytes recieved
    rec_length = brain->readSerialBytes(rec_buffer, rec_length);
    if (rec_length > 0) {
        uint8_t controlFlag = rec_buffer[0];
        if (controlFlag == BBControlFlagRemote) {
            BBControlStruct control;
            bool remoteOn = (rec_buffer[1] != 0);
            if (remoteOn) {
                // If the remote is on then run the motors
                memcpy(&control, &rec_buffer[1], sizeof(control));
                runMotors((int)control.dir - 1, (int)control.steer - 1);
            }
            state.remoteOn = remoteOn;
        }
        else if (controlFlag == BBControlFlagAutopilot) {
            // Update the autopilot
            state.autopilotOn = (rec_buffer[1] != 0);
            if (!state.remoteOn && !state.autopilotOn) {
                // If the autopilot is turned off (and the remote is not on)
                // then stop the motors.
                stopMotors();
            }
        }
        else if (controlFlag == BBControlFlagResetCalibration) {
            // Read the motor calibration from the scratch banks
            resetMotorCalibration();
        }
        else if (controlFlag == BBControlFlagMotorCalibration) {
            // Set the motor calibration for each motor state
            for (int ii=1; ii < rec_length && ii < BBMotorCalibrationStateCount; ii++) {
                updateMotorCalibration(ii - 1, rec_buffer[ii]);
                updateMotorState();
            }
        }
        
        // No matter what, copy back the message to indicate that it was received
        uint8_t buffer[rec_length];
        memcpy(buffer, rec_buffer, rec_length);
        brain->writeSerialBytes(buffer, rec_length);
        
    }
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
    if (currentSpd == spd) {
        // Speed has not changed
        return;
    }
    
    // If this is a switch from forward/backward then send the
    // stop signal and set a delay
    if ((spd > BB_MOTOR_STOP && currentSpd < BB_MOTOR_STOP) ||
        (spd < BB_MOTOR_STOP && currentSpd > BB_MOTOR_STOP)) {
        servo->write(BB_MOTOR_STOP);
        delay(50);
    }
    
    // write to the appropriate motor
    servo->write(spd);
    
    // Send message that motor speed changed
    uint8_t flag = (motor == BB_MOTOR_LEFT) ? BBControlFlagLeftMotorChanged : BBControlFlagRightMotorChanged;
    uint8_t buffer[] = {flag, (uint8_t)spd};
    brain->writeSerialBytes(buffer, sizeof(buffer));
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
            for (int jj=0; jj < 2; jj++) {
                motorCalibration[ii][jj] = defaultMotorCalibration[ii][jj];
            }
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


