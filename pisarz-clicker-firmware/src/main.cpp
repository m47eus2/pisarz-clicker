#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "servoDrivers.h"
#include "key.h"
#include "clickEvent.h"

#define EVENTTABMAXLEN 50

#define SERVOMIN  120
#define SERVOMAX  520
#define SERVO_FREQ 50

//
// TODO
//

/*
Sterowanie serwerm przez sterownik      DONE
Odbieranie znaków przez UART            DONE
Tworzenie Key (lookup table)            DONE
Tworzenie ClickEvent                    DONE
Update loop eventów
Nakładanie kliknięć
Kliknięcia jednoczesne
*/

//
// Event tab
//

ClickEvent clickEventTab[EVENTTABMAXLEN];
uint8_t clickEventTabLen = 0;

//
// Functions prototypes
//

void showEventTab(uint8_t n);
void receiveData();
void updateEvents();

//
// Setup
//

void setup() {
    // Serial setup
    Serial.begin(9600);

    // Servo drivers setup
    servoDriver.begin();
    servoDriver.setOscillatorFrequency(27000000);
    servoDriver.setPWMFreq(SERVO_FREQ);

    delay(10);
}

//
// Main loop
//

void loop() {
    // servoDriver.setPWM(servonum, 0, SERVOMIN);
    // delay(1000);
    // servoDriver.setPWM(servonum, 0, SERVOMAX);
    // delay(1000);

    receiveData();
    showEventTab(5);

    delay(500);
}

//
// Functions
//

void receiveData(){
    if(Serial.available() > 0){
        uint8_t incomingByte = Serial.read();
        uint8_t retCode;
        ClickEvent event = clickEvent_create(incomingByte, millis(), &retCode);
        if(retCode == 0 && clickEventTabLen < EVENTTABMAXLEN){
            clickEventTab[clickEventTabLen] = event;
            clickEventTabLen++;
        }
    }
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