//
//  MotorControlTests.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/7/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "BrickBotTests.hpp"

void BrickBotTests::runTests() {
    
    BrickBotTests tests;
    
    // Attach the serial and bean
    tests.serialMock = new Stream();
    tests.beanMock = new BeanClass();
    tests.attachComm(new BrickBotBean(tests.serialMock, tests.beanMock));
    
    // Attach to mock servos for test
    tests.leftServoMock = new BrickBotServoMock(0);
    tests.rightServoMock = new BrickBotServoMock(1);
    tests.attachServos(tests.leftServoMock, tests.rightServoMock);

    // Test Stop
    tests.testStop();
    
    // Test Run - using default calibration
    tests.testRun(BB_DIR_FORWARD, 0, 180, 0);
    tests.testRun(BB_DIR_FORWARD, BB_STEER_RIGHT, 180, 45);
    tests.testRun(BB_DIR_FORWARD, BB_STEER_LEFT, 135, 0);
    tests.testRun(BB_DIR_BACKWARD, 0, 0, 180);
    tests.testRun(BB_DIR_BACKWARD, BB_STEER_RIGHT, 0, 135);
    tests.testRun(BB_DIR_BACKWARD, BB_STEER_LEFT, 45, 180);
    tests.testRun(2, -2, 135, 0);
    tests.testRun(-2, 2, 0, 135);
    
    // Test Stop
    tests.testStop();
    
    // Test Run - following motor calibration
    // Desired = {{20, -90}, {90, -34}, {90, -18}};
    uint8_t buffer[3] = {20, 146, 162};
    tests.beanMock->setScratchData(BBReservedScratchBankMotorCalibration, buffer, 3);
    tests.resetMotorCalibration();
    tests.testRun(BB_DIR_FORWARD, 0, 180, 56);
    tests.testRun(BB_DIR_FORWARD, BB_STEER_RIGHT, 180, 72);
    tests.testRun(BB_DIR_FORWARD, BB_STEER_LEFT, 110, 0);
    
    // Test Stop
    tests.testStop();
    
    // Test Turtle - robot rolls over or is picked up by a 2 year old
    uint8_t buffer_clear[1] = {0};
    tests.beanMock->setScratchData(BBReservedScratchBankMotorCalibration, buffer_clear, 1);
    tests.resetMotorCalibration();
    // start moving forward
    tests.testRun(BB_DIR_FORWARD, 0, 180, 0);
    // turn upside down and update state
    tests.beanMock->accelerationZ = -220;
    tests.updateState();
    // Check that the motors are stopped
    assert(tests.leftServoMock->value == 90);
    assert(tests.rightServoMock->value == 90);
    // turn rightside up and update state
    tests.beanMock->accelerationZ = 220;
    tests.updateState();
    assert(tests.leftServoMock->value == 180);
    assert(tests.rightServoMock->value == 0);
    
    
}

BrickBotServoMock::BrickBotServoMock(int pin) {
    this->pin = pin;
}

void BrickBotServoMock::write(int value) {
    this->value = value;
    std::cout << "write " << value << " to pin " << this->pin << "\n";
}

int BrickBotServoMock::read() {
    std::cout << "read pin " << this->pin << " = " << value << "\n";
    return this->value;
}

void BrickBotTests::testStop() {
    
    this->stopMotors();
    
    assert(this->leftServoMock->value == 90);
    assert(this->rightServoMock->value == 90);
    assert(this->_dir == 0);
    assert(this->_steer == 0);
}

void BrickBotTests::testRun(int dir, int steer, int expectedLeft, int expectedRight) {
    
    this->runMotors(dir, steer);
    
    assert(this->leftServoMock->value == expectedLeft);
    assert(this->rightServoMock->value == expectedRight);
}