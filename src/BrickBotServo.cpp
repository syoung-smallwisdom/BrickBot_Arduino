//
//  BrickBotServo.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/8/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "BrickBotServo.h"

BrickBotServo::BrickBotServo(int pin) {
    motor.attach(pin);
}

void BrickBotServo::write(int value) {
    motor.write(value);
}

int BrickBotServo::read() {
    return motor.read();
}