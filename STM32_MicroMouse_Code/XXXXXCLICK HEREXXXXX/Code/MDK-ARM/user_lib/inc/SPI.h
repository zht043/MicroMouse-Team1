#ifndef __SPI_H
#define __SPI_H
#include "GPIO.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_dma.h"
void SPI1_init(void);
uint8_t SPI_SendByte(uint8_t byte, SPI_TypeDef * SPIx);
uint8_t SPI_ReadByte(SPI_TypeDef * SPIx);
void SPI2_init(void);
#endif 
