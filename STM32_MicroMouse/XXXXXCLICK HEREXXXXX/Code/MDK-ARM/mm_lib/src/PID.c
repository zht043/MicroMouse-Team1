#include "PID.h"

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
				ctr->pTerm = ctr->Kp * currErr;
				return (-1.000f) * ctr->pTerm;
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
		ctr->dTerm = ctr->Kd * (currErr - ctr->prevErr) / (double)dT; 
		
		
		ctr->prevT = micros();
		ctr->prevErr = currErr;

		return (-1.000f) * (ctr->pTerm + ctr->iTerm + ctr->dTerm);

}


// ------ Encoder Helper Methods ------ //
double EncoderDiffConversionFactor = 0.00289438f;
double convertToAngle(double diff) {
		return diff * EncoderDiffConversionFactor;	
}


double EncoderDispConversionFactor = 0.000178880137; //0.0618025751;
double convertToCM(double cnt) {
		return cnt * EncoderDispConversionFactor;	
}

double Range(void) {
		return convertToCM((double)(LEnc() + REnc()));
}



//Test Me
#define EncSamplingPeriod 100
int32_t prevT_vL = 0;
int32_t prevLEnc = 0;
double vL = 0.000f;
double Lspeed(void) {
		//first iter
		if(prevT_vL == 0) {
				prevT_vL = micros();
				prevLEnc = LEnc();
				return 0.000f;
		}
		
		uint32_t dT = micros() - prevT_vL;
		
		if(dT < EncSamplingPeriod) return vL;
		
		if(dT > 3 * EncSamplingPeriod) {
				prevT_vL = micros();
				prevLEnc = LEnc();
				return 0.000f;
		}
		
		vL = convertToCM((double)(LEnc() - prevLEnc)) / us_to_sec(dT) ;
		prevLEnc = LEnc();
		prevT_vL = micros();
		return vL;
}

int32_t prevT_vR = 0;
int32_t prevREnc = 0;
double vR = 0.000f;
double Rspeed(void) {
		if(prevT_vR == 0) {
				prevT_vR = micros();
				prevLEnc = REnc();
				return 0.000f;
		}
		
		uint32_t dT = micros() - prevT_vR;
		
		if(dT < EncSamplingPeriod) return vR;
		
		if(dT > 3 * EncSamplingPeriod) {
				prevT_vR = micros();
				prevLEnc = REnc();
				return 0.000f;
		}
		
		vR = convertToCM((double)(REnc() - prevREnc)) / us_to_sec(dT);
		prevREnc = REnc();
		prevT_vR = micros();
		return vR;
}


void LspeedTester(void) {
		while(1) {
				uint32_t t0 = millis();
				while(millis() - t0 < 10) {
						motor(convertToCM(REnc()) * 10.00f, 0);
						Lspeed();
				}
				printf("\r%lf\r\n", Lspeed());
		}
}	

void RspeedTester(void) {
		while(1) {
				uint32_t t0 = millis();
				while(millis() - t0 < 10) {
						motor(0, convertToCM(LEnc()) * 10.00f);
						Rspeed();
				}
				printf("\r%lf\r\n", Rspeed());
		}
}	





// ------ IR Helper Methods ------ //	
extern __IO uint16_t IR_values[6];
#define LF_th 1400	
#define RF_th 3500	
#define L_th 500
#define R_th 720		
double IR_ErrGen(void) {
		double ret = 0.000f;
		if(IRv_L > L_th) ret -= (IRv_L - L_th) / (1700.000f - L_th);
		if(IRv_LFB > LF_th) ret -= (IRv_LFB - LF_th) / (3700 - LF_th);
		if(IRv_RFB > RF_th) ret += (IRv_RFB - RF_th) / (4095.000f*1.2 - RF_th);
		if(IRv_R > R_th) ret += (IRv_R - R_th) / (4000.000f - R_th);
		return ret;
} 	
	
