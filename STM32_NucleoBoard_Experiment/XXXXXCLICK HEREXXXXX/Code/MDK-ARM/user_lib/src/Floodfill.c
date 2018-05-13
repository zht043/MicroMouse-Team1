#include "Floodfill.h"

int isCentre(int x, int y){
    if(x == CENTERX1 && y == CENTERY1)
        return 1;
    if(x == CENTERX2 && y == CENTERY2)
        return 1;
    if(x == CENTERX3 && y == CENTERY3)
        return 1;
    if(x == CENTERX4 && y == CENTERY4)
        return 1;
    return 0;
}
void updatePosition(int r1, int c1, int r2, int c2){
    if(r1+1 == r2){
        // south
        direction = newCoord(1,0);
    } else if(r2+1 == r1) {
        // north
        direction = newCoord(-1,0);
    } else if(c1+1 == c2){
        // east
        direction = newCoord(0,1);
    } else{
        // west
        direction = newCoord(0,-1);
    }
}

void initFloodfill() {
    for(int i = 0; i < 100 ; i++){
        for(int j = 0; j < 100 ; j++){
            visit[i][j] = 0;
            dist[i][j] = -1;
            parentX[i][j] = -1;
            parentY[i][j] = -1;
            bestRouteX[i][j] = -1;
            bestRouteY[i][j] = -1;
        }
    }
    Qx = newStack(10000);
    Qy = newStack(10000);
		direction = newCoord(0,0);
    push(store, Qx, 0);
    push(store, Qy, 0);
    int hr = row/2;
    int cr = col/2;
    CENTERX1 = hr;
    CENTERY1 = cr;
    CENTERX2 = hr;
    CENTERY2 = cr-1;
    CENTERX3 = hr-1;
    CENTERY3 = cr;
    CENTERX4 = hr-1;
    CENTERY4 = cr-1;
}
