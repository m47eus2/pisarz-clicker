#include "lut.h"

uint8_t servoChannelLUT[256];

void servoChannelLUTInit(){
    servoChannelLUT['a'] = 8;
    servoChannelLUT['b'] = 9;
}