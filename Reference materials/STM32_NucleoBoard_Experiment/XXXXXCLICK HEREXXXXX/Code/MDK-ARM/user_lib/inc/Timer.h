#ifndef __Timer_H

#define __Timer_H



#include "GPIO.h"
#include "misc.h"

typedef struct 

{

    uint8_t Pxx;

	  uint16_t Ch;

		uint8_t TIMERx;

}TIM;

void PWM_ON(uint8_t TIMERx, uint32_t Frequency);

void setPWM(TIM port, uint32_t dutyCircle);

void TIM3_IR_IT(void);

uint16_t usToCCR(uint16_t us, uint32_t Freq);

TIM initIO_TIM(uint8_t TIMERx, uint8_t Pxx, uint16_t ch);

void initEncoder(void);

void ResetREnc(void);

void ResetLEnc(void);

void ResetEnc(void);

int32_t REnc(void);

int32_t LEnc(void);



#define Ch1       1

#define Ch2      10

#define Ch3     100

#define Ch4    1000



#define TIMER1    1

#define TIMER2    2

#define TIMER3    3

#define TIMER4    4

#define TIMER5    5

#define TIMER8    8

#define TIMER9    9

#define TIMER10   10

#define TIMER11   11

#define TIMER12 	12

#define TIMER13 	13

#define TIMER14 	14

#define TIMER15 	15



#endif 
