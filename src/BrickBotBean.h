//
//  BrickBotBean.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 11/2/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef BrickBotBean_hpp
#define BrickBotBean_hpp

#include "BrickBotBrain.h"

typedef struct {
    uint16_t ibeacon_uuid;
    uint16_t ibeacon_major;
    uint16_t ibeacon_minor;
} BBBeaconConfig;

class BrickBotBean : public BrickBotBrain
{
public:
    BrickBotBean(BeanSerialTransport *serial, BeanClass *bean, int powerSwitch = -1);
    
    bool getConnectionState();
    void sleep(uint32_t duration_ms);
    bool enabled();
    
    int16_t getAccelerationX(void);
    int16_t getAccelerationY(void);
    int16_t getAccelerationZ(void);
    
    size_t readSerialBytes( char *buffer, size_t length);
    size_t writeSerialBytes(const uint8_t *buffer, size_t size);
    size_t println(const String &s);
    
    void setName(const String &s);
    void setCalibrationData(BBCalibrationData data);
    
protected:
    BeanSerialTransport *serial;
    int powerSwitch;
    BeanClass *bean;
};

#endif /* BrickBotBean_hpp */
