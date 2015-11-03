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
#include "WString.h"
#include "Stream_Mock.hpp"

typedef struct {
    uint8_t length;
    uint8_t data[20];
} ScratchData;

typedef struct {
    int16_t xAxis;
    int16_t yAxis;
    int16_t zAxis;
    uint8_t sensitivity;
} AccelerationReading;

class BeanClass {
public:
    void setBeanName( const String &s );
    const char* getBeanName(void);
    bool getConnectionState();
    ScratchData readScratchData(uint8_t bank);
    int16_t getAccelerationX(void);
    int16_t getAccelerationY(void);
    int16_t getAccelerationZ(void);
    AccelerationReading getAcceleration();
    void sleep(uint32_t duration_ms);
    void enableWakeOnConnect( bool enable );
    void setScratchData(uint8_t bank, const uint8_t* buffer, uint8_t length);
    void setBeaconParameters( uint16_t uuid, uint16_t major_id, uint16_t minor_id );
    BeanClass();
    
    bool connectionState = false;
    ScratchData scratchData[6];
    int16_t accelerationZ = 220;
    
};

extern BeanClass Bean;

class BeanSerialTransport : public Stream {
    friend class BeanClass;
};

extern BeanSerialTransport Serial;

#endif /* Bean_Mock_hpp */
