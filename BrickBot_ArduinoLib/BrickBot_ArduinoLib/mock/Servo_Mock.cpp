//
//  Servo_Mock.cpp
//  BrickBot_ArduinoTest
//
//  Created by Shannon Young on 10/7/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "Servo_Mock.hpp"

uint8_t Servo::attach(int pin) {
    _pin = pin;
    std::cout << "attach " << pin << "\n";
    return 1;
}

void Servo::write(int value) {
    std::cout << "write " << value << " to pin " << _pin << "\n";
    _value = value;
}

int Servo::read() {
    std::cout << "read pin " << _pin << " = " << _value << "\n";
    return _value;
}

