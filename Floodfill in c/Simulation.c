#include "Simulation.h"
#include "GridObject.h"

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
        direction -> row = 1;
        direction -> col = 0;

    } else if(r2+1 == r1) {
        // north
        direction -> row = -1;
        direction -> col = 0;

    } else if(c1+1 == c2){
        // east
        direction -> row = 0;
        direction -> col = 1;

    } else{
        // west
        direction -> row = -1;
        direction -> col = 0;
    }
}


boolean floodfill() {
    int parentX[100][100];
    int parentY[100][100];

    Stack* Qx;
    Stack* Qy;

    if(Qx.isEmpty())
        return false;

    int x = Qx.peek(), y = Qy.peek();

    printf("X = %d, Y = %d", x, y);

    int parentx = parentX[x][y];
    int parenty = parentY[x][y];

    if(isCentre(x, y)) {
        dist[x][y] = 0; visit[x][y] = true;

        updatePosition(x, y, parentX[x][y], parentY[x][y]);

        Qx.pop();
        Qy.pop();
        return true;
    }

    visit[x][y] = true;
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

        if(!grid.coordFree(new Coord(nxtX, nxtY)))
            continue;

        if(visit[nxtX][nxtY] == false){

            Qx.push(nxtX);
            Qy.push(nxtY);
            parentX[nxtX][nxtY] = x;
            parentY[nxtX][nxtY] = y;

            System.out.println("nxtX = " + nxtX + ", nxtY = " + nxtY);


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

    Qx.pop();
    Qy.pop();

    updatePosition(x, y, parentx, parenty);
    return true;
}


// void update() {
//     //printf("%d", grid.toString());
//
//     if (!floodfill()) {
//         int bestX = 0;
//         int bestY = 0;
//
//         printf("Best dist = %d", dist[0][0]);
//
//         while(!isCentre(bestX, bestY)){
//
//         //	grid.setUpColor(bestX, bestY, Color.YELLOW);
//             int nxtX, nxtY;
//             nxtX = bestRouteX[bestX][bestY];
//             nxtY = bestRouteY[bestX][bestY];
//
//             bestX = nxtX;
//             bestY = nxtY;
//             printf("BestX = %d, BestY = %d", bestX, bestY);
//
//             bestPath -> row = bestX;
//             bestPath -> col = bestY;
//
//             //grid.addPath(bp);
//             //game.addGridObject(bp);
//         }
//
//         //tt.changeState();
//         //printf("%d",grid.toString());
//
//     }
//     //game.repaint();
// }
