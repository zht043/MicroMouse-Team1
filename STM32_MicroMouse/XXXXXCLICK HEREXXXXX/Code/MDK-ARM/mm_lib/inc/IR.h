#ifndef __IR_H
#define __IR_H
#include "GPIO.h"
#include "SysTime.h"
#include "ADC.h"
#include "USART.h"
#include "Timer.h"
#define num_samples_IR  1 // number of samples to average over for readings
#define Impulse_period 50

#define IRv_L   IR_values[0]
#define IRv_LFA IR_values[1]
#define IRv_LFB IR_values[2]
#define IRv_RFB IR_values[3]
#define IRv_RFA IR_values[4]
#define IRv_R   IR_values[5]

void initIR(void);
void IR_Tester(void);
uint16_t parse_ADC_Sample(uint16_t Sarr[], uint32_t n);
void TIM3_itTask_cc1(void);


#endif
