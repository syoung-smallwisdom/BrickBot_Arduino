//
//  BrickBotAutopilot.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 11/2/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef BrickBotAutopilot_hpp
#define BrickBotAutopilot_hpp

#include "BrickBot.h"


class BrickBotRover: public BrickBot {
public:
    void loop();
    
    BrickBotRover(BrickBotBrain *brain, BrickBotDriver *driver, BrickBotRangeFinder *rangeFinder) :
        BrickBot(brain, driver, rangeFinder) {};
    
protected:
    int reverseCount = 0;
    int forwardCount = 0;
    int autoSteer = BB_STEER_LEFT;
    void resetAutopilot();
    void runAutopilot();
    void flipAutoSteer();
};

#endif /* BrickBotAutopilot_hpp */
