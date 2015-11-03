//
//  BrickBotDriver.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 11/2/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "BrickBotDriver.h"

void BrickBotDriver::runMotors(int dir, int steer) {
    if (dir == 0) {
        if (steer == 0) {
            setMotorValue(BB_MOTOR_RIGHT, BB_MOTOR_STOP);
            setMotorValue(BB_MOTOR_LEFT, BB_MOTOR_STOP);
        }
        else {
            setMotorValue(BB_MOTOR_RIGHT, steer * BB_MOTOR_SLOW + 90);
            setMotorValue(BB_MOTOR_LEFT, steer * BB_MOTOR_SLOW + 90);
        }
    }
    else {
        for (int mm=BB_MOTOR_LEFT; mm <= BB_MOTOR_RIGHT; mm++) {
            int spd =dir * motorCalibration[steer + 1][mm] + 90;
            setMotorValue(mm, spd);
        }
    }
}

void BrickBotDriver::setDefaultCalibrationData(uint8_t *data, uint8_t length) {
    if (length == BBMotorCalibrationStateCount) {
        for (int ii=0; ii < BBMotorCalibrationStateCount; ii++) {
            defaultCalibrationData.data[ii] = data[ii];
            updateMotorCalibration(ii, data[ii]);
        }
    }
}

BBCalibrationData BrickBotDriver::getDefaultCalibrationData() {
    return defaultCalibrationData;
}

void BrickBotDriver::resetMotorCalibration() {
    for (int ii=0; ii < defaultCalibrationData.length; ii++) {
        updateMotorCalibration(ii, defaultCalibrationData.data[ii]);
    }
}

void BrickBotDriver::updateMotorCalibration(int idx, uint8_t rec) {
    // If the normalized value is negative, then change LEFT, else change RIGHT
    int offset = (int)rec - BB_MOTOR_CENTER;
    motorCalibration[idx][BB_MOTOR_LEFT] = offset < 0 ? BB_MOTOR_CENTER + offset : BB_MOTOR_CENTER;
    motorCalibration[idx][BB_MOTOR_RIGHT] = offset > 0 ? -1*BB_MOTOR_CENTER + offset : -1*BB_MOTOR_CENTER;
}

void BrickBotDriver::saveMotorCalibration() {
    for (int ii=0; ii < BBMotorCalibrationStateCount; ii++) {
        if (motorCalibration[ii][BB_MOTOR_LEFT] == 90) {
            defaultCalibrationData.data[ii] = 2*BB_MOTOR_CENTER + motorCalibration[ii][BB_MOTOR_RIGHT];
        }
        else {
            defaultCalibrationData.data[ii] = motorCalibration[ii][BB_MOTOR_LEFT];
        }
    }
}

