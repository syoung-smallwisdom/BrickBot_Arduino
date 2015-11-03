
#include <BrickBotRover.h>
#include <BrickBotBean.h>
#include <Servo.h>
#include <BrickBotServoDriver.h>
#include <BrickBotHCSR04.h>

// Included locally - this is only used for rover2.
#include <Adafruit_NeoPixel.h>
#include "BrickBotNeopixelStrip.h"

#define PIN_POWER_SWITCH  A0        
#define PIN_LEFT          0
#define PIN_RIGHT         1
#define PIN_NEOPIXEL      2
#define PIN_RANGE_ECHO    3
#define PIN_RANGE_TRIGGER 4
#define PIN_AUDIO         5

BrickBotRover *controller;

void setup() {
  // Setup the serial connection
  Serial.begin(57600);
  Serial.setTimeout(5);

  // Attach the brickbot
  controller = new BrickBotRover(new BrickBotBean(&Serial, &Bean, A1), 
                                    new BrickBotServoDriver(PIN_LEFT, PIN_RIGHT), 
                                    new BrickBotHCSR04(PIN_RANGE_ECHO, PIN_RANGE_TRIGGER));
  controller->attachVoiceBox(new BrickBotPiezoVoiceBox(PIN_AUDIO));
  controller->attachLights(new BrickBotNeopixelStrip(2, PIN_NEOPIXEL));
}

void loop() {
  controller->loop();
}

