#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "servoDrivers.h"
#include "key.h"
#include "clickEvent.h"
#include "clickEventTab.h"


//
// TODO
//

/*
Sterowanie serwerm przez sterownik      DONE
Odbieranie znaków przez UART            DONE
Tworzenie Key (lookup table)            DONE
Tworzenie ClickEvent                    DONE

Update loop eventów:
Kręcenie serwerm z drivera              DONE
Funkcje servoDown, servoUp              DONE
Kolejkowanie bez nakładania             DONE
Nakładanie kliknięć                     DONE

Znaki dwu-klawiszowe:
Duże litery (shift)
Polskie znaki dwu-bajtowe (alt)
PICP (Pisarz-Internal-Communication-Protocol) Parser

Fast typing:
Któtki delay pomiędzy przyciśnięciami
Przed każdym rozpoczęciem clicking sprawdzanie czy nie istnieje event
z takim samym key w stanie clicking albo returning
*/

//
// Functions prototypes
//

void receiveData();
void servoManualControll();

//
// Setup
//

void setup() {
    // Serial setup
    Serial.begin(115200);

    // Servo drivers setup
    initServoDriver(&servoDriver);

    delay(10);
}

//
// Main loop
//

void loop() {
    receiveData();
    clickEventTab_updateEvents();
    //clickEventTab_showEventTab();
    clickEventTab_removeDoneEvents();
}

//
// Functions
//

void receiveData(){
    while(Serial.available() > 0){
        uint8_t incomingByte = Serial.read();
        uint8_t retCode;
        ClickEvent event = clickEvent_create(incomingByte, &retCode);
        if(retCode == 0)
            clickEventTab_addEvent(event);
    }
}

//
// DEBUGGING
//

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