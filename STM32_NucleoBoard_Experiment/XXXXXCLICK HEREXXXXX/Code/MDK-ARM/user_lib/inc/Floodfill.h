#ifndef __FLOODFILL_H
#define __FLOODFILL_H
#include <stdio.h>
#include <stdlib.h>
#include "GPIO.h"
#include "stm32f4xx_usart.h"
#include "misc.h"
#include "Stack.h"
#include "Coord.h"
#include <limits.h>

void initFloodfill(void);
bool isCenter(int x, int y);
void updatePosition(int r1, int c1, int r2, int c2);
bool floodfill(void);
void driver(Stack * stack);
bool Occupy(int row, int col);
bool withinBounds(int x, int y);


#endif