// ------ Straight ------ //
uint32_t gS_t0;
uint32_t periodFFF = 0.000f;
double gS_d0;
uint8_t End_Straight_Condition(void) {
		if(millis() - gS_t0 < periodFFF) return 0;
		return 1;
}
uint32_t spt_cnt = 0;
void Straight_Parallel_Task(void) {
		spt_cnt ++;
}
extern double tP, tI, tD;

/*
void vReg(double Vexp) {
		PID_Ctr Linear_Vel;
		initPID(&Linear_Vel, 5.000f, 0.000f, 0.000f, 1000);  
		
}*/
void halt(double bufferRange) {
		PID_Ctr Linear_Disp;
		initPID(&Linear_Disp, 10, 0, 0, 100);
		//initPID(&Linear_Disp, tP, tI, tD, 100);	
	
		PID_Ctr Angular_Disp;
		initPID(&Angular_Disp, 12.000f, 0.000f, 100000.000f, 100);
		
		double v, w, dRange, Range0 = Range();;
		uint32_t t0 = millis();
		while(millis() - t0 < 1000) {
				w = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()));  
				dRange = Range() - Range0; 
				v = PID(&Linear_Disp, dRange - bufferRange);
				curve(v, w);
		}
		stop();
}

extern double scalingIRErr;

void goStraight(double speed) {
		
		
		PID_Ctr Angular_Disp;
		//initPID(&Angular_Disp, 10.000f, 0.000f, 10000.000f, 100);
		initPID(&Angular_Disp, tP, tI, tD, 100);
		
	/*
		PID_Ctr Linear_Vel;
		initPID(&Linear_Vel, 3.000f, 0.000f, 0.000f, 1000);  
		*/
	
		//PID_Ctr Angular_Disp_Inc;
		//initPID(&Angular_Disp_Inc, 15.000f, 0.000f, 0.000f, 1);
		
		double v, w, w_inc = 0.000f;
		double AD_Exp = 0.000f, LV_Exp = speed;
		while(!End_Straight_Condition()) {
				w_inc = IR_ErrGen() * scalingIRErr;
				w = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - AD_Exp );  // Error = Actual val - Expected val
				//v = PID(&Linear_Vel, ((Lspeed() + Rspeed()) / 2.000f) * 0.46728f - LV_Exp);  // LorRspeed max is 214, 100/214 = 0.46
				//w_inc = IR_ErrGen(); //PID(&Angular_Disp_Inc, IR_ErrGen());
				curve(speed, (w - w_inc));
			//printf("\rv: %05.5lf w: %05.5lf, w_inc: %05.5lf.\n\r", v, w, w_inc);
				//curve(v, w);
				
		}
}

double fabs(double variable) {
	return variable < 0 ? -variable : variable;
}

void pidIR(double speed) {
	
	
}
/*
void turn45(double speed, int8_t dir) {		
		PID_Ctr Linear_VelL, Linear_VelR;
		initPID(&Linear_VelL, tP, 0.000f, tD, 1000);  
		initPID(&Linear_VelR, tP, 0.000f, tD, 1000);  
			
		double expectedAngle = 90.000f * dir, LV_Exp = speed; // TODO what is expec	ted linear velocity??
		double realAngle = convertToAngle(LEnc() - REnc());

		while(fabs(realAngle - expectedAngle) > 1) {	
			realAngle = convertToAngle(LEnc() - REnc());
			double Rexpected, Lexpected;
			
			if (dir == -1) { // right side is faster
				Rexpected = 1.2632008 * speed ;
				Lexpected = 0.7367991 * speed ;
			} else {
				Lexpected = 1.2632008 * speed ;
				Rexpected = 0.7367991 * speed ;	
			}
			
			vL = PID(&Linear_VelL, Lspeed() * 0.46728f - Lexpected);  // LorRspeed max is 214, 100/214 = 0.46
			vR = PID(&Linear_VelR, Rspeed() * 0.46728f - Rexpected);
			motor(vL, vR);
		}	
}
*/

