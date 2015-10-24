//
//  BrickBotShared.h
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/9/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef BrickBotShared_h
#define BrickBotShared_h

#include <stdint.h>

#define BB_DIR_FORWARD 1
#define BB_DIR_BACKWARD -1
#define BB_STEER_RIGHT 1
#define BB_STEER_LEFT -1

enum BBControlFlag: uint8_t {
    BBControlFlagLeftMotorChanged = 0xE0,
    BBControlFlagRightMotorChanged = 0xE1,
    BBControlFlagRemote = 0xF0,
    BBControlFlagAutopilot = 0xF1,
    BBControlFlagMotorCalibration = 0xF2,
    BBControlFlagResetCalibration = 0xF3,
    BBControlFlagSaveCalibration = 0xF4,
    BBControlFlagSetName = 0xF5,
};

enum BBReservedScratchBank: uint8_t {
    BBReservedScratchBankSketchId = 1,
    BBReservedScratchBankMotorCalibration = 3
};

enum BBMotorCalibrationState: uint8_t {
    BBMotorCalibrationStateForwardLeft = 0,
    BBMotorCalibrationStateForwardStraight,
    BBMotorCalibrationStateForwardRight,
    BBMotorCalibrationStateCount
};

typedef struct {
    uint8_t steer: 2;     // 2-bit = left, center, right
    uint8_t dir: 2;       // 2-bit = back, center, forward
    bool remoteOn: 1;
    uint8_t padding: 3;
} BBControlStruct;

#endif /* BrickBotShared_h */
