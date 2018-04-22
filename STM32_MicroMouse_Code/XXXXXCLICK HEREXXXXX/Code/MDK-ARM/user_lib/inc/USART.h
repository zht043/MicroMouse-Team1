#ifndef __USART_H
#define __USART_H
#include <stdio.h>
#include <stdlib.h>
#include "GPIO.h"
#include "stm32f4xx_usart.h"
#include "misc.h"
typedef struct 
{
		USART_TypeDef* USARTx;
		uint32_t USARTx_CLK;
		uint8_t USARTx_AF;	
}USART;
void initUSART(USART_TypeDef* USARTx, uint8_t TX_Pxx, uint8_t RX_Pxx, uint32_t USARTx_BAUDRATE); 
void printfForUx(USART_TypeDef* USARTx);
void scanfForUx(USART_TypeDef* USARTx);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
void readLine(char* str);
#endif 
