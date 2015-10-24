
const int durationThreshold = 800;
const int veryFarThreshold = 11000;
const int veryNearThreshold = 220000;

static int echoPin;
static int triggerPin;

void setupRangeFinder(int ePin, int tPin) {
    triggerPin = tPin;
    echoPin = ePin;

    // Set the pinMode for each pin
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

bool hasObjectInFront() {
    
    // trigger a read
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(triggerPin, LOW);
    
    // read value
    long duration = pulseIn(echoPin, HIGH);
    bool ret = (duration < durationThreshold) || (duration > veryNearThreshold);

    Serial.println("duration:" + String(duration) + ", ret:" + String(ret));
    
    return ret;
}
