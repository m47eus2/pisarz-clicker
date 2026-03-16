#ifndef SERVODRIVERS_H
#define SERVODRIVERS_H

#include <Adafruit_PWMServoDriver.h>
#include "key.h"

#define SERVOMIN 120
#define SERVOMAX 520
#define SERVOMID 320

#define SERVO_CLICKING_TIME 1024
#define SERVO_RETURNING_TIME 1024
#define SERVO_SEPARATE_KEY_DELAY 1024
#define SERVO_SIMULT_KEY_DELAY 1024

#define SERVO_FREQ 50

extern Adafruit_PWMServoDriver servoDriver;

void servoDown(Key key);
void servoUp(Key key);

#endif