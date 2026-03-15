#ifndef LUT_H
#define LUT_H

#include <stdint.h>
#include <Adafruit_PWMServoDriver.h>
#include "key.h"


const uint8_t getServoChannelFromLUT(uint8_t character, uint8_t *returnCode);
const Adafruit_PWMServoDriver *getServoDriverFromLUT(uint8_t character, uint8_t *returnCode);
const servoDir getServoDirFromLUT(uint8_t character, uint8_t *returnCode);


#endif