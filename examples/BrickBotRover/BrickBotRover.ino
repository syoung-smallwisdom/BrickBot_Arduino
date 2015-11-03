#include <Servo.h>
#include <BrickBotRover.h>
#include <BrickBotBean.h>
#include <BrickBotServoDriver.h>
#include <BrickBotHCSR04.h>

#define PIN_LEFT          0
#define PIN_RIGHT         1
#define PIN_RANGE_ECHO    3
#define PIN_RANGE_TRIGGER 4

BrickBotRover *controller;

void setup() {
  // Setup the serial connection
  Serial.begin(57600);
  Serial.setTimeout(5);

  // Instantiate the classes that are used for this robot to define the brain, driver and range finder
  // This robot doesn't have lights or sound.
  BrickBotBean *brain = new BrickBotBean(&Serial, &Bean);
  BrickBotServoDriver *driver = new BrickBotServoDriver(PIN_LEFT, PIN_RIGHT);
  BrickBotHCSR04 *rangeFinder = new BrickBotHCSR04(PIN_RANGE_ECHO, PIN_RANGE_TRIGGER);
  
  // Setup motor calibration - must be done in setup b/c there is no way to save calibration data
  // across poweron. Set it on the driver, and then save that value to the brain.
  uint8_t data[3] = {BB_MOTOR_CENTER / 2, BB_MOTOR_CENTER, BB_MOTOR_CENTER * 3 / 2};
  driver->setDefaultCalibrationData(data, 3);
  brain->setCalibrationData(driver->getDefaultCalibrationData());

  // Setup the controller
  controller = new BrickBotRover(brain, driver, rangeFinder);
}

void loop() {
  controller->loop();
}

