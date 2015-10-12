//
//  BrickBotTests.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/7/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef BrickBotTests_hpp
#define BrickBotTests_hpp

#include <iostream>
#include <assert.h>
#include "BrickBot.h"

class BrickBotServoMock : public BrickBotServoProtocol
{
public:
    BrickBotServoMock(int pin);
    void write(int value);
    int read();
    int value;
    int pin;
};

class BrickBotTests: BrickBot {
public:
    static void runTests();
private:
    void testSetDirection(int dir, int steer, int expectedDir, int expectedSteer);
    void testStop();
    void testRun(int dir, int steer, int expectedLeft, int expectedRight);
    
    BrickBotServoMock *leftServoMock;
    BrickBotServoMock *rightServoMock;
    Stream *serialMock;
    BeanClass *beanMock;
    
};

#endif /* MotorControlTests_hpp */
