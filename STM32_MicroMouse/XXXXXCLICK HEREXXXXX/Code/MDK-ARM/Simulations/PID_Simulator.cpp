#include <stdio.h>

// ------ General PID Controller ------ // 

int us;
int micros() {
	return us;
}

int sT_t0 = 0;
int softTimer(int period_us) {
		if( micros() - sT_t0 > period_us ) {
				sT_t0 = micros();
				return 1;
		}
		return 0;
}

typedef struct {
		double Kp,Ki,Kd;
		double prevErr;
		double integrator;
		int isFirstIteration;
		int Period;
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
		return (double)us / 1000000;
}

double pTerm, iTerm, dTerm;

double PID(PID_Ctr* ctr, double currErr) {
		if(ctr->isFirstIteration) {
				ctr->isFirstIteration = 0;
		  	
				return ctr->Kp * currErr;
		}
		//P
		pTerm = ctr->Kp * currErr;
 		
		if(!softTimer(ctr->Period)) return (-1.000f) * (pTerm + iTerm + dTerm);
		
		//I
		ctr->integrator += currErr * us_to_sec(ctr->Period);
		iTerm = ctr->Ki * ctr->integrator;
		//D
		dTerm = ctr->Kd * (currErr - ctr->prevErr) / us_to_sec(ctr->Period) / 10000; // 10000 is just a dimentional scaling factor
		ctr->prevErr = currErr;
		return (-1.000f) * (pTerm + iTerm + dTerm);
}


int main() {
	PID_Ctr Angular_Disp;
	initPID(&Angular_Disp, 1.000f, 1.000f, 1.000f, 10);
	while(1) 
	{
        double Err, w;
		scanf("%d %lf", &us, &Err);
		w = PID(&Angular_Disp, Err);  // Error = Actual val - Expected val
  		printf("w = %lf   pTerm = %lf, iTerm = %lf, dTerm = %lf \n" , w, pTerm, iTerm, dTerm );
	}
		
}
