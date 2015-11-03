//
//  BrickBotRangeFinder.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 11/2/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef BrickBotRangeFinder_hpp
#define BrickBotRangeFinder_hpp

#include "BrickBotArduino.h"

class BrickBotRangeFinder
{
public:
    virtual bool hasObjectInFront() { return false; };
};

#endif /* BrickBotRangeFinder_hpp */
