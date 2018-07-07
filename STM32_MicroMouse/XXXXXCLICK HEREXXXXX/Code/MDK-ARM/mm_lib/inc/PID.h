#ifndef __PID_H
#define __PID_H

#include "GPIO.h"
#include "IR.h"
#include "Timer.h"
#include "SysTime.h"
#include "Motor.h"
#include "Led.h"
#include "Stack.h"
#include "Floodfill.h"


int canMoveRight();
int canMoveLeft();
int canMoveForward();
void turnRight();
void turnLeft();
void turnForward();
void turnBackX();
double convertToAngle(double diff);
void gS_Tester(double speed) ;
double convertToCM(double cnt);
void LspeedTester(void);
void RspeedTester(void);
double IR_ErrGen(void);
void TurnLeft(void);
void halt(double bufferRange);
void goStraight(double speed);
void luckyGO(void);
void tUC(void);


#endif
