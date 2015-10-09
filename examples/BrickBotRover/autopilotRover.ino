/**
 * Autopilot using range finder
 */
static int reverseCount = 0;
static int forwardCount = 0;
static int autoSteer = BB_STEER_LEFT;

void resetAutopilot() {
  // reset if using remote
  reverseCount = 0;
  forwardCount = 0;
  autoSteer = BB_STEER_LEFT;
}

void runAutopilot() {
  
  if (reverseCount > 0) {
    // count down the reverse count if backing up
    reverseCount--;
    if (reverseCount == 10) {
      // Once the robot has backed up, then turn before starting forward again
      brickBot.runMotors(0, autoSteer);
      flipAutoSteer();
    }
  }
  else if (brickBot.hasObjectInFront()) {
    // Object in front detected so start the reverse
    reverseCount = 20;
    brickBot.runMotors(BB_DIR_BACKWARD, autoSteer);
    flipAutoSteer();
  }
  else {
    // move in serpentine - this gives the rangefinder a broader scope
    // which means it does a better job of "seeing" obsticles like chair legs
    brickBot.runMotors(BB_DIR_FORWARD, autoSteer);
    forwardCount++;
    if (forwardCount > 20) {
      flipAutoSteer();
    }
  }
}

void flipAutoSteer() {
  forwardCount = 0;
  autoSteer = (autoSteer == BB_STEER_LEFT) ? BB_STEER_RIGHT : BB_STEER_LEFT;
}
