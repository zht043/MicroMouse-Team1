#ifndef __PID_H
#define __PID_H

#include "GPIO.h"
#include "IR.h"
#include "Timer.h"
#include "SysTime.h"
#include "Motor.h"

double convertToAngle(double diff);
void gS_Tester(double speed) ;
double convertToCM(double cnt);
void LspeedTester(void);
void RspeedTester(void);


#endif
