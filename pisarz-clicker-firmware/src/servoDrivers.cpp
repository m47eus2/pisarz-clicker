#include "servoDrivers.h"


Adafruit_PWMServoDriver servoDriver = Adafruit_PWMServoDriver();

void initServoDriver(Adafruit_PWMServoDriver *driver){
    driver->begin();
    //driver->setOscillatorFrequency(27000000);
    driver->setPWMFreq(SERVO_FREQ);

    for(uint8_t i=0; i<16; i++)
        driver->setPWM(i, 0, SERVOMID);
}

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
