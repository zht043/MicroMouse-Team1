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
		motor(30,30);
		delay(500);
		motor(0,0);
}


//ProgramB : Speed Run
void ProgramB_main() {
		//Not there yet, blink to show warnings
		while(1) blinkLED(1);
}

//ProgramC : Calibration
void ProgramC_main() {
		char str[20];
		printf("\rXXXXXXXXXXX\r\n");
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
