//
//  BrickBotRangeFinder.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/8/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef BrickBotRangeFinder_hpp
#define BrickBotRangeFinder_hpp

#ifndef BrickBot_Simulator
#include <Arduino.h>
#else
#include "Arduino_Mock.hpp"
#endif

class BrickBotRangeFinderProtocol
{
public:
    virtual bool hasObjectInFront() { return false; };
};

class BrickBotRangeFinder : public BrickBotRangeFinderProtocol
{
public:
    BrickBotRangeFinder(int triggerPin, int echoPin);
    bool hasObjectInFront();
    int durationThreshold = 800;
    
protected:
    int triggerPin;
    int echoPin;
};

#endif /* BrickBotRangeFinder_hpp */
