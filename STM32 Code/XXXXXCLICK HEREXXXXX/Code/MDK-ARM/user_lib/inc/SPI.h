#ifndef __SPI_H
#define __SPI_H
#include "GPIO.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_dma.h"
void SPI_init(void);
uint8_t SPI_FLASH_SendByte(uint8_t byte);
uint8_t SPI_FLASH_ReadByte(void);
#endif 
