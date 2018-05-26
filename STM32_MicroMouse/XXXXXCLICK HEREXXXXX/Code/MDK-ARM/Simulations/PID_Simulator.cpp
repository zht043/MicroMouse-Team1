#include <stdio.h>

// ------ General PID Controller ------ // 



typedef struct {
		double Kp,Ki,Kd;
		double prevErr;
		double integrator;
		double pTerm, iTerm, dTerm;
		uint8_t isFirstIteration;
		uint32_t Period;
		uint32_t prevT;
}PID_Ctr;



void initPID(PID_Ctr* ctr, double Kp, double Ki, double Kd, uint32_t Period_us) {
		ctr->Kp = Kp;
		ctr->Ki = Ki;
		ctr->Kd = Kd;
		ctr->isFirstIteration = 1;
		ctr->integrator = 0.000f;
		ctr->Period = Period_us;
}

double us_to_sec(uint32_t us) {
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
		uint32_t dT = micros() - ctr->prevT;
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
		ctr->dTerm = ctr->Kd * (currErr - ctr->prevErr) / us_to_sec(dT); 
		
		
		ctr->prevT = micros();
		ctr->prevErr = currErr;
		return (-1.000f) * (ctr->pTerm + ctr->iTerm + ctr->dTerm);
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
