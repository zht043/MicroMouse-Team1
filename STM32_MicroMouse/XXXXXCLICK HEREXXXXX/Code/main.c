#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
/////////////////////////////// user_lib
#include "SysTime.h"
#include "GPIO.h"
#include "Timer.h"
#include "USART.h"
#include "SPI.h"
#include "ADC.h"
/////////////////////////////// mm_lib
#include "HelperMethods.h"
#include "Motor.h"
#include "Led.h"
#include "IR.h"
#include "StartGesture.h"
#include "PID.h"
/////////////////////////////// var & const & macros
extern __IO uint16_t IR_values[6];
/////////////////////////////// func declarations 
void ProgramA_main(void);
void ProgramB_main(void);
void ProgramC_main(void);
//////////////////////////////
double scalingIRErr = 1000;


void initPeriphs(void) {
		SysTime_Init();
		initLED();
		//------------------------------------------------
		initUSART(USART1, PB6, PB7, 9600);
		printfForUx(USART1);
		scanfForUx(USART1);
		printf("\rHellow World! El Psy Congroo!!!\r\n");
		//------------------------------------------------
		initIR();
		initMotor();
		initEncoder();
		ResetEnc();
}
int main(void)
{
		initPeriphs();
		uint8_t Program = startGesture();
		switch(Program) {
			case ProgramA : ProgramA_main(); break;
			case ProgramB : ProgramB_main(); break;
			case ProgramC : ProgramC_main(); break;
			default : break;
		}
}

//ProgramA : Search Run
void ProgramA_main() {
		//motor(30,30);
		//delay(500);
		//gS_Tester(30);
		//TurnLeft();
		luckyGO();
		/*while(1) {
				tUC();
		}*/
		//motor(0,0);
}


//ProgramB : Speed Run
void ProgramB_main() {
		//Not there yet, blink to show warnings
		while(1) blinkLED(1);
}

double tP = 45.000f, tI = 0.000f, tD = 10000.000f;
extern uint32_t periodFFF;
//ProgramC : Calibration
void ProgramC_main() {
		char str[20];
		printf("\rXXXXXXXXXXX\r\n");
	while(1) {
		ResetEnc();
		readLine(str);
		if(!strcmp(str, "IR")) {
				while(1) { 	
						printf("\rL[%4d] ** LFA[%4d] LFB[%4d]   #######   RFB[%4d] RFA[%4d] ** R[%4d]\r\n", 
										IRv_L, 
										IRv_LFA, 
										IRv_LFB, 
										IRv_RFB, 
										IRv_LFA, 
										IRv_R);
						delay(1);
				}
		}
		if(!strcmp(str, "ENC")) {
				while(1) {
						printf("\rLENC[%9d]   ###########   RENC[%9d]\r\n", LEnc(), REnc());
						delay(1);
				}
		}
		if(!strcmp(str,	"AC")) {
				while(1) {
						//printf("\r%d\r\n", LEnc() - REnc());
						printf("\r%lf\r\n", convertToAngle(LEnc() - REnc()));
						delay(1);
				}
		}
		if(!strcmp(str, "LC")) {
				while(1) {
						//printf("\r%d\r\n", LEnc() - REnc());
						printf("\r%lf\r\n", convertToCM((double)(LEnc() + REnc())));
						delay(1);
				}
		}
		if(!strcmp(str, "VTL")) {
				LspeedTester();
		}
		if(!strcmp(str, "VTR")) {
				RspeedTester();
		}
		if(!strcmp(str, "GS")) {
				while(1) {
						
						printf("\rEnter speed Plz\r\n");
						readLine(str);
						double speed = strtof(str, NULL);
						printf("\r%lf\r\n", speed);
						
						printf("\rEnter P I D values seprated by a space Plz\r\n");
						readLine(str);
						// tP, tI, tD
						char * token;
						token = strtok(str, " ");
						tP = atof(token);
					//printf("\r Input: %s\r\n", str);
						token = strtok(NULL, " ");
						tI = atof(token);				
						token = strtok(NULL, " ");
						tD = atof(token);
					printf("\rEntered value:  P : %lf I : %lf D : %lf\r\n", tP, tI, tD); 
						
					
						printf("\rEnter Time Plz\r\n");
						readLine(str);
						periodFFF = strtof(str, NULL);
						gS_Tester(speed);
						stop();
					
				}
		}
		
		if(!strcmp(str, "TH")) {
			while(1) {
				printf("\rIR_Errgen Value: %lf\r\n", IR_ErrGen());
			}
		}
		if(!strcmp(str, "IRT")) {
			while(1) {
			printf("\rSet scaling factor and speed seperated by space.\r\n");
			char * token;
			double speed;
			readLine(str);
			token = strtok(str, " ");
		  scalingIRErr = atof(token);
			token = strtok(NULL, " ");
			speed = atof(token);
				
				
			printf("\rEnter P I D values seprated by a space Plz\r\n");
						readLine(str);
						// tP, tI, tD
						char * token2;
						token2 = strtok(str, " ");
						tP = atof(token2);
					//printf("\r Input: %s\r\n", str);
						token2 = strtok(NULL, " ");
						tI = atof(token2);				
						token2 = strtok(NULL, " ");
						tD = atof(token2);
					printf("\rEntered value:  P : %lf I : %lf D : %lf\r\n", tP, tI, tD); 
							
				
			gS_Tester(speed);
				stop();
			}
		}
		
		if(!strcmp(str, "TN")) {
			while(1) {
				double speed = 35.00;
				printf("\r left Turn\n\r");
				TurnLeft();
				//printf("\r Left Turn\n\r");
				//turn45(speed, -1);
				scanf("press enter to continue");
			}
		}
		
	}
}





















#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
