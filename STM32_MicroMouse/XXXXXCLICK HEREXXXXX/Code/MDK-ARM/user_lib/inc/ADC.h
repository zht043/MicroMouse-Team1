#ifndef __ADC_H
#define __ADC_H
#include "GPIO.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"
int addADC(uint8_t Pxx, uint8_t ADCchannel);
void initADC(ADC_TypeDef * ADCx); 
void ADC_Sampling(uint16_t Sarr[], uint8_t ch, uint32_t n);
uint16_t analogRead(uint8_t ch);
#endif 
