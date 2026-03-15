#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "key.h"
#include "clickEvent.h"

#define SERVOMIN  120
#define SERVOMAX  520
#define SERVO_FREQ 50

//
// TODO
//

/*
Sterowanie serwerm przez sterownik      DONE
Odbieranie znaków przez UART            DONE
Tworzenie Key (lookup table)
Tworzenie ClickEvent
Update loop eventów
Nakładanie kliknięć
Kliknięcia jednoczesne
*/

//
// Drivers objects
//

Adafruit_PWMServoDriver servoDriver = Adafruit_PWMServoDriver();

//
// Data types
//

ClickEvent clickEventTab[50];
uint8_t clickEventTabLen = 0;

//
// Functions
//

void showEventTab(uint8_t n);
void receiveData();
void updateEvents();

void servoDown(Key key);
void servoUp(Key key);


uint8_t servonum = 7;

void setup() {
    // Serial setup
    Serial.begin(9600);
    Serial.println("8 channel Servo test!");

    // Servo drivers setup
    servoDriver.begin();
    servoDriver.setOscillatorFrequency(27000000);
    servoDriver.setPWMFreq(SERVO_FREQ);

    delay(10);
}

void loop() {
    // servoDriver.setPWM(servonum, 0, SERVOMIN);

    // delay(1000);
  
    // servoDriver.setPWM(servonum, 0, SERVOMAX);

    // delay(1000);

    receiveData();
    
    // for(int i=0; i<10; i++)
    //     Serial.print(clickEventTab[i].key.channel);
    //Serial.println();

    showEventTab(5);

    delay(500);
}

void showEventTab(uint8_t n){
    Serial.println("=== === Event Tab === ===");
    for(int i=0; i < n; i++){
        Serial.print("Idx: ");
        Serial.print(i);
        Serial.print("   state: ");
        Serial.print(clickEventTab[i].state);
        Serial.print("   driver: ");
        Serial.print((uintptr_t)clickEventTab[i].key.driver, HEX);
        Serial.print("   key.channel: ");
        Serial.print(clickEventTab[i].key.channel);
        Serial.print("   key.dir: ");
        Serial.println(clickEventTab[i].key.dir);
    }
    Serial.println();
}

void receiveData(){
    if(Serial.available() > 0){
        uint8_t incomingByte = Serial.read();

        Serial.print("Received: ");
        Serial.println(incomingByte, DEC);

        uint8_t retCode;
        ClickEvent event = clickEvent_create(incomingByte, millis(), &retCode);
        if(retCode == 0){
            clickEventTab[clickEventTabLen] = event;
            clickEventTabLen++;
        }
    }
}

