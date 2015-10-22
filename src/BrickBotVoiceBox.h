//
//  BrickBotVoiceBoxhpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on = 10/22/15
//  Copyright © = 2015 Smallwisdom All rights reserved
//

#ifndef BrickBotVoiceBox_hpp
#define BrickBotVoiceBox_hpp

#include "BrickBotArduino.h"

class BrickBotVoiceBoxProtocol
{
public:
    virtual void sayHello() {};
    virtual void sayUhOh() {};
};

class BrickBotPiezoVoiceBox: public BrickBotVoiceBoxProtocol
{
public:
    BrickBotPiezoVoiceBox(int buzzerPin);
    
    void sayHello();
    void sayUhOh();
    
protected:
    int buzzerPin;
};

#ifdef __cplusplus
extern "C"{
#endif
    
    void playNote(int buzzerPin, uint32_t note, unsigned long duration);
    
#ifdef __cplusplus
} // extern "C"
#endif

enum BBNote: uint32_t {
    BBNote_None = 0,
    BBNote_B0  = 31,
    BBNote_C1  = 33,
    BBNote_CS1 = 35,
    BBNote_D1  = 37,
    BBNote_DS1 = 39,
    BBNote_E1  = 41,
    BBNote_F1  = 44,
    BBNote_FS1 = 46,
    BBNote_G1  = 49,
    BBNote_GS1 = 52,
    BBNote_A1  = 55,
    BBNote_AS1 = 58,
    BBNote_B1  = 62,
    BBNote_C2  = 65,
    BBNote_CS2 = 69,
    BBNote_D2  = 73,
    BBNote_DS2 = 78,
    BBNote_E2  = 82,
    BBNote_F2  = 87,
    BBNote_FS2 = 93,
    BBNote_G2  = 98,
    BBNote_GS2 = 104,
    BBNote_A2  = 110,
    BBNote_AS2 = 117,
    BBNote_B2  = 123,
    BBNote_C3  = 131,
    BBNote_CS3 = 139,
    BBNote_D3  = 147,
    BBNote_DS3 = 156,
    BBNote_E3  = 165,
    BBNote_F3  = 175,
    BBNote_FS3 = 185,
    BBNote_G3  = 196,
    BBNote_GS3 = 208,
    BBNote_A3  = 220,
    BBNote_AS3 = 233,
    BBNote_B3  = 247,
    BBNote_C4  = 262,
    BBNote_CS4 = 277,
    BBNote_D4  = 294,
    BBNote_DS4 = 311,
    BBNote_E4  = 330,
    BBNote_F4  = 349,
    BBNote_FS4 = 370,
    BBNote_G4  = 392,
    BBNote_GS4 = 415,
    BBNote_A4  = 440,
    BBNote_AS4 = 466,
    BBNote_B4  = 494,
    BBNote_C5  = 523,
    BBNote_CS5 = 554,
    BBNote_D5  = 587,
    BBNote_DS5 = 622,
    BBNote_E5  = 659,
    BBNote_F5  = 698,
    BBNote_FS5 = 740,
    BBNote_G5  = 784,
    BBNote_GS5 = 831,
    BBNote_A5  = 880,
    BBNote_AS5 = 932,
    BBNote_B5  = 988,
    BBNote_C6  = 1047,
    BBNote_CS6 = 1109,
    BBNote_D6  = 1175,
    BBNote_DS6 = 1245,
    BBNote_E6  = 1319,
    BBNote_F6  = 1397,
    BBNote_FS6 = 1480,
    BBNote_G6  = 1568,
    BBNote_GS6 = 1661,
    BBNote_A6  = 1760,
    BBNote_AS6 = 1865,
    BBNote_B6  = 1976,
    BBNote_C7  = 2093,
    BBNote_CS7 = 2217,
    BBNote_D7  = 2349,
    BBNote_DS7 = 2489,
    BBNote_E7  = 2637,
    BBNote_F7  = 2794,
    BBNote_FS7 = 2960,
    BBNote_G7  = 3136,
    BBNote_GS7 = 3322,
    BBNote_A7  = 3520,
    BBNote_AS7 = 3729,
    BBNote_B7  = 3951,
    BBNote_C8  = 4186,
    BBNote_CS8 = 4435,
    BBNote_D8  = 4699,
    BBNote_DS8 = 4978,
};

#endif /* BrickBotVoiceBox_hpp */
