#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

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

typedef struct{
    uint8_t driver;
    uint8_t channel;
    uint8_t dir;
} Key;

typedef enum{
    BORN,
    CLICKING,
    RETURNING,
    DONE
} clickEventState;

typedef struct{
    Key key;
    unsigned long bornTime;
    clickEventState state;

} ClickEvent;


ClickEvent clickEventTab[100];
uint8_t clickEventTabLen = 0;

//
// Functions
//

void receiveData();
void updateEvents();

ClickEvent clickEvent_create(uint16_t key, unsigned long time, uint8_t *returnCode);
void clickEvent_update(ClickEvent *event, unsigned long time);
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
    for(int i=0; i<5; i++)
        Serial.print(clickEventTab[i].key.channel);
    Serial.println();
    delay(500);
}

ClickEvent clickEvent_create(uint16_t character, unsigned long time, uint8_t *returnCode){
    Key key;
    *returnCode = 1;
    if(character == 'a'){
        key.driver = 0;
        key.channel = 7;
        key.dir = 0;
        *returnCode = 0;
    }
    else{
        key.driver = 0;
        key.channel = 0;
        key.dir = 0;
    }

    ClickEvent event;
    event.key = key;
    event.bornTime = time;
    event.state = BORN;

    return event;
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