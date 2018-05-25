#include "PID.h"

// ------ General PID Controller ------ // 



typedef struct {
		double Kp,Ki,Kd;
		double prevErr;
		double integrator;
		uint8_t isFirstIteration;
		uint32_t Period;
		uint32_t sT_t0;
}PID_Ctr;


uint8_t softTimer(PID_Ctr* ctr, uint32_t period_us) {
		if( micros() - ctr->sT_t0 > period_us ) {
				ctr->sT_t0 = micros();
				return 1;
		}
		return 0;
}

void initPID(PID_Ctr* ctr, double Kp, double Ki, double Kd, uint32_t Period_us) {
		ctr->Kp = Kp;
		ctr->Ki = Ki;
		ctr->Kd = Kd;
		ctr->isFirstIteration = 1;
		ctr->integrator = 0.000f;
		ctr->Period = Period_us;
}

double us_to_sec(uint32_t us) {
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
		if(!softTimer(ctr, ctr->Period)) return (-1.000f) * (pTerm + iTerm + dTerm);
		
		//I
		ctr->integrator += currErr * us_to_sec(ctr->Period);
		iTerm = ctr->Ki * ctr->integrator;
		//D
		dTerm = ctr->Kd * (currErr - ctr->prevErr) / us_to_sec(ctr->Period)  / 10000; // 10000 is just a dimentional scaling factor 
		ctr->prevErr = currErr;
		return (-1.000f) * (pTerm + iTerm + dTerm);
}


// ------ Encoder Helper Methods ------ //
double EncoderDiffConversionFactor = 0.00289438f;
double convertToAngle(double diff) {
		return diff * EncoderDiffConversionFactor;	
}

//Test Me
double EncoderDispConversionFactor = 0.000178880137; //0.0618025751;
double convertToCM(double cnt) {
		return cnt * EncoderDispConversionFactor;	
}



//Test Me
#define EncSamplingPeriod 100
uint32_t prevT_vL = 0;
uint32_t prevLEnc = 0;
double vL = 0.000f;
double Lspeed(void) {
		if(prevT_vL == 0) 
			return 0.000f;
		
		uint32_t dT = micros() - prevT_vL;
		
		if(dT < EncSamplingPeriod) 
			return vL;
		
		if(dT > 3 * EncSamplingPeriod) {
				prevT_vL = micros();
				prevLEnc = LEnc();
				return 0.000f;
		}
		
		vL = convertToCM((double)(LEnc() - prevLEnc)) / (double)dT;
		prevLEnc = LEnc();
		prevT_vL = micros();
		return vL;
}

uint32_t prevT_vR = 0;
uint32_t prevREnc = 0;
double vR = 0.000f;
double Rspeed(void) {
		if(prevT_vR == 0) return 0.000f;
		uint32_t dT = micros() - prevT_vR;
		if(dT < EncSamplingPeriod) return vR;
		if(dT > 3 * EncSamplingPeriod) {
				prevT_vR = micros();
				prevREnc = REnc();
				return 0.000f;
		}
		vR = convertToCM(REnc() - prevREnc) / (double)dT;
		prevREnc = REnc();
		prevT_vR = micros();
		return vR;
}
void LspeedTester(void) {
		while(1) {
				uint32_t t0 = millis();
				while(millis() - t0 < 10) motor(convertToCM(REnc()) * 10.00f, 0);
				printf("\r%lf\r\n", Lspeed());
		}
}	

void RspeedTester(void) {
		while(1) {
				motor(0, convertToCM(LEnc()) * 10.00f);
				printf("\r%lf\r\n", Rspeed());
		}
}	



// ------ IR Helper Methods ------ //	
extern __IO uint16_t IR_values[6];
#define LF_th 1700	
#define RF_th 1700	
#define L_th 600
#define R_th 600		
double IR_ErrGen(void) {
		double ret = 0.000f;
		if(IRv_L > L_th) ret -= (IRv_L - L_th) / (4095.000f - L_th);
		if(IRv_LFA > LF_th) ret -= (IRv_LFA - LF_th) / (4095.000f - LF_th);
		if(IRv_RFB > RF_th) ret += (IRv_RFB - RF_th) / (4095.000f - RF_th);
		if(IRv_R > R_th) ret += (IRv_R - R_th) / (4095.000f - R_th);
		return ret;
} 	
	
// ------ Straight ------ //
uint32_t gS_t0;
uint8_t End_Straight_Condition(void) {
		if(millis() - gS_t0 < 700) return 0;
		return 1;
}
uint32_t spt_cnt = 0;
void Straight_Parallel_Task(void) {
		spt_cnt ++;
}
void goStraight(double speed) {
		ResetEnc();
		
		PID_Ctr Angular_Disp;
		initPID(&Angular_Disp, 20.000f, 5.000f, 0.000f, 1);
		
	/*
		PID_Ctr Linear_Vel;
		initPID(&Linear_Vel, 5.000f, 0.000f, 0.000f, 10);  //fix period and pval
		*/
	/*
		PID_Ctr Angular_Disp_Inc;
		initPID(&Angular_Disp_Inc, 5.000f, 0.000f, 0.000f, 10);
		*/
		double v = 50.000f, w, w_inc = 0.000f;
		double AD_Exp = 0.000f, LV_Exp = speed;
		while(!End_Straight_Condition()) {
				w = PID(&Angular_Disp, convertToAngle(LEnc() - REnc()) - AD_Exp );  // Error = Actual val - Expected val
				//v = PID(&Linear_Vel, (Lspeed() + Rspeed()) / 2.000f - LV_Exp);
				//w_inc = PID(&Angular_Disp_Inc, IR_ErrGen());
				curve(v, (w + w_inc));
				Straight_Parallel_Task();
		}
}
void gS_Tester(void) {
		gS_t0 = millis();
		goStraight(50);
		stop();
}








































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


