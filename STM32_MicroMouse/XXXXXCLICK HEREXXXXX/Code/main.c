#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "SysTime.h"
#include "GPIO.h"
#include "Timer.h"
#include "USART.h"
#include "SPI.h"
#include "ADC.h"
///////////////////////////////
#include "Motor.h"
#include "Led.h"
#include "IR.h"
///////////////////////////////
int main(void)
{
		SysTime_Init();
		initLED();
		blinkLED(10);
	
		initUSART(USART1, PB6, PB7, 9600);
		printfForUx(USART1);
		scanfForUx(USART1);
		printf("\rHellow World! El Psy Congroo!!!\r\n");
		
		initIR();
		//initMotor();
		///motorTester();
	/*
		initMotor();
		initEncoder();
		while(1) {	
				printf("\r%d %d\r\n", LEnc(), REnc());
		}*/
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
