#ifndef SERVODRIVERS_H
#define SERVODRIVERS_H

#include <stdint.h>
#include <Adafruit_PWMServoDriver.h>
#include "key.h"

#define SERVOMIN 100
#define SERVOMID 304
#define SERVOMAX 505

#define SERVO_CLICKING_TIME 300
#define SERVO_DONE_TIME 500
#define SERVO_SEPARATE_KEY_DELAY 100
#define SERVO_SIMULT_KEY_DELAY 1024

#define SERVO_FREQ 50

extern Adafruit_PWMServoDriver servoDriver;

void initServoDriver(Adafruit_PWMServoDriver *driver);

void servoDown(Key key);
void servoUp(Key key);

#endif