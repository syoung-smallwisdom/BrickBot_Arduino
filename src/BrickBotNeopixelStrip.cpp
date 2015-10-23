//
//  BrickBotNeopixelStrip.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/22/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "BrickBotNeopixelStrip.h"

BrickBotNeopixelStrip::BrickBotNeopixelStrip(int count, int pin) {
    this->strip = Adafruit_NeoPixel(count, pin, NEO_GRB + NEO_KHZ800);
    strip.begin();
    setEnabled(false);
}

bool BrickBotNeopixelStrip::getEnabled() {
    return strip.getBrightness() > 0;
}

void BrickBotNeopixelStrip::setEnabled(bool enabled) {
    if (enabled == getEnabled()) {
        // Do nothing if already enabled/disabled
        return;
    }
    uint8_t brightness = enabled ? 100 : 0;
    strip.setBrightness(brightness);
    strip.show();
}

uint16_t BrickBotNeopixelStrip::numPixels() {
    return strip.numPixels();
}

void BrickBotNeopixelStrip::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
    strip.setPixelColor(n, r, g, b);
}

void BrickBotNeopixelStrip::show() {
    strip.show();
}