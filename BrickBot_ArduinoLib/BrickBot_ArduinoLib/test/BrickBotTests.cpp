//
//  MotorControlTests.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/7/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "BrickBotTests.hpp"

void BrickBotTests::runTests() {
    
    // Attach the serial and bean
    BeanSerialTransport *serialMock = new BeanSerialTransport();
    BeanClass *beanMock = new BeanClass();
    
    // Attach to mock servos for test
    BrickBotTests tests = BrickBotTests(serialMock, beanMock);

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
    tests.driver->resetMotorCalibration();
    
    // Test Turtle - robot rolls over or is picked up by a 2 year old
    // start moving forward
    tests.testRun(BB_DIR_FORWARD, 0, 180, 0);
    // turn upside down and update state
    tests.beanMock->accelerationZ = -220;
    tests.updateState();
    // Check that the motors are stopped
    assert(tests.driver->getMotorSpeed(0) == 90);
    assert(tests.driver->getMotorSpeed(1) == 90);
    // turn rightside up and update state
    tests.beanMock->accelerationZ = 220;
    tests.updateState();
    assert(tests.driver->getMotorSpeed(0) == 180);
    assert(tests.driver->getMotorSpeed(1) == 0);
    
    // Test Stop
    tests.testStop();

    // Test Run - following motor calibration
    // Desired = {{20, -90}, {90, -34}, {90, -18}};
    tests.serialMock->length = 4;
    uint8_t buffer[4] = {BBControlFlagMotorCalibration, 20, 146, 162};
    memcpy(tests.serialMock->buffer, buffer, 4);
    tests.beanMock->connectionState = true;
    tests.updateState();
    tests.testRun(BB_DIR_FORWARD, 0, 180, 56);
    tests.testRun(BB_DIR_FORWARD, BB_STEER_RIGHT, 180, 72);
    tests.testRun(BB_DIR_FORWARD, BB_STEER_LEFT, 110, 0);
    
    // check setting/getting motor calibration
    tests.driver->saveMotorCalibration();
    BBCalibrationData data = tests.driver->getDefaultCalibrationData();
    assert(data.length == 3);
    assert(data.data[0] == 20);
    assert(data.data[1] == 146);
    assert(data.data[2] == 162);
}

void BrickBotTests::testStop() {
    
    this->stopMotors(true);
    
    assert(this->driver->getMotorSpeed(0) == 90);
    assert(this->driver->getMotorSpeed(1) == 90);
    assert(this->_dir == 0);
    assert(this->_steer == 0);
}

void BrickBotTests::testRun(int dir, int steer, int expectedLeft, int expectedRight) {
    
    this->updateState();
    this->runMotors(dir, steer);
    
    assert(this->driver->getMotorSpeed(0) == expectedLeft);
    assert(this->driver->getMotorSpeed(1) == expectedRight);
}