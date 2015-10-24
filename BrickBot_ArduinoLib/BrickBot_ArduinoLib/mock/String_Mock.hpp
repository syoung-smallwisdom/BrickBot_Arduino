//
//  String_Mock.hpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/22/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#ifndef String_Mock_hpp
#define String_Mock_hpp

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// The string class
class String
{
    
public:
    String(const char *cstr = "");
    String(const String &str);
    
    unsigned char concat(char c);
    String & operator += (char c)			{concat(c); return (*this);}
    
    const char *buffer;	        // the actual char array
};


#endif /* String_Mock_hpp */
