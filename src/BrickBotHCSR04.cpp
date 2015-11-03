//
//  BrickBotHCSR04RangeFinder.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 11/2/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "BrickBotHCSR04.h"

const int durationThreshold = 800;
//const int veryFarThreshold = 11000;
const int veryNearThreshold = 220000;

BrickBotHCSR04::BrickBotHCSR04(int ePin, int tPin) {
    triggerPin = tPin;
    echoPin = ePin;
    
    // Set the pinMode for each pin
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

bool BrickBotHCSR04::hasObjectInFront() {
    
    // trigger a read
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(triggerPin, LOW);
    
    // read value
    long duration = pulseIn(echoPin, HIGH);
    bool ret = (duration < durationThreshold) || (duration > veryNearThreshold);
    
//    Serial.println("Duration:" + String(duration) + ", ret:" + String(ret) + ", Acceleration:" + String(accel.xAxis) + ", " + String(accel.yAxis) + ", " + String(accel.zAxis) + ", sensitivity:" + String(accel.sensitivity));
    
    return ret;
}