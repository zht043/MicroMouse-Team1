#ifndef __FLOODFILL_H
#define __FLOODFILL_H
#include <stdio.h>
#include <stdlib.h>
#include "GPIO.h"
#include "stm32f4xx_usart.h"
#include "misc.h"
#include "Stack.h"
typedef enum {false, true} bool;
void initFloodfill(void);
int isCenter(int x, int y);
void updatePostition(int r1, int c1, int r2, int c2);
bool floodfill(void);
#endif 
