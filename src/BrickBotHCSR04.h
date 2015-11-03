//
//  HCSR04RangeFinder.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 11/2/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef HCSR04RangeFinder_hpp
#define HCSR04RangeFinder_hpp

#include "BrickBotRangeFinder.h"

class BrickBotHCSR04: public BrickBotRangeFinder
{
public:
    BrickBotHCSR04(int ePin, int tPin);
    bool hasObjectInFront();
       
private:
    int echoPin;
    int triggerPin;
};

#endif /* HCSR04RangeFinder_hpp */
