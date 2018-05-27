#include <stdio.h>

// ------ General PID Controller ------ // 

int us;
int micros() {
	return us;
}

typedef struct {
		double Kp,Ki,Kd;
		double prevErr;
		double integrator;
		double pTerm, iTerm, dTerm;
		int isFirstIteration;
		int Period;
		int prevT;
}PID_Ctr;



void initPID(PID_Ctr* ctr, double Kp, double Ki, double Kd, int Period_us) {
		ctr->Kp = Kp;
		ctr->Ki = Ki;
		ctr->Kd = Kd;
		ctr->isFirstIteration = 1;
		ctr->integrator = 0.000f;
		ctr->Period = Period_us;
}

double us_to_sec(int us) {
		return (double)us / 1000000.000f;
}



double PID(PID_Ctr* ctr, double currErr) {
		if(ctr->isFirstIteration) {
				ctr->isFirstIteration = 0;
				ctr->prevErr = currErr;
				ctr->prevT = micros();
				return ctr->Kp * currErr;
		}
		//P
		ctr->pTerm = ctr->Kp * currErr;
		
		//time management
		int dT = micros() - ctr->prevT;
		if(dT < ctr->Period) return (-1.000f) * (ctr->pTerm + ctr->iTerm + ctr->dTerm);
		if(dT > 3 * ctr->Period) {
				ctr->prevT = micros();
				ctr->prevErr = currErr;
				return (-1.000f) * (ctr->pTerm + ctr->iTerm + ctr->dTerm);
		}
		
		//I
		ctr->integrator += currErr * us_to_sec(dT);
		ctr->iTerm = ctr->Ki * ctr->integrator;
		
		//D
		ctr->dTerm = ctr->Kd * (currErr - ctr->prevErr) / dT; 
		
		
		ctr->prevT = micros();
		ctr->prevErr = currErr;
		return (-1.000f) * (ctr->pTerm + ctr->iTerm + ctr->dTerm);
}
int main() {
	PID_Ctr Angular_Disp;
	double Err = 0, w = 0;
	initPID(&Angular_Disp, 1.000f, 1.000f, 1.000f, 10);
	printf("w = %lf   pTerm = %lf, iTerm = %lf, dTerm = %lf \n" , w, Angular_Disp.pTerm, Angular_Disp.iTerm, Angular_Disp.dTerm );
	printf("Err = %lf   pErr= %lf, pT = %d, isF = %d \n" , w, Angular_Disp.prevErr, Angular_Disp.prevT, Angular_Disp.isFirstIteration );
	while(1) 
	{
        
		scanf("%d %lf", &us, &Err);
		w = PID(&Angular_Disp, Err);  // Error = Actual val - Expected val
  		printf("w = %lf   pTerm = %lf, iTerm = %lf, dTerm = %lf \n" , w, Angular_Disp.pTerm, Angular_Disp.iTerm, Angular_Disp.dTerm );
  		printf("Err = %lf   pErr= %lf, pT = %d, isF = %d \n" , w, Angular_Disp.prevErr, Angular_Disp.prevT, Angular_Disp.isFirstIteration );
	}
		
}
