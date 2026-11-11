#include "pca9685.h"

#define PCA9685_MODE1       0x00
#define PCA9685_MODE2       0x01
#define PCA9685_PRESCALE    0xFE
#define PCA9685_LED0_ON_L   0x06

#define PCA9685_TIMEOUT     100

typedef struct
{
    I2C_HandleTypeDef *i2cHandler;
    uint16_t pca9685Address;

} pca9685_type;

static pca9685_type pca9685_handler;

void pca9685_WriteRegister(uint8_t reg, uint8_t data)
{
    uint8_t buffer[2] = {reg, data};

    HAL_I2C_Master_Transmit(
        pca9685_handler.i2cHandler,
        pca9685_handler.pca9685Address,
        buffer,
        2,
        PCA9685_TIMEOUT
    );
}

uint8_t pca9685_ReadRegister(uint8_t reg)
{
    uint8_t data = 0;

    HAL_I2C_Mem_Read(
        pca9685_handler.i2cHandler,
        pca9685_handler.pca9685Address,
        reg,
        I2C_MEMADD_SIZE_8BIT,
        &data,
        1,
        PCA9685_TIMEOUT
    );

    return data;
}

void pca9685_SetFreq50Hz(void)
{
    uint8_t oldmode;
    uint8_t sleep;

    oldmode = pca9685_ReadRegister(PCA9685_MODE1);
    sleep = (oldmode & 0x7F) | 0x10;
    pca9685_WriteRegister(PCA9685_MODE1, sleep);
    pca9685_WriteRegister(PCA9685_PRESCALE, 128); // default 121
    pca9685_WriteRegister(PCA9685_MODE1, oldmode);

    HAL_Delay(5);

    pca9685_WriteRegister(PCA9685_MODE1, oldmode | 0x80);
}

void pca9685_Init(I2C_HandleTypeDef *handler, uint8_t address)
{
    pca9685_handler.i2cHandler = handler;
    pca9685_handler.pca9685Address = address << 1;

    pca9685_WriteRegister(PCA9685_MODE1, 0x20);

    HAL_Delay(10);

    pca9685_WriteRegister(PCA9685_MODE2, 0x04);
    pca9685_SetFreq50Hz();
}

void pca9685_SetPwm(uint8_t channel, uint16_t on, uint16_t off)
{
    if (channel > 15)
        return;

    uint8_t reg = PCA9685_LED0_ON_L + (4 * channel);

    uint8_t buffer[4] =
    {
        on & 0xFF,
        (on >> 8) & 0x0F,
        off & 0xFF,
        (off >> 8) & 0x0F
    };

    HAL_I2C_Mem_Write(
        pca9685_handler.i2cHandler,
        pca9685_handler.pca9685Address,
        reg,
        I2C_MEMADD_SIZE_8BIT,
        buffer,
        4,
        PCA9685_TIMEOUT
    );
}

void pca9685_SetServoAngle(uint8_t channel, float angle)
{
    if (channel > 15)
        return;

    if (angle < 0.0f)
        angle = 0.0f;

    if (angle > 180.0f)
        angle = 180.0f;

    uint16_t minPulse = 205; // 1 ms
    uint16_t maxPulse = 410; // 2 ms

    uint16_t pulse = minPulse + (uint16_t)((angle / 180.0f) * (maxPulse - minPulse));

    pca9685_SetPwm(channel, 0, pulse);
}