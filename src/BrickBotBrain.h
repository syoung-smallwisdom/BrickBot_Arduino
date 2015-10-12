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

#ifndef BrickBot_Simulator
#include <Arduino.h>
#else
#include "Arduino_Mock.hpp"
#endif

#include "BrickBotShared.h"

class BrickBotBrainProtocol
{
public:
    virtual bool getConnectionState() { return false; };
    virtual void sleep(uint32_t duration_ms) = 0;
    
    virtual int16_t getAccelerationX(void) { return 0; };
    virtual int16_t getAccelerationY(void) { return 0; };
    virtual int16_t getAccelerationZ(void) { return 0; };
    
    virtual ScratchData readScratchData(uint8_t bank) {
        ScratchData ret; return ret;
    };
    virtual void setScratchData(uint8_t bank, const uint8_t* buffer, uint8_t length) = 0;
    
    virtual size_t readSerialBytes( char *buffer, size_t length) { return 0; };
    virtual void println(const char* str) = 0;
    
};

class BrickBotBean : public BrickBotBrainProtocol
{
public:
    BrickBotBean(Stream *serial, BeanClass *bean);
    
    bool getConnectionState();
    void sleep(uint32_t duration_ms);
    
    int16_t getAccelerationX(void);
    int16_t getAccelerationY(void);
    int16_t getAccelerationZ(void);
    
    ScratchData readScratchData(uint8_t bank);
    void setScratchData(uint8_t bank, const uint8_t* buffer, uint8_t length);
    
    size_t readSerialBytes( char *buffer, size_t length);
    void println(const char* str);
    
protected:
    Stream *serial;
    BeanClass *bean;
};

#endif /* BrickBotBrain_hpp */
