#ifndef __Motor_H
#define __Motor_H

#include "Timer.h"
#include "GPIO.h"
#include "SysTime.h"

void initMotor(void);
void motor(double Lpwr, double Rpwr);
void motorTester(void);
void halt(void);
void curve(double v, double w);

#endif 

