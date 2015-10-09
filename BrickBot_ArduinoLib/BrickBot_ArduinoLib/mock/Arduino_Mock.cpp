//
//  Arduino_Mock.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/8/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "Arduino_Mock.hpp"

void delay(unsigned long delay) {
    std::cout << "delay " << delay << "\n";
}

void delayMicroseconds(unsigned int us) {
    std::cout << "delayMicroseconds " << us << "\n";
}

void pinMode(uint8_t pin, uint8_t type) {
    std::cout << "pinMode " << pin << ":" << type << "\n";
}

void digitalWrite(uint8_t pin, uint8_t state) {
    std::cout << "digitalWrite " << pin << ":" << state << "\n";
}

unsigned long pulseIn(uint8_t pin, uint8_t state) {
    std::cout << "pulseIn " << pin << ":" << state << "\n";
    return 55;
}

