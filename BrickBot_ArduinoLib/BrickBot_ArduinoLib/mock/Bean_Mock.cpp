//
//  Bean_Mock.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/8/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "Bean_Mock.hpp"

BeanClass Bean;
BeanSerialTransport Serial;

BeanClass::BeanClass() {
    for (int ii=1; ii <= 5; ii++) {
        scratchData[ii].length = 1;
        scratchData[ii].data[0] = 0;
    }
}

ScratchData BeanClass::readScratchData(uint8_t bank) {
    return scratchData[bank];
}

bool BeanClass::getConnectionState() {
    return connectionState;
}

int16_t BeanClass::getAccelerationZ (void) {
    return accelerationZ;
}

int16_t BeanClass::getAccelerationX(void) {
    return 0;
}

int16_t BeanClass::getAccelerationY(void) {
    return 0;
}

AccelerationReading BeanClass::getAcceleration() {
    AccelerationReading reading;
    return reading;
}

void BeanClass::sleep(uint32_t duration_ms) {
    // ignored
}

void BeanClass::enableWakeOnConnect( bool enable ) {
    // ignored
}

void BeanClass::setScratchData(uint8_t bank, const uint8_t* buffer, uint8_t length) {
    scratchData[bank].length = length;
    memcpy(scratchData[bank].data, buffer, length);
}

void BeanClass::setBeanName( const String &s ) {
    
}

const char* getBeanName(void) {
    return "";
}
