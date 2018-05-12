#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <Coord.h>

Coord* newCoord(int x, int y){
	Coord* coord = (Coord*) malloc(sizeof(Coord));;
	coord -> row = x;
    coord -> col = y;
	return coord;
}
