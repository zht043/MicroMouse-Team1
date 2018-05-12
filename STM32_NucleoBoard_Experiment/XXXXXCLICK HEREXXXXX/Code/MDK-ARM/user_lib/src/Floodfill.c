#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
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


bool floodfill() {

    if(Qx->isEmpty())
        return false;

    int x = Qx->peek();
    int y = Qy->peek();

    printf("X = %d, Y = %d", x, y);

    int parentx = parentX[x][y];
    int parenty = parentY[x][y];

    if(isCentre(x, y)) {
        dist[x][y] = 0;
        visit[x][y] = 1;

        updatePosition(x, y, parentX[x][y], parentY[x][y]);

        Qx->pop();
        Qy->pop();
        return true;
    }

    visit[x][y] = 1;
    if(parentx != -1 && parenty != -1){

        if(dist[parentx][parenty] != -1){
            bestRouteX[x][y] = parentx;
            bestRouteY[x][y] =  parenty;
            dist[x][y] = dist[parentx][parenty]+1;
        }
    }


    for(int i = 0 ; i < 4 ; i++){
        int nxtX = x+xx[i];
        int nxtY = y+yy[i];

        //if(!grid.coordFree(new Coord(nxtX, nxtY)))
        //              continue;

        if(visit[nxtX][nxtY] == 0){

            Qx->push(nxtX);
            Qy->push(nxtY);
            parentX[nxtX][nxtY] = x;
            parentY[nxtX][nxtY] = y;

            //System.out.println("nxtX = " + nxtX + ", nxtY = " + nxtY);


            updatePosition(x, y, nxtX, nxtY);

            return true;
        }

        // Even if we have visited our neighbour, it could be the case that he has the shortest path!
        if(dist[nxtX][nxtY] != -1){ // Can our neighbour reach center?
            if(dist[x][y] == -1){ // Can we reach center?

                bestRouteX[x][y] = nxtX;
                bestRouteY[x][y] = nxtY;
                dist[x][y] = dist[nxtX][nxtY]+1;
            }
            else{
                if(dist[nxtX][nxtY]+1 < dist[x][y]){ // Can our neighbour reach the center faster?

                    bestRouteX[x][y] = nxtX;
                    bestRouteY[x][y] = nxtY;
                    dist[x][y] = dist[nxtX][nxtY]+1;
                }
            }
        }
    }

    Qx->pop();
    Qy->pop();

    updatePosition(x, y, parentx, parenty);
    return true;
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

    //Qx ->init();
    //Qy ->init();

    Qx->push(0);
    Qy->push(0);

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
