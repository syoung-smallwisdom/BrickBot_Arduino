//
//  main.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/7/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include <iostream>

#include "BrickBot.h"

#include "BrickBotTests.hpp"

int main(int argc, const char * argv[]) {
    
    BrickBotTests::runTests();
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}


