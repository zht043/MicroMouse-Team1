#ifndef __SysTime_H
#define __SysTime_H

#include "stm32f4xx.h"

void SysTick_Init(uint32_t); 
void SysTick_Increment(void);
uint32_t millis(void);
uint32_t micros(void);
void delay_us(uint32_t);
void delay(uint32_t); 

#endif
