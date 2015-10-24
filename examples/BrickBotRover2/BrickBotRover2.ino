#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include <BrickBot.h>
#include <BrickBotNeopixelStrip.h>

#define PIN_POWER_SWITCH  A0        
#define PIN_LEFT          0
#define PIN_RIGHT         1
#define PIN_NEOPIXEL      2
#define PIN_RANGE_ECHO    3
#define PIN_RANGE_TRIGGER 4
#define PIN_AUDIO         5

const int delayMilliseconds = 50;
BrickBot brickBot;

void setup() {
  // Setup the serial connection
  Serial.begin(57600);
  Serial.setTimeout(5);

  // Attach the brickbot
  brickBot.attach(new BrickBotBean(&Serial, &Bean, A1), PIN_LEFT, PIN_RIGHT);
  brickBot.attachVoiceBox(new BrickBotPiezoVoiceBox(PIN_AUDIO));
  brickBot.attachLights(new BrickBotNeopixelStrip(2, PIN_NEOPIXEL));

  // Setup sensors and outputs specific to this version of the robot
  setupRangeFinder(PIN_RANGE_ECHO, PIN_RANGE_TRIGGER);
}

void loop() {

    // Update the brickbot state (and run robot if using remote)
    // This should be checked at the beginning of each loop to test for the 
    // robot being run remotely or turtled (turned over).
    BrickBotState state = brickBot.updateState();

    // Check for state changes
    bool shouldRun = (state.autopilotOn || state.connected) && state.enabled;

    // If the autopilot is ON or the robot is connected to a remote
    // then update the autopilot routine and then wait before looping again.
    if (shouldRun) {
    
      if (state.autopilotOn && !state.remoteOn) {
        // If the autopilot is on then check the range
        runAutopilot();
      }
      else {
        // Otherwise, reset the autopilot state
        resetAutopilot();
      }
    
      // use a delay rather than a Bean.sleep so that the motors stay active
      delay(delayMilliseconds);
      
    }
    else {
      // let the bean sleep
      Bean.sleep(500);     
    }
}

void sleep() {
  Bean.sleep(1000);
}

