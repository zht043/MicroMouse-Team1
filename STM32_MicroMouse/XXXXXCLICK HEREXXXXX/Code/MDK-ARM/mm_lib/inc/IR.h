#ifndef __IR_H
#define __IR_H
#include "GPIO.h"
#include "SysTime.h"
#include "ADC.h"
#include "USART.h"
#include "Timer.h"
#define num_samples_IR  10 // number of samples to average over for readings
#define Impulse_period 1
void initIR(void);
void IR_Tester(void);
uint16_t parse_ADC_Sample(uint16_t Sarr[], uint32_t n);
void TIM3_itTask_cc1(void);


#endif
