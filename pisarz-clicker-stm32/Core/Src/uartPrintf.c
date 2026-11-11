#include "uartPrintf.h"
#include "usart.h"
#include <stdint.h>

int __io_putchar(int ch){
    if (ch == '\n'){
        uint8_t ch2 = '\r';
        HAL_UART_Transmit(&huart3, &ch2, 1, HAL_MAX_DELAY);
    }

    HAL_UART_Transmit(&huart3, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return 1;
}