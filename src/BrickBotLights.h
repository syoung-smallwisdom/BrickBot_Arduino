//
//  BrickBotLights.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/22/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef BrickBotLights_hpp
#define BrickBotLights_hpp

#include "BrickBotArduino.h"

class BrickBotLights
{
public:
    virtual void setEnabled(bool enabled) {};
    virtual bool getEnabled() { return true; };
    virtual uint16_t numPixels() { return 1; };
    virtual void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) = 0;
    virtual void show() {};
    void step();
    
protected:
    uint16_t currentStep = 0;
};

#endif /* BrickBotLights_hpp */
