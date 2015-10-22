#include <Servo.h>
#include <BrickBot.h>

#define PIN_LEFT  0
#define PIN_RIGHT 1
#define PIN_TRIG  3
#define PIN_ECHO  2

const int delayMilliseconds = 50;
BrickBot brickBot;
//uint8_t previousLeftSpeed = 0;
//uint8_t previousRightSpeed = 0;

void setup() {
  // Setup the serial connection
  Serial.begin(57600);
  Serial.setTimeout(5);

  // Attach the brickbot
  brickBot.attach(new BrickBotBean(&Serial, &Bean), PIN_LEFT, PIN_RIGHT, PIN_TRIG, PIN_ECHO);
}

void loop() {

  // Update the brickbot state (and run robot if using remote)
  // This should be checked at the beginning of each loop to test for the 
  // robot being run remotely or turtled (turned over).
  BrickBotState state = brickBot.updateState();

  // If the autopilot is ON or the robot is connected to a remote
  // then update the autopilot routine and then wait before looping again.
  if (state.autopilotOn || state.connected) {
 
    if (state.autopilotOn && !state.remoteOn) {
      // If the autopilot is on then check the range
      runAutopilot();
    }
    else {
      // Otherwise, reset the autopilot state
      resetAutopilot();
    }

//    uint8_t leftSpeed = brickBot.getMotorSpeed(0);
//    uint8_t rightSpeed = brickBot.getMotorSpeed(1);
//
//    if ((leftSpeed != previousLeftSpeed) || (rightSpeed != previousRightSpeed)) {
//      previousLeftSpeed = leftSpeed;
//      previousRightSpeed = rightSpeed;
//      Serial.println("Speed changed. {" + String(leftSpeed) + "," + String(rightSpeed) + "}");
//    }

    // use a delay rather than a Bean.sleep so that the motors stay active
    delay(delayMilliseconds);
  }
  else {
    // Otherwise, put the robot to sleep
    brickBot.sleep();
  }
}

