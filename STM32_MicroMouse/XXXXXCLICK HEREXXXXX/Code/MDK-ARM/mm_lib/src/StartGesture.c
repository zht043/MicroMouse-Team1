#include "StartGesture.h"


#define Both 0
#define None 1
#define Left 2
#define Right 3
uint16_t L_IR_Threshold  = 660; 
uint16_t LF_IR_Threshold = 2500;
uint16_t RF_IR_Threshold = 2500;
uint16_t R_IR_Threshold  = 750;


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

uint8_t startGesture(void) {
		uint8_t SG_finished = 0; //Flag that marks the end of gesture phase
		uint32_t tBuff = 1000; //1 sec buffer
		uint32_t t0;
		uint8_t continueFlag = 0; //Flag for restarting this gesture session
		uint8_t Program; //determines which program to start with
		while(!SG_finished) {
				blinkLED(12);
				while(GestureState() == None) GestureLED();

				if(GestureState() == Left) {
						//restart session if staying in left state for too long
						t0 = millis();
						while(GestureState() == Left) {
								GestureLED(); 
								if(millis() - t0 > tBuff) 
								{
										continueFlag = 1; 
										break;
								}		
						}
						if(GestureState() == Both) continueFlag = 1;
						if(continueFlag) 
						{
								continueFlag = 0; 
								continue;
						}
						
						//wait till swept to right
						t0 = millis();
						while(GestureState() != Right) {
								GestureLED(); 
								if(millis() - t0 > tBuff) 
								{
										continueFlag = 1; 
										break;
								}
						}
						if(GestureState() == Both) continueFlag = 1;
						if(continueFlag) 
						{
								continueFlag = 0; 
								continue;
						}
						
						//restart session if staying in right state for too long
						t0 = millis();
						while(GestureState() == Right) {
								GestureLED(); 
								if(millis() - t0 > tBuff) 
								{
										continueFlag = 1; 
										break;
								}
						}
						if(GestureState() == Both) continueFlag = 1;
						if(continueFlag) 
						{
								continueFlag = 0; 
								continue;
						}
						
						//wait till swept to left
						t0 = millis();
						while(GestureState() != Left) {
								GestureLED(); 
								if(millis() - t0 > tBuff) 
								{
										continueFlag = 1; 
										break;
								}
						}
						if(GestureState() == Both) continueFlag = 1;
						if(continueFlag) 
						{
								continueFlag = 0; 
								continue;
						}
						
						
						//restart session if staying in left state for too long
						t0 = millis();
						while(GestureState() == Left) {
								GestureLED(); 
								if(millis() - t0 > tBuff) 
								{
										continueFlag = 1; 
										break;
								}		
						}
						if(GestureState() == Both) continueFlag = 1;
						if(continueFlag) 
						{
								continueFlag = 0; 
								continue;
						}
						
						//restart session if state is not None 
						while(millis() - t0 < tBuff / 4) {
								GestureLED(); 
								if(GestureState() != None) 
								{
										continueFlag = 1; 
										break;
								}
						}	
						if(continueFlag)
						{
								continueFlag = 0; 
								continue;
						}
						Program = ProgramA;
						SG_finished = 1;
				}
				
				if(GestureState() == Right) {
						//restart session if staying in right state for too long
						t0 = millis();
						while(GestureState() == Right) {
								GestureLED(); 
								if(millis() - t0 > tBuff) 
								{
										continueFlag = 1; 
										break;
								}		
						}
						if(GestureState() == Both) continueFlag = 1;
						if(continueFlag) 
						{
								continueFlag = 0; 
								continue;
						}
						
						//wait till swept to left
						t0 = millis();
						while(GestureState() != Left) {
								GestureLED(); 
								if(millis() - t0 > tBuff) 
								{
										continueFlag = 1; 
										break;
								}
						}
						if(GestureState() == Both) continueFlag = 1;
						if(continueFlag) 
						{
								continueFlag = 0; 
								continue;
						}
						
						//restart session if staying in left state for too long
						t0 = millis();
						while(GestureState() == Left) {
								GestureLED(); 
								if(millis() - t0 > tBuff) 
								{
										continueFlag = 1; 
										break;
								}
						}
						if(GestureState() == Both) continueFlag = 1;
						if(continueFlag) 
						{
								continueFlag = 0; 
								continue;
						}
						
						//wait till swept to right
						t0 = millis();
						while(GestureState() != Right) {
								GestureLED(); 
								if(millis() - t0 > tBuff) 
								{
										continueFlag = 1; 
										break;
								}
						}
						if(GestureState() == Both) continueFlag = 1;
						if(continueFlag) 
						{
								continueFlag = 0; 
								continue;
						}
						
						
						//restart session if staying in right state for too long
						t0 = millis();
						while(GestureState() == Right) {
								GestureLED(); 
								if(millis() - t0 > tBuff) 
								{
										continueFlag = 1; 
										break;
								}		
						}
						if(GestureState() == Both) continueFlag = 1;
						if(continueFlag) 
						{
								continueFlag = 0; 
								continue;
						}
						
						//restart session if state is not None 
						while(millis() - t0 < tBuff / 4) {
								GestureLED(); 
								if(GestureState() != None) 
								{
										continueFlag = 1; 
										break;
								}
						}	
						if(continueFlag)
						{
								continueFlag = 0; 
								continue;
						}
						Program = ProgramB;
						SG_finished = 1;
				}
				if(GestureState() == Both) {
						t0 = millis();
						while(GestureState() == Both) {
								if(millis() - t0 > 2 * tBuff) break;
								GestureLED();
						}
						if(millis() - t0 < 2 * tBuff) continue;
						Program = ProgramC;
						SG_finished = 1;
				}					
		}
		
		if(Program == ProgramA) blinkLED_Left(12);
		if(Program == ProgramB) blinkLED_Right(12);
		if(Program == ProgramC) blinkLED_Both(12);
		return Program;
}

