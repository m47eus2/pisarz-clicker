#ifndef SERVODRIVERS_H
#define SERVODRIVERS_H

#include <Adafruit_PWMServoDriver.h>
#include "key.h"

extern Adafruit_PWMServoDriver servoDriver;

void servoDown(Key key);
void servoUp(Key key);

#endif