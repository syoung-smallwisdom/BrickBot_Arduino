//
//  BrickBotNeopixelStrip.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/22/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef BrickBotNeopixelStrip_hpp
#define BrickBotNeopixelStrip_hpp

#include "BrickBotLights.h"

#ifndef BrickBot_Simulator
#include <Adafruit_NeoPixel.h>
#else
#include "Neopixel_Mock.hpp"
#endif

class BrickBotNeopixelStrip: public BrickBotLights
{
public:
    BrickBotNeopixelStrip(int count, int pin);
    
    bool getEnabled();
    void setEnabled(bool enabled);
    uint16_t numPixels();
    void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
    void show();
    
protected:
    Adafruit_NeoPixel strip;
};

#endif /* BrickBotNeopixelStrip_hpp */
