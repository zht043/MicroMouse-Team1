#ifndef __Timer_H
#define __Timer_H

#include "GPIO.h"
typedef struct 
{
    uint8_t Pxx;
	  uint16_t Ch;
		uint8_t TIMERx;
}TIM;
void initTimer_PWM_OUTPUT(uint8_t, uint16_t, uint32_t);
void PWM_OUT(TIM port, uint32_t dutyCircle);
TIM initIO_TIM(uint8_t, uint8_t);


#define Ch1       1
#define Ch2      10
#define Ch3     100
#define Ch4    1000

#define TIMER1 0x01
#define TIMER2 0x02
#define TIMER3 0x03
#define TIMER4 0x04
#define TIMER5 0x05
#define TIMER8 0x08
#define TIMER9 0x09
#define TIMER10 0x0A
#define TIMER11 0x0B
#define TIMER12 0x0C
#define TIMER13 0x0D
#define TIMER14 0x0E
#define TIMER15 0x0F

#endif 
