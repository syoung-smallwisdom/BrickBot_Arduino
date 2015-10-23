//
//  BrickBotVoiceBox.cpp
//  BrickBot_ArduinoLib
//
//  Created by Shannon Young on 10/22/15.
//  Copyright © 2015 Smallwisdom. All rights reserved.
//

#include "BrickBotVoiceBox.h"

void playNote(int buzzerPin, uint32_t note, unsigned long duration) {
    if (note == BBNote_None){
        noTone(buzzerPin);
        delay(duration);
    }
    else{
        //Play tone on piezo buzzer
        tone(buzzerPin, note, duration);
        delay(duration);
        //Stop tone on buzzerPin
        noTone(buzzerPin);
    }
}

BrickBotPiezoVoiceBox::BrickBotPiezoVoiceBox(int buzzerPin) {
    this->buzzerPin = buzzerPin;
}

void BrickBotPiezoVoiceBox::sayHello(){
    playNote(buzzerPin, BBNote_A7,100); //A
    playNote(buzzerPin, BBNote_G7,100); //G
    playNote(buzzerPin, BBNote_E7,100); //E
    playNote(buzzerPin, BBNote_C7,100); //C
    playNote(buzzerPin, BBNote_D7,100); //D
    playNote(buzzerPin, BBNote_B7,100); //B
    playNote(buzzerPin, BBNote_F7,100); //F
    playNote(buzzerPin, BBNote_C8,100); //C
    playNote(buzzerPin, BBNote_A7,100); //A
    playNote(buzzerPin, BBNote_G7,100); //G
    playNote(buzzerPin, BBNote_E7,100); //E
    playNote(buzzerPin, BBNote_C7,100); //C
    playNote(buzzerPin, BBNote_D7,100); //D
    playNote(buzzerPin, BBNote_B7,100); //B
    playNote(buzzerPin, BBNote_F7,100); //F
    playNote(buzzerPin, BBNote_C8,100); //C
}

void BrickBotPiezoVoiceBox::sayUhOh() {
    for (uint32_t i=BBNote_C6; i<BBNote_DS6; i=i*1.01) {
        playNote(buzzerPin, i, 30);
    }
    delay(200);
    for (uint32_t i=BBNote_DS6; i>BBNote_C6; i=i*.99) {
        playNote(buzzerPin, i, 30);
    }
}
