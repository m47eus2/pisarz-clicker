#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "servoDrivers.h"
#include "clickEventTab.h"
#include "parser.h"


//
// TODO
//

/*
Sterowanie serwerm przez sterownik      DONE
Odbieranie znaków przez UART            DONE
Tworzenie Key (lookup table)            DONE
Tworzenie ClickEvent                    DONE
Kręcenie serwerm z drivera              DONE
Funkcje servoDown, servoUp              DONE
Kolejkowanie bez nakładania             DONE
Nakładanie kliknięć                     DONE
Duże litery (shift)                     DONE
Polskie znaki dwu-bajtowe (alt)         DONE
Fast typing                             DONE
Dwa znaki po sobie na jednym serwie     DONE
PICP Parser
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
    Serial.begin(115200);
    initServoDrivers();
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
        parser_readByte(incomingByte);
    }
}

//
// DEBUG
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