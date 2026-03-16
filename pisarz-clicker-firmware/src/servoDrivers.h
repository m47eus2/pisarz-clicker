#ifndef SERVODRIVERS_H
#define SERVODRIVERS_H

#include <Adafruit_PWMServoDriver.h>
#include "key.h"

#define SERVOMIN 120
#define SERVOMAX 520
#define SERVOMID 320
#define SERVO_FREQ 50

extern Adafruit_PWMServoDriver servoDriver;

void servoDown(Key key);
void servoUp(Key key);

#endif