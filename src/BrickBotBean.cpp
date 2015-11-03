//
//  BrickBotBean.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 11/2/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "BrickBotBean.h"

BrickBotBean::BrickBotBean(BeanSerialTransport *serial, BeanClass *bean, int powerSwitch) {
    
    // assign pointers
    this->serial = serial;
    this->bean = bean;
    this->powerSwitch = powerSwitch;
    
    // Setup the bean to wake up when connected to the remote
    this->bean->enableWakeOnConnect(true);
    
    // write the sketch id to the scratch bank for this library
    // This is used by the remote to confirm the sketch is valid and to get the version
    uint8_t data[] = "BrickBot_1.0.0";
    uint8_t length = sizeof(data);
    this->bean->setScratchData(BBReservedScratchBankSketchId, data, length);
}

bool BrickBotBean::getConnectionState() {
    return bean->getConnectionState();
}

void BrickBotBean::sleep(uint32_t duration_ms) {
    bean->sleep(duration_ms);
}

int16_t BrickBotBean::getAccelerationX(void) {
    AccelerationReading accel = Bean.getAcceleration();
    return accel.xAxis;
}

int16_t BrickBotBean::getAccelerationY(void) {
    AccelerationReading accel = Bean.getAcceleration();
    return accel.yAxis;
}

int16_t BrickBotBean::getAccelerationZ(void) {
    AccelerationReading accel = Bean.getAcceleration();
    return accel.zAxis;
}

size_t BrickBotBean::readSerialBytes( char *buffer, size_t length){
    return serial->readBytes(buffer, length);
}

size_t BrickBotBean::writeSerialBytes(const uint8_t *buffer, size_t size) {
    return serial->write(buffer, size);
}

size_t BrickBotBean::println(const String &s) {
    return serial->println(s);
}

bool BrickBotBean::enabled() {
    if (powerSwitch >= 0) {
        // by default, Bean will run on 3.3v line while the motors and leds run on 5v,
        // read the voltage on the 5v line using a transistor to step it down.
        int av = analogRead(powerSwitch);
        return av > 150;
    }
    else {
        return true;
    }
}

void BrickBotBean::setName(const String &s ) {
    bean->setBeanName(s);
}

void BrickBotBean::setCalibrationData(BBCalibrationData data) {
    bean->setScratchData(BBReservedScratchBankMotorCalibration, data.data, data.length);
}