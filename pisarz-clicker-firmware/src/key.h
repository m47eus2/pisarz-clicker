#ifndef KEY_H
#define KEY_H

#include <stdint.h>
#include <Adafruit_PWMServoDriver.h>

#define SHIFT_CODE 10
#define ALT_CODE 11

typedef enum{
    LEFT,
    RIGHT
} servoDir;

typedef struct{
    Adafruit_PWMServoDriver *driver;
    uint8_t channel;
    servoDir dir;
} Key;

Key key_create(uint8_t character, uint8_t *returnCode);
Key key_createEmpty();
uint8_t key_checkServoEqual(Key keya, Key keyb);

#endif