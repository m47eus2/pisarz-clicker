#ifndef LUT_H
#define LUT_H

#include <stdint.h>
#include <Adafruit_PWMServoDriver.h>

extern Adafruit_PWMServoDriver servoDriver;

uint8_t getServoChannelFromLUT(uint8_t character, uint8_t *returnCode);
// Adafruit_PWMServoDriver *getServoDriverFromLUT(uint8_t character, uint8_t *returnCode);


#endif