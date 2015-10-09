//
//  Bean_Mock.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/8/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef Bean_Mock_hpp
#define Bean_Mock_hpp

#include <stdio.h>
#include <iostream>

typedef struct {
    uint8_t length;
    uint8_t data[20];
} ScratchData;

class BeanClass {
public:
    bool getConnectionState();
    ScratchData readScratchData(uint8_t bank);
    int16_t getAccelerationX(void);
    int16_t getAccelerationY(void);
    int16_t getAccelerationZ(void);
    void sleep(uint32_t duration_ms);
    void enableWakeOnConnect( bool enable );
    void setScratchData(uint8_t bank, const uint8_t* buffer, uint8_t length);
    BeanClass();
    
    bool connectionState = false;
    ScratchData scratchData[6];
    int16_t accelerationZ = 220;
    
};

extern BeanClass Bean;

#endif /* Bean_Mock_hpp */
