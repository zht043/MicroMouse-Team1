#ifndef __COORD_H
#define __COORD_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Coord{
    int row;
    int col;
}Coord;

Coord * newCoord(int x, int y);

#endif
