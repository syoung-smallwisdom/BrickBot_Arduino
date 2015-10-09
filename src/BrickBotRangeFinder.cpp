//
//  BrickBotRangeFinder.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/8/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "BrickBotRangeFinder.h"

BrickBotRangeFinder::BrickBotRangeFinder(int triggerPin, int echoPin) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;

    // Set the pinMode for each pin
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

bool BrickBotRangeFinder::hasObjectInFront() {
    
    // trigger a read
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(triggerPin, LOW);
    
    // read value
    long duration = pulseIn(echoPin, HIGH);
    
    return duration < durationThreshold;
}