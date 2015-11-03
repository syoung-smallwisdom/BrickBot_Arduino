//
//  BrickBotDriver.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 11/2/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef BrickBotDriver_hpp
#define BrickBotDriver_hpp

#include "BrickBotShared.h"
#include "BrickBotArduino.h"

#define BB_MOTOR_LEFT 0
#define BB_MOTOR_RIGHT 1

#define BB_MOTOR_STOP 90
#define BB_MOTOR_CENTER 90
#define BB_MOTOR_SLOW 20

typedef struct {
    uint8_t length = BBMotorCalibrationStateCount;
    uint8_t data[BBMotorCalibrationStateCount] = {BB_MOTOR_CENTER / 2, BB_MOTOR_CENTER, BB_MOTOR_CENTER * 3 / 2};
} BBCalibrationData;

class BrickBotDriver
{
public:

    void setDefaultCalibrationData(uint8_t *data, uint8_t length);
    BBCalibrationData getDefaultCalibrationData();
    
    void resetMotorCalibration();
    void saveMotorCalibration();
    void updateMotorCalibration(int idx, uint8_t rec);
    
    void runMotors(int dir, int steer);
    
    virtual uint8_t getMotorSpeed(int motor) { return 0;};
    virtual void setMotorValue(int motor, int spd) = 0;
    
protected:
    BBCalibrationData defaultCalibrationData;
    int motorCalibration[BBMotorCalibrationStateCount][2];
};

#endif /* BrickBotDriver_hpp */
