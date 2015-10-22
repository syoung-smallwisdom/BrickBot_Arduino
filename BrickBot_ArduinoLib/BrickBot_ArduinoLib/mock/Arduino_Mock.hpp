//
//  Arduino_Mock.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/8/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef Arduino_Mock_hpp
#define Arduino_Mock_hpp

#include <iostream>
#include "Stream_Mock.hpp"
#include "Bean_Mock.hpp"

#ifdef __cplusplus
extern "C"{
#endif
    
#define HIGH 0x1
#define LOW  0x0
    
#define INPUT 0x0
#define OUTPUT 0x1
    
#define A0 0

void delay(unsigned long);
void delayMicroseconds(unsigned int us);
    
void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
    
int analogRead(uint8_t);
    
unsigned long pulseIn(uint8_t pin, uint8_t state);
    
void tone(uint8_t pin, unsigned int frequency, unsigned long duration = 0);
void noTone(uint8_t pin);
    
#ifdef __cplusplus
} // extern "C"
#endif

#endif /* Arduino_Mock_hpp */
