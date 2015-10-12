//
//  Stream_Mock.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/8/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "Stream_Mock.hpp"

size_t Stream::readBytes( char *buffer, size_t length) {
    
    size_t len = (this->length < length) ? this->length : length;
    memcpy(buffer, this->buffer, len);
    return this->length;
}

size_t Stream::write(const uint8_t *buffer, size_t size) {
    for (int ii=0; ii < size; ii++) {
        std::cout << (int)buffer[ii] << " ";
    }
    std::cout << "\n";
    return 1;
}