void TurnLeft(void) {
		double w0 = convertToAngle(LEnc() - REnc());
		while(convertToAngle(LEnc() - REnc()) - w0 > -90.000f) motor(-50, 50);
		//while(convertToAngle(LEnc() - REnc()) - w0 > -.000f) motor(.7 * speed, 1.3 * speed);
		//motor(0.00f,0.00f);
		//delay(300);
		
}
void TurnRight(void) {
		double w0 = convertToAngle(LEnc() - REnc());
		while(convertToAngle(LEnc() - REnc()) - w0 < 90.000f) motor(50, -50);	
}
void turnBackX(void) {
		double w0 = convertToAngle(LEnc() - REnc());
		while(convertToAngle(LEnc() - REnc()) - w0 < 180.000f) motor(30, -30);
		turnForward();
}
void gS_Tester(double speed) {
		gS_t0 = millis();
		//gS_d0 = convertToCM(LEnc() + REnc());
		goStraight(speed);
		halt(5.000f);
		stop();
		//TurnRight();
		stop();
}

void irPID(double speed) {
		PID_Ctr Angular_Disp;
		initPID(&Angular_Disp, 10.000f, 0.000f, 10000.000f, 100);
	
		PID_Ctr Linear_Vel;
		initPID(&Linear_Vel, 3.000f, 0.000f, 0.000f, 1000);  
		
		double v, w = 0.000f;
		double AD_Exp = 0.000f, LV_Exp = speed;
		while(!End_Straight_Condition()) {

		// Error = Actual val - Expected val

		w = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - AD_Exp );  
		// LorRspeed max is 214, 100/214 = 0.46

		v = PID(&Linear_Vel, ((Lspeed() + Rspeed()) / 2.000f) * 0.46728f - LV_Exp);  
		curve(v, w);
		}
}

#define goForward 0x01
#define goLeft 0x02
#define goRight 0x03
#define goBack 0x04



typedef struct {
		int wl, wr, wf;
}Fcell;	



Fcell updateCell(void) {
		Fcell cell;
		if(IRv_L > L_th && IRv_R > R_th)  cell.wf = 1;
		else cell.wf = 0;
		if(IRv_LFB > LF_th) cell.wl = 1;
		else cell.wl = 0;
		if(IRv_RFB > RF_th) cell.wr = 1;
		else cell.wr = 0;
		return cell;
}

int canMoveRight(){
	Fcell cell = updateCell();
	return !cell.wr;
}

int canMoveLeft(){
	Fcell cell = updateCell();
	return !cell.wl;
}

int canMoveForward(){
	Fcell cell = updateCell();
	return ((!cell.wr) & (!cell.wl));
}

void tUC(void) {
		Fcell cell = updateCell();
		if(cell.wf ) {L_LED_ON(); R_LED_ON();}
		if(cell.wl ) {L_LED_ON();}
		if(cell.wr ) {R_LED_ON();}
		if(!cell.wf && !cell.wl && !cell.wr) {L_LED_OFF(); R_LED_OFF();}
}

Fcell wall;
uint8_t getCmd() {
		if(wall.wf) {
			if(wall.wl) {
					if(wall.wr) return goBack;
					else return goRight;
			}
			else if(wall.wr) return goLeft;
			else return goLeft; //random
		}
		else return goForward;
}

void turnRight() {
		double v, w, w_inc = 0.000f;
	double AD_Exp = 0.000f, LV_Exp = 35.00f;
	double d0;
	PID_Ctr Angular_Disp;
	TurnRight();
					d0 = convertToCM(LEnc() + REnc() );		
					initPID(&Angular_Disp, tP, tI, tD, 100);	
					while(convertToCM(LEnc() + REnc() ) - d0 < 14) {
							//printf("Moving right");
							w_inc = IR_ErrGen() * scalingIRErr;
							w = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - AD_Exp ); 
							curve(35.000f, (w - w_inc));
					}
					halt(4);
}

void turnLeft() {
			double v, w, w_inc = 0.000f;
	double AD_Exp = 0.000f, LV_Exp = 35.00f;
	double d0;
	PID_Ctr Angular_Disp;
					TurnLeft();
					d0 = convertToCM(LEnc() + REnc() );		
					initPID(&Angular_Disp, tP, tI, tD, 100);	
					while(convertToCM(LEnc() + REnc() ) - d0 < 14) {
						//	printf("Moving left");
							w_inc = IR_ErrGen() * scalingIRErr;
							w = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - AD_Exp ); 
							curve(35.000f, (w - w_inc));
						
					}
					halt(4);
}

void turnForward() {
	double v, w, w_inc = 0.000f;
	double AD_Exp = 0.000f, LV_Exp = 35.00f;
	double d0;
	PID_Ctr Angular_Disp;
					d0 = convertToCM(LEnc() + REnc() );		
					initPID(&Angular_Disp, tP, tI, tD, 100);	
					while(convertToCM(LEnc() + REnc() ) - d0 < 14) {
							//printf("Moving forward");
							w_inc = IR_ErrGen() * scalingIRErr;
							w = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - AD_Exp ); 
							curve(35.000f, (w - w_inc));
					}
					halt(4);
}


void luckyGO(void) {
Stack* result = newStack(MAX);

	static int store[MAX];
	initFloodfill();
	driver(store, result);
}

uint8_t cmd = 0;
void luckyGOGO(void) {
	double v, w, w_inc = 0.000f;
	double AD_Exp = 0.000f, LV_Exp = 35.00f;
	double d0;
	PID_Ctr Angular_Disp;

			wall = updateCell();
		//	cmd = getCmd();
		//	printf("Command = %d\n\r", cmd);
	
	   static int store[MAX];
	   Stack* result = newStack(MAX);
	   initFloodfill();
	   driver(store, result);
		  if(cmd == 1){
					d0 = convertToCM(LEnc() + REnc() );		
					initPID(&Angular_Disp, tP, tI, tD, 100);	
					while(convertToCM(LEnc() + REnc() ) - d0 < 14) {
							//printf("Moving forward");
							w_inc = IR_ErrGen() * scalingIRErr;
							w = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - AD_Exp ); 
							curve(35.000f, (w - w_inc));
					}
					halt(4);
			}
			else if(cmd == 0) {
					TurnLeft();
					d0 = convertToCM(LEnc() + REnc() );		
					initPID(&Angular_Disp, tP, tI, tD, 100);	
					while(convertToCM(LEnc() + REnc() ) - d0 < 14) {
						//	printf("Moving left");
							w_inc = IR_ErrGen() * scalingIRErr;
							w = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - AD_Exp ); 
							curve(35.000f, (w - w_inc));
						
					}
					halt(4);
			}
			
			else if(cmd == goRight) {
					TurnRight();
					d0 = convertToCM(LEnc() + REnc() );		
					initPID(&Angular_Disp, tP, tI, tD, 100);	
					while(convertToCM(LEnc() + REnc() ) - d0 < 14) {
							//printf("Moving right");
							w_inc = IR_ErrGen() * scalingIRErr;
							w = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - AD_Exp ); 
							curve(35.000f, (w - w_inc));
					}
					halt(4);
			}
			
			else if(cmd == goBack) {
					//printf("Moving back");
					turnBackX();
			}
	//stop();
}
/*
while(1) {	
		wall = updateCell();
		if(skipCmd) skipCmd = 0; 
		else cmd = getCmd();
		
		if(cmd == goForward) {
					
					d0 = convertToCM(LEnc() + REnc() );		
					initPID(&Angular_Disp, tP, tI, tD, 100);	
					while(convertToCM(LEnc() + REnc() ) - d0 < 9) {
							w_inc = IR_ErrGen() * scalingIRErr;
							w = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - AD_Exp ); 
							curve(35.000f, (w - w_inc));
					}
					
					
					wall = updateCell();
					if(wall.wf) {L_LED_ON(); R_LED_OFF();}
					else if(wall.wr) {R_LED_ON(); L_LED_OFF();}
					else if(wall.wl) {L_LED_ON(); R_LED_ON();}
					else {L_LED_OFF(); R_LED_OFF();}
					cmd = getCmd();
					
					d0 = convertToCM(LEnc() + REnc() );
					initPID(&Angular_Disp, tP, tI, tD, 100);	
					while(convertToCM(LEnc() + REnc() ) - d0 < 5) {
							w_inc = IR_ErrGen() * scalingIRErr;
							w = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - AD_Exp ); 
							curve(35.000f, (w - w_inc));
					}
					
					if(cmd == goForward) {
							d0 = convertToCM(LEnc() + REnc() );
							initPID(&Angular_Disp, tP, tI, tD, 100);	
							while(convertToCM(LEnc() + REnc() ) - d0 < 4) {
									w_inc = IR_ErrGen() * scalingIRErr;
									w = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - AD_Exp ); 
									curve(35.000f, (w - w_inc));
							}
					}
					else if(cmd == goLeft) {
							halt(4);
							TurnLeft();
					}
					else if(cmd == goRight) {
							halt(4);
							TurnRight();
					}
					
		}
		if(cmd == goLeft) {
					d0 = convertToCM(LEnc() + REnc() );		
					initPID(&Angular_Disp, tP, tI, tD, 100);	
					while(convertToCM(LEnc() + REnc() ) - d0 < 9) {
					w_inc = IR_ErrGen() * scalingIRErr;
					w = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - AD_Exp ); 
					curve(35.000f, (w - w_inc));
					TurnLeft(); 	
		}
		if(cmd == goRight) {
					d0 = convertToCM(LEnc() + REnc() );		
					initPID(&Angular_Disp, tP, tI, tD, 100);	
					while(convertToCM(LEnc() + REnc() ) - d0 < 9) {
					w_inc = IR_ErrGen() * scalingIRErr;
					w = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - AD_Exp ); 
					curve(35.000f, (w - w_inc));
					TurnRight(); 	
		}				
	}
*/


/*
void newhalt(int period) {
	double initTime = micros();
	double curTime = micros();
  double vt = (Lspeed() + Rspeed()) / 2; 
	double vi = vt;
	int percent = 100;
	int dec = 10;
	 PID_Ctr Angular_Disp;
    initPID(&Angular_Disp, 12.000f, 0.000f, 100000.000f, 100);
    double v, angularv, angularvIncrement = 0.00f;
    double angularDisplacementExpected = 0.00f, linearVelocityExpected = vi;
	
	while(vt > 0.01f && percent > 0) {
		vt = (Lspeed() + Rspeed()) / 2; 
		curTime = micros();
  	
		if (curTime - initTime - period < 0.1f) {
				initTime = micros();
				percent -= dec;
				
		}		
vt = vi * (double) percent / 100;
			  angularv = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - angularDisplacementExpected);
        curve(vt, angularv);
						
	}
}

void halt(double dist) {
    // average velocity of the mouse at a given time t
    double vt = (Lspeed() + Rspeed()) / 2; 
		double vi = vt;
    PID_Ctr Angular_Disp;
    initPID(&Angular_Disp, 12.000f, 0.000f, 100000.000f, 100);
    double v, angularv, angularvIncrement = 0.00f;
    double angularDisplacementExpected = 0.00f, linearVelocityExpected = vi;
    // interval window is 1us
    double decrementSize = 1.0e-6f; 

    double expScalingFactor = 1.00f;
    double timeStarted = micros();
    double targetTime = dist/vi;

    while(vt > 0.01f) {
        vt = (Lspeed() + Rspeed()) / 2; 
        // calculate how much we need to decrement by
        double decelerationAmount = ((double)(micros() - timeStarted)/(double)targetTime) * vi; 
        // we will decrement vt by a predefined incrememnt for given distance
        vt -= decelerationAmount * expScalingFactor;
        // error calculation in angular velocity
        angularv = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - angularDisplacementExpected);
        curve(vt, angularv);
    }
}*/




