#include "StartGesture.h"

#define Both 0
#define None 1
#define Left 2
#define Right 3
uint16_t L_IR_Threshold  = 660; 
uint16_t LF_IR_Threshold = 2500;
uint16_t RF_IR_Threshold = 2500;
uint16_t R_IR_Threshold  = 850;


extern __IO uint16_t IR_values[6];
uint8_t GestureState(void) {
		if(IRv_L > L_IR_Threshold) {
				if(IRv_R > R_IR_Threshold) return Both;
				else return Left;
		}
		else {
				if(IRv_R > R_IR_Threshold) return Right;
				else return None;
		}
}
void GestureLED(void) {
		switch(GestureState()) {
					case Both: 
							L_LED_ON();
							R_LED_ON();
					break;
					case None: 
							L_LED_OFF();
							R_LED_OFF();
					break;
					case Left: 
							L_LED_ON();
							R_LED_OFF();
					break;
					case Right: 
							L_LED_OFF();
							R_LED_ON();
					break;
					default: break;
		}
}
void startGesture(void) {
		uint8_t SG_finished = 0;
		uint32_t tBuff = 1000; //1 sec buffer
		uint32_t t0;
		uint8_t continueFlag = 0;
		while(!SG_finished) {
				while(GestureState() != Left) GestureLED();
				t0 = millis();
				while(GestureState() == Left) {
						GestureLED();
						if(millis() - t0 > tBuff) {continueFlag = 1; break;}
				}
				if(continueFlag) {continueFlag = 0; continue;}
				t0 = millis();
				while(GestureState() != Right) {
						GestureLED();
						if(millis() - t0 > tBuff) {continueFlag = 1; break;}
				}
				if(continueFlag) {continueFlag = 0; continue;}
				t0 = millis();
				while(GestureState() == Right) {
						GestureLED();
						if(millis() - t0 > tBuff) {continueFlag = 1; break;};
				}
				if(continueFlag) {continueFlag = 0; continue;}
				t0 = millis();
				while(GestureState() != Left) {
						GestureLED();
						if(millis() - t0 > tBuff) {continueFlag = 1; break;};
				}
				if(continueFlag) {continueFlag = 0; continue;}
				t0 = millis();
				while(GestureState() == Left) GestureLED();
				while(millis() - t0 < tBuff) {
						GestureLED();
						if(GestureState() != None) {continueFlag = 1; break;};
				}
				if(continueFlag) {continueFlag = 0; continue;}
				SG_finished = 1;
				blinkLED(12);
		}
}

