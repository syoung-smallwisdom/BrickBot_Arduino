//
//  BrickBotBrain.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/9/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

/**
 * This is a wrapper class for using whichever "brain" (Arduino controller) that you would like.
 * Defined here is the wrapper for a LightBlue Bean which is the controller that I used for this 
 * project.
 */

#ifndef BrickBotBrain_hpp
#define BrickBotBrain_hpp

#include "BrickBotArduino.h"
#include "BrickBotShared.h"
#include "BrickBotDriver.h"

class BrickBotBrain
{
public:
    virtual bool getConnectionState() { return false; };
    virtual bool enabled() { return true; };
    virtual void sleep(uint32_t duration_ms) {
        delay(duration_ms);
    };
    
    virtual int16_t getAccelerationX(void) { return 0; };
    virtual int16_t getAccelerationY(void) { return 0; };
    virtual int16_t getAccelerationZ(void) { return 0; };
    
    virtual size_t readSerialBytes( char *buffer, size_t length) { return 0; };
    virtual size_t writeSerialBytes(const uint8_t *buffer, size_t size) { return 0; };
    virtual size_t println(const String &s) { return 0; };
    
    virtual void setName(const String &s) = 0;
    virtual void setCalibrationData(BBCalibrationData data) = 0;
}; 

#endif /* BrickBotBrain_hpp */
