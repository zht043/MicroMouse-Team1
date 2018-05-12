#ifndef __ADC_H
#define __ADC_H
#include "GPIO.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"
<<<<<<< HEAD

int addADC(uint8_t Pxx, uint8_t ADCchannel);
void initADC(ADC_TypeDef * ADCx); 
int getADCValue(int index);
int getIndexValue(void);

#endif 
=======
int addADC(uint8_t Pxx, uint8_t ADCchannel);
void initADC(ADC_TypeDef * ADCx); 
void ADC_Sampling(uint32_t *Sarr, uint8_t ch, uint32_t n);
#endif 
>>>>>>> 05d1b953cbc62c1c173e7f8b30dfeea875945d89
