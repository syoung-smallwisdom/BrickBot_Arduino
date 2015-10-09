//
//  Stream_Mock.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/8/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef Stream_Mock_hpp
#define Stream_Mock_hpp

#include <stdio.h>
#include <string.h>
#include <iostream>

class Stream
{
public:
    size_t readBytes( char *buffer, size_t length); // read chars from stream into buffer
    // terminates if length characters have been read or timeout (see setTimeout)
    // returns the number of characters placed in the buffer (0 means no valid data found)
    
    size_t println(const char[]);

    char *buffer = {};
    size_t length = 0;
};

#endif /* Stream_Mock_hpp */
