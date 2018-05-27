#include "Floodfill.h"
int storex[MAX];
int storey[MAX];

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

enum dirArr {MIDDLE, NORTH, EAST, SOUTH, WEST};
enum dirArr direction;

int output;

bool floodfill(){

		printf("Hello from the floodfill function!\n\r");
	
	  if(isEmpty(storex, Qx)){
		  return false;
  	}
		
		printf("Hello from the other side!\n\r");

    int x = peek(storex, Qx);
		
		printf("Can you hear me?\n\r");
    int y = peek(storey, Qy);
		printf("Why?\n\r");
    printf("X = %d, Y = %d\r\n", x, y);
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
        if(!withinBounds(nxtX, nxtY) /*|| grid[nxtX][nxtY]*/ ){
           continue;
		    }
				
				// Check if we can call from cur to next
				// EAST, SOUTH, WEST, NORTH
				
				 if(x+1 == nxtX){
					// south
					//direction = newCoord(1,0);
					if(direction == NORTH) {
						// Check U turn but we know its golden!
					}
					else if(direction == EAST) {
						// Check if we can Turn right 90
						if(!canMoveRight()) continue;
					}
					else if(direction == WEST) {
						// Check Turn left 90
						if(!canMoveLeft()) continue;
					}
					else {
						// Check forward
						if(!canMoveForward()) continue;
					}
				} 
				else if(nxtX+1 == x) {
					// north
					//direction = newCoord(-1,0);
					if(direction == SOUTH) {
					// Check U turn but we know its golden!
					}
					else if(direction == EAST) {
						// Check Turn left 90
						if(!canMoveLeft()) continue;
					}
					else if(direction == WEST) {
						// Check Turn right 90
						if(!canMoveRight()) continue;
					}
					else {
						// Check forward
						if(!canMoveForward()) continue;
					}
				} 
				else if(y+1 == nxtY){
					// east
					//direction = newCoord(0,1);
					if(direction == WEST) {
						// Check U turn but we know its golden
					}
					else if(direction == NORTH) {
						// Check Turn right 90
						if(!canMoveRight()) continue;
					}
					else if(direction == SOUTH) {
						// Check Turn left 90
						if(!canMoveLeft());
					}
					else {
						// Check move forward
						if(!canMoveForward()) continue;
					}
				} 
				else{
					// west
					//direction = newCoord(0,-1);
					if(direction == EAST) {
						// Call U turn
					}
					else if(direction == NORTH) {
						// Call Turn left 90
						if(!canMoveLeft()) continue;
					}
					else if(direction == SOUTH) {
						// Call Turn right 90
						if(!canMoveRight()) continue;
					}
					else {
						// Check if move forward
						if(!canMoveForward()) continue;
					}
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
				if(direction == NORTH) {
					// Call U turn
					//turnBack();
					output = 3;
				}
				else if(direction == EAST) {
					// Call Turn right 90
					//turnRight();
					output = 2;
				}
				else if(direction == WEST) {
					// Call Turn left 90
					//turnLeft();
					output = 0;
				}
				else {
					// Go forward
					//turnForward();
					output  = 1;
				}
				//outpunt = 3;
			  direction = SOUTH;
    } else if(r2+1 == r1) {
        // north
        //direction = newCoord(-1,0);
				if(direction == SOUTH) {
				// Call U turn
					//turnBack();
					output = 3;
				}
				else if(direction == EAST) {
					// Call Turn left 90
					//turnLeft();
					output = 0;
				}
				else if(direction == WEST) {
					// Call Turn right 90
					//turnRight();
					output = 2;
				}
				else {
					// Go forward
					//turnForward();
					output = 1;
				}
			  direction = NORTH;
    } else if(c1+1 == c2){
        // east
        //direction = newCoord(0,1);
				if(direction == WEST) {
					// Call U turn
					//turnBack();
					output = 3;
				}
				else if(direction == NORTH) {
					// Call Turn right 90
					//turnRight();
					output = 2;
				}
				else if(direction == SOUTH) {
					// Call Turn left 90
					//turnLeft();
					output = 0;
				}
				else {
					// Move forward
					//turnForward();
					output = 1;
					
				}
				direction = EAST;
    } else{
        // west
        //direction = newCoord(0,-1);
				if(direction == EAST) {
					// Call U turn
					//turnBack();
					output = 3;
				}
				else if(direction == NORTH) {
					// Call Turn left 90
					//turnLeft();
					output = 0;
				}
				else if(direction == SOUTH) {
					// Call Turn right 90
					//turnRight();
					output = 2;
				}
				else {
					// Move forward
					//turnForward();
					output = 1;
				}
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

int driver(int dir[], Stack * stack){
/*
	for(int i = 0; i < 8; i ++){
		floodfill();
	}*/
		printf("Hello from floodfill!\n\r");
		while(floodfill());
		printf("Hello after we know best route!\n\r");

		//STOP
		int bestX = 0;
		int bestY = 0;

		printf("\rBest dist = %d\r\n", dist[0][0]);
	//  return;
		while(!isCenter(bestX,bestY)){
			int nxtX, nxtY;
			nxtX = bestRouteX[bestX][bestY];
			nxtY = bestRouteY[bestX][bestY];

			updatePosition(bestX, bestY, nxtX, nxtY);
			push(dir, stack, direction); 
			
			bestX = nxtX;
			bestY = nxtY;
//			push(storex, stack, bestX);
//			push(storey, stack, bestY);
		  printf("\rBestX = %d , BestY = %d \r\n",  bestX , bestY);
			return output;
		}
}

bool Occupy(int row, int col){
	if(!grid[row][col]){
		grid[row][col] = true;
		return true;
	}
	return false;
}
