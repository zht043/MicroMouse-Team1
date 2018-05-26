#include "Floodfill.h"
static int storex[MAX];
static int storey[MAX];

bool grid[16][16];
//Coord* direction;
int xx[] = {0,1,0,-1};
int yy[] = {1,0,-1,0};
bool visit[16][16];
int dist[16][16];
int bestRouteX[16][16];
int bestRouteY[16][16];
int parentX[16][16];
int parentY[16][16];
Stack* Qx;
Stack* Qy;
int row = 16;
int col = 16;
int CENTERX1;
int CENTERY1;
int CENTERX2;
int CENTERY2;
int CENTERX3;
int CENTERY3;
int CENTERX4;
int CENTERY4;

enum dirArr {MIDDLE, NORTH, SOUTH, EAST, WEST};
enum dirArr direction;


bool floodfill(){
	  if(isEmpty(storex, Qx)){
		  return false;
  	}

    int x = peek(storex, Qx);
    int y = peek(storey, Qy);
    printf("\rX = %d, Y = %d\r\n", x, y);
    int parentx = parentX[x][y];
    int parenty = parentY[x][y];
    if(isCenter(x, y)) {
        dist[x][y] = 0;
        visit[x][y] = true;
        updatePosition(x, y, parentX[x][y], parentY[x][y]);
        pop(storex, Qx);
        pop(storey, Qy);
			
		/*		for (int i = 0; i < 16; i++) {
					for (int j = 0; j < 16; j++){
						
						printf("%d", bestRouteX[i][j]);
					}
					printf("\n");
				}*/
	 printf("Check point 1\n");
        return true;
    }
    visit[x][y] = true;
    if(parentx != -1 && parenty != -1){
        if(dist[parentx][parenty] != -1){
            bestRouteX[x][y] = parentx;
            bestRouteY[x][y] =  parenty;
            dist[x][y] = dist[parentx][parenty]+1;
					  printf("Check point 2\n");
						printf("bestRoute %d,%d\n", parentx, parenty);
        }
    }
    for(int i = 0 ; i < 4 ; i++){
        int nxtX = x+xx[i];
        int nxtY = y+yy[i];
			  printf("\rnxtX = %d, nxtY = %d\n\r",  nxtX , nxtY);

				// grid[i][j] abstractly represents if the nextx, nexty
			  // is reachable for current x, current y
        if(!withinBounds(nxtX, nxtY) || grid[nxtX][nxtY] ){
           continue;
		    }
				
        if(visit[nxtX][nxtY] == false){
            push(storex, Qx, nxtX);
            push(storey, Qy, nxtY);
            parentX[nxtX][nxtY] = x;
            parentY[nxtX][nxtY] = y;
            updatePosition(x, y, nxtX, nxtY);
            return true;
        }
				
        // Even if we have visited our neighbour, it could be the case that he has the shortest path!
        if(dist[nxtX][nxtY] != -1){ // Can our neighbour reach center?
            if(dist[x][y] == -1){ // Can we reach center?
                bestRouteX[x][y] = nxtX;
                bestRouteY[x][y] = nxtY;
                dist[x][y] = dist[nxtX][nxtY]+1;
							  printf("Check point 3\n");
            }
            else{
                if(dist[nxtX][nxtY]+1 < dist[x][y]){ // Can our neighbour reach the center faster?
                    bestRouteX[x][y] = nxtX;
                    bestRouteY[x][y] = nxtY;
                    dist[x][y] = dist[nxtX][nxtY]+1;
									  printf("Check point 4\n");
                }
            }
        }
    }
    pop(storex, Qx);
    pop(storey, Qy);
    updatePosition(x, y, parentx, parenty);
		return true;
}

bool withinBounds(int x, int y) {
	if(x < 0 || x >= 16 || y < 0 || y >= 16) return false;
	return true;
}

bool isCenter(int x, int y){
    if(x == CENTERX1 && y == CENTERY1){
        return true;
		}
    if(x == CENTERX2 && y == CENTERY2){
        return true;
		}
    if(x == CENTERX3 && y == CENTERY3){
        return true;
		}
    if(x == CENTERX4 && y == CENTERY4){
        return true;
		}
    return false;
}


void updatePosition(int r1, int c1, int r2, int c2){
		
    if(r1+1 == r2){
        // south
        //direction = newCoord(1,0);
			  direction = SOUTH;
    } else if(r2+1 == r1) {
        // north
        //direction = newCoord(-1,0);
			  direction = NORTH;
    } else if(c1+1 == c2){
        // east
        //direction = newCoord(0,1);
				direction = EAST;
    } else{
        // west
        //direction = newCoord(0,-1);
			  direction = WEST;
    }
	
	
}

void initFloodfill() {
    for(int i = 0; i < 16 ; i++){
        for(int j = 0; j < 16 ; j++){
            visit[i][j] = false;
            dist[i][j] = -1;
            parentX[i][j] = -1;
            parentY[i][j] = -1;
            bestRouteX[i][j] = -1;
            bestRouteY[i][j] = -1;
			      grid[i][j] = false;
        }
    }
	
		for(int i = 0 ; i < 15 ; i++) grid[i][1] = true, grid[14][i+1] = true;
		grid[14][15] = false;
		
		
    Qx = newStack(10000);
    Qy = newStack(10000);
	//direction = newCoord(0,0);
		direction = MIDDLE;
    push(storex, Qx, 0);
    push(storey, Qy, 0);
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

void driver(Stack * stack){
/*
	for(int i = 0; i < 8; i ++){
		floodfill();
	}*/
		while(floodfill());
		//STOP
		int bestX = 0;
		int bestY = 0;

		printf("\rBest dist = %d\r\n", dist[0][0]);
	//  return;
		while(!isCenter(bestX,bestY)){
			int nxtX, nxtY;
			nxtX = bestRouteX[bestX][bestY];
			nxtY = bestRouteY[bestX][bestY];

			bestX = nxtX;
			bestY = nxtY;
			push(storex, stack, bestX);
			push(storey, stack, bestY);
		  printf("\rBestX = %d , BestY = %d \r\n",  bestX , bestY);
		}
}

bool Occupy(int row, int col){
	if(!grid[row][col]){
		grid[row][col] = true;
		return true;
	}
	return false;
}
