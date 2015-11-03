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
#include "BrickBotServoDriver.h"
#include "BrickBotBean.h"

class BrickBotTests: BrickBot {
public:
    BrickBotTests(BeanSerialTransport *serial, BeanClass *bean) :
    BrickBot(new BrickBotBean(serial, bean), new BrickBotServoDriver(0,1), new BrickBotRangeFinder())  {
        this->serialMock = serial;
        this->beanMock = bean;
    };
    static void runTests();
    
private:
    void testSetDirection(int dir, int steer, int expectedDir, int expectedSteer);
    void testStop();
    void testRun(int dir, int steer, int expectedLeft, int expectedRight);
    
    BeanSerialTransport *serialMock;
    BeanClass *beanMock;
    
};

#endif /* MotorControlTests_hpp */
