#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "servoDrivers.h"
#include "key.h"
#include "clickEvent.h"

#define CLICKEVENT_TAB_MAX_LEN 50


//
// TODO
//

/*
Sterowanie serwerm przez sterownik      DONE
Odbieranie znaków przez UART            DONE
Tworzenie Key (lookup table)            DONE
Tworzenie ClickEvent                    DONE
Update loop eventów
{
Kręcenie serwerm z drivera              DONE
Funkcje servoDown, servoUp              DONE
Kolejkowanie bez nakładania
}
Nakładanie kliknięć
Kliknięcia jednoczesne
*/

//
// Event tab
//

ClickEvent clickEventTab[CLICKEVENT_TAB_MAX_LEN];
uint8_t clickEventTabLen = 0;

//
// Functions prototypes
//

void showEventTab(uint8_t n);
void receiveData();
void updateEvents();

void servoManualControll();

//
// Setup
//

void setup() {
    // Serial setup
    Serial.begin(9600);

    // Servo drivers setup
    initServoDriver(&servoDriver);

    delay(10);
}

//
// Main loop
//

void loop() {
    receiveData();
    updateEvents();
}

//
// Functions
//

void receiveData(){
    if(Serial.available() > 0){
        uint8_t incomingByte = Serial.read();
        uint8_t retCode;
        ClickEvent event = clickEvent_create(incomingByte, &retCode);
        if(retCode == 0 && clickEventTabLen < CLICKEVENT_TAB_MAX_LEN){
            clickEventTab[clickEventTabLen] = event;
            clickEventTabLen++;
        }
    }
}

void updateEvents(){
    ClickEvent prevEvent = clickEvent_createEmpty();
    unsigned long currentTime = millis();
    for(uint8_t i=0; i < clickEventTabLen; i++){
        if(clickEventTab[i].state != EMPTY){
            clickEvent_update(&(clickEventTab[i]), prevEvent, currentTime);
            prevEvent = clickEventTab[i];
        }
    }

    if(clickEventTabLen)
        showEventTab(clickEventTabLen);

    if(clickEventTab[0].state == DONE){
        for(uint8_t i=0; i < clickEventTabLen-1; i++){ // BUG WAS HERE (clickEventTabLen-2)
            clickEventTab[i] = clickEventTab[i+1];
        }
        clickEventTab[clickEventTabLen-1] = clickEvent_createEmpty();
        clickEventTabLen--;
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

void servoManualControll(){
    static uint16_t manualValue = SERVOMID;
    if(Serial.available() > 0){
        uint8_t incomingByte = Serial.read();
        if(incomingByte == 'w') manualValue++;
        else if(incomingByte == 's') manualValue--;
    }
    Serial.println(manualValue);
    servoDriver.setPWM(8, 0, manualValue);
}