//
//  BrickBotLights.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/22/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "BrickBotLights.h"

void BrickBotLights::step(){
    
    for(uint16_t i=0; i<this->numPixels(); i++) {
        
        uint8_t wheelPos = (128*i+currentStep) & 255;
        uint8_t r, g, b;
        if(wheelPos < 85) {
            r = wheelPos * 3; g = 255 - wheelPos * 3; b = 0;
        } else if(wheelPos < 170) {
            wheelPos -= 85;
            r = 255 - wheelPos * 3; g = 0; b = wheelPos * 3;
        } else {
            wheelPos -= 170;
            r = 0; g = wheelPos * 3; b = 255 - wheelPos * 3;
        }
        
        this->setPixelColor(i, r, g, b);
    }
    this->show();
    
    currentStep += 2;
    if (currentStep >= 256) {
        currentStep = 0;
    }
}