#ifndef __LED_H
#define __LED_H

#include "GPIO.h"
#include "SysTime.h"

void initLED(void);
void L_LED_ON(void);
void L_LED_OFF(void);
void R_LED_ON(void);
void R_LED_OFF(void);
void blinkLED(uint8_t numBlinks);
#endif 