/*
typedef struct {
		double Kp;
		double Ki;
		double Kd;
		double intergrator;
}PID_Var;

// ------ data stream manager ------ //

//IR
extern __IO uint16_t IR_values[6];
uint16_t IRprev[6] = {0};
uint16_t IRcurr[6] = {0};

uint8_t hasUpdated_IR(uint8_t ch) {
		IRcurr[ch] = IR_values[ch];
		if(IRcurr[ch] == IRprev[ch]) return 0;
		IRprev[ch] = IRcurr[ch];
		return 1;
}

//Enc
uint32_t LEnd_prev = 0;
uint32_t REnd_prev = 0;
uint32_t LEnc_curr = 0;
uint32_t REnc_curr = 0;
uint8_t hasUpdated_LEnc(void) {
		LEnc_curr = LEnc();
		if(LEnc_curr == LEnd_prev) return 0;
		LEnd_prev = LEnc_curr;
		return 1;
}
uint8_t hasUpdated_REnc(void) {
		REnc_curr = REnc();
		if(REnc_curr == REnd_prev) return 0;
		REnd_prev = REnc_curr;
		return 1;
}




// ------ Angular Displacement ------ //
double Enc_Ang_Disp = 0.000f;
double EncoderConversionFactor = 0.00289438f;

double convertToAngle(double diff) {
		return diff * EncoderConversionFactor;	
}

void Update_Enc_Ang_Disp(void) {
		Enc_Ang_Disp =  convertToAngle((double)(LEnc_curr - REnc_curr)); 
}

double IR_norm[8] = {0.000f};
#define IR_LF_Thresh 1700
#define IR_RF_Thresh 1700
void Update_IR_norm(uint8_t ch) {
		switch(ch) {
			case IR_L :
					
			break;
			case IR_LF :
					if(IRcurr[IR_LFA] < IR_LF_Thresh) IR_norm[IR_LF] = 0.000f;
					else IR_norm[IR_LF] = (IRcurr[IR_LFA] - IR_LF_Thresh) / 
																(4000           - IR_LF_Thresh) ;
			break;
			case IR_RF :
					if(IRcurr[IR_RFB] < IR_RF_Thresh) IR_norm[IR_RF] = 0.000f;
					else IR_norm[IR_RF] = (IRcurr[IR_RFB] - IR_RF_Thresh) / 
																(4000           - IR_RF_Thresh) ;
			break;
			case IR_R :
					
			break;
			default : break;
		}
}


double AD_dscale = 0.000f;
double AD_dEnc_dt = 0.000f;
void Update_AD_dEnc_dt(double prev, double curr, double dt) {
		AD_dEnc_dt = AD_dscale * ((curr - prev) / dt);
}	

// previous time when update was issued and time AD_threshold
uint32_t AD_t_prev; 
uint16_t AD_threshold = 1000; //derivative
// makes sure encoders dont get updated too fast
uint32_t AD_t_prev_enc;
uint16_t AD_threshold_enc = 10; //Enc
uint32_t AD_LENCprev, AD_RENCprev = 0;

uint8_t hasUpdated_T(uint32_t curtime) {
    return curtime - AD_t_prev > AD_threshold;
}



// idea: issue update when one of the sensor readings updates, and time interval
// is sufficiently large. 
uint8_t AD_uPID_Flag = 0;
void AD_DSM(void) {
    uint8_t LIR, RIR, LFIR, RFIR;
    uint8_t LENC, RENC;
    // not to confuse -- these variables store readings
    uint32_t LENCcur, RENCcur;
    LIR  = hasUpdated_IR(IR_L);
    RIR  = hasUpdated_IR(IR_R);
    LFIR = hasUpdated_IR(IR_LFA) || hasUpdated_IR(IR_LFB);
    RFIR = hasUpdated_IR(IR_RFA) || hasUpdated_IR(IR_RFB);

    LENC = hasUpdated_LEnc();
    RENC = hasUpdated_REnc();

    // Store if any updates are made to any sensor //
    uint8_t uIR  = LIR || RIR || LFIR || RFIR;
    uint8_t uENC = LENC || RENC;

    uint32_t curTime = micros();
    uint8_t dT = hasUpdated_T(curTime);

	////
    // have we updated encoder?
    if ( (curTime - AD_t_prev_enc > AD_threshold_enc) && uENC) {
				Update_Enc_Ang_Disp();	
				AD_uPID_Flag = 1;
        AD_t_prev_enc = micros();
    }//////
		if(uENC) {
				Update_Enc_Ang_Disp();	
				AD_uPID_Flag = 1;
		}

    // have we updated IR?
    if (uIR) {
				if(LIR)  Update_IR_norm(IR_L);
				if(RIR)  Update_IR_norm(IR_R);
				if(LFIR) Update_IR_norm(IR_LF);
				if(RFIR) Update_IR_norm(IR_RF);
				AD_uPID_Flag = 1;
    }

    // do we find a new derivative?
    if (dT) {
        LENCcur = LEnc_curr; 
        RENCcur =	REnc_curr;
				
				Update_AD_dEnc_dt(convertToAngle(AD_LENCprev - AD_RENCprev), 
													convertToAngle(LENCcur - RENCcur), 
													curTime - AD_t_prev);
        // update values
				AD_LENCprev = LENCcur;
			  AD_RENCprev = RENCcur;
        AD_t_prev = micros();
    }
}




PID_Var Angular_Disp;
void Set_Angular_Disp_Const(double pConst, double iConst, double dConst) {
		Angular_Disp.Kp = pConst;
		Angular_Disp.Ki = iConst;
		Angular_Disp.Kd = dConst;
}

void init_Angular_Disp_PID(double pConst, double iConst, double dConst) {
		Set_Angular_Disp_Const(pConst, iConst, dConst);
		Angular_Disp.intergrator = 0.000f;
		AD_t_prev = micros();
		AD_t_prev_enc = micros();
		AD_LENCprev = LEnc();
		AD_RENCprev = REnc();
}
double Angular_Disp_Perr(void) {
		return Enc_Ang_Disp;
}

double Angular_Disp_Ierr(void) {
		double Ierr;
		Ierr = IR_norm[IR_L] + IR_norm[IR_R];
		//Ierr += IR_norm[IR_LF] * 0.300f + IR_norm[IR_RF] * 0.300f;
		Angular_Disp.intergrator += Ierr;
		return Angular_Disp.intergrator;
}

double Angular_Disp_Derr(void) {
		return AD_dEnc_dt;
}
double Angular_Disp_PID_OUTPUT(void) {
	/////
		return Angular_Disp.Kp * Angular_Disp_Perr() +
					 Angular_Disp.Ki * Angular_Disp_Ierr() +
					 Angular_Disp.Kd * Angular_Disp_Derr();////
		return Angular_Disp.Kp * Angular_Disp_Perr();
}

//Search Run Controll
double gs_v, gs_w;
void init_gS(void) {
		init_Angular_Disp_PID(0.500f,0.000f,0.000f);
}
void goingStraight() {
		AD_DSM();
		gs_v = 30;
		if(AD_uPID_Flag) {
				gs_w = Angular_Disp_PID_OUTPUT(); 
				curve(gs_v, -1.00f * gs_w);
		}
		AD_uPID_Flag = 0;
}

void gS_Tester(void) {
		//init_gS();
		uint32_t t0 = millis();
		while(millis() - t0 < 600) {
					if(IRv_LFA < IR_LF_Thresh) IR_norm[IR_LF] = 0.000f;
					else IR_norm[IR_LF] = -(IRv_LFA - IR_LF_Thresh) / 
																(4000           - IR_LF_Thresh) ;
					
					if(IRv_RFB < IR_RF_Thresh) IR_norm[IR_RF] = 0.000f;
					else IR_norm[IR_RF] = (IRv_RFB - IR_RF_Thresh) / 
																(4000           - IR_RF_Thresh) ;

				
				curve(50, convertToAngle(LEnc() - REnc()) * 5.00f + Angular_Disp_Ierr() * );
		}
		stop();
}


*/


