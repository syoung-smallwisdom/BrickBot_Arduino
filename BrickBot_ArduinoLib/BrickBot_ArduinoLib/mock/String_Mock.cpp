//
//  String_Mock.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/22/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "String_Mock.hpp"

String::String(const char *cstr)
{
    this->buffer = cstr;
}

String::String(const String &value)
{
    *this = value;
}

unsigned char String::concat(char c)
{
    return 1;
}