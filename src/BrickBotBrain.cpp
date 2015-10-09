//
//  BrickBotBrain.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/9/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "BrickBotBrain.h"

BrickBotBean::BrickBotBean(Stream *serial, BeanClass *bean) {
    
    // assign pointers
    this->serial = serial;
    this->bean = bean;
    
    // Setup the bean to wake up when connected to the remote
    this->bean->enableWakeOnConnect(true);
}

bool BrickBotBean::getConnectionState() {
    return bean->getConnectionState();
}

void BrickBotBean::sleep(uint32_t duration_ms) {
    bean->sleep(duration_ms);
}

int16_t BrickBotBean::getAccelerationX(void) {
    return bean->getAccelerationX();
}

int16_t BrickBotBean::getAccelerationY(void) {
    return bean->getAccelerationY();
}

int16_t BrickBotBean::getAccelerationZ(void) {
    return bean->getAccelerationZ();
}

ScratchData BrickBotBean::readScratchData(uint8_t bank) {
    return bean->readScratchData(bank);
}

void BrickBotBean::setScratchData(uint8_t bank, const uint8_t* buffer, uint8_t length) {
    bean->setScratchData(bank, buffer, length);
}

size_t BrickBotBean::readSerialBytes( char *buffer, size_t length){
    return serial->readBytes(buffer, length);
}

void BrickBotBean::println(const char* str) {
    serial->println(str);
}

