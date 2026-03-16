#include "servoDrivers.h"

Adafruit_PWMServoDriver servoDriver = Adafruit_PWMServoDriver();

void servoDown(Key key){
    uint16_t position;
    if(key.dir == LEFT)
        position = SERVOMIN;
    else
        position = SERVOMAX;
    
    key.driver->setPWM(key.channel, 0, position);
}

void servoUp(Key key){
    key.driver->setPWM(key.channel, 0, SERVOMID);
}