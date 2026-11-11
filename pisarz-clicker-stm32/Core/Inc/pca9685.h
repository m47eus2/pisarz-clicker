#ifndef PCA9685_H
#define PCA9685_H

#include <stdint.h>
#include "i2c.h"

void pca9685_WriteRegister(uint8_t reg, uint8_t data);
uint8_t pca9685_ReadRegister(uint8_t reg);

void pca9685_Init(I2C_HandleTypeDef *handler, uint8_t address);
void pca9685_SetFreq50Hz(void);

void pca9685_SetPwm(uint8_t channel, uint16_t on, uint16_t off);
void pca9685_SetServoAngle(uint8_t channel, float angle);

#endif