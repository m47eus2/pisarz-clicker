#ifndef KEY_H
#define KEY_H

#include <stdint.h>
#include <Adafruit_PWMServoDriver.h>

typedef enum{
    LEFT,
    RIGHT
} servoDir;

typedef struct{
    Adafruit_PWMServoDriver *driver;
    uint8_t channel;
    servoDir dir;
} Key;

Key key_create(uint16_t character, uint8_t *returnCode);
Key key_createEmpty();

#endif