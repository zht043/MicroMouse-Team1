#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "SysTime.h"
#include "GPIO.h"
#include "Initiation.h"
#include "Timer.h"
#include "USART.h"
#include "SPI.h"
void DownTester(void) {
		SysTime_Init();
		GPIO LED0 = initIO(PB13,OUTPUT);
	  GPIO LED1 = initIO(PB12,OUTPUT);
		GPIO LED2 = initIO(PB14,OUTPUT);
		GPIO LED3 = initIO(PB15,OUTPUT);
		GPIO LED4 = initIO(PB1,OUTPUT);
		GPIO LED5 = initIO(PB0,OUTPUT);
		GPIO LED6 = initIO(PC4,OUTPUT);
		GPIO LED7 = initIO(PC5,OUTPUT);
		GPIO LED8 = initIO(PA8,OUTPUT);
		GPIO LED9 = initIO(PA9,OUTPUT);
		GPIO LED10 = initIO(PA10,OUTPUT);
		GPIO LED11 = initIO(PA11,OUTPUT);
		GPIO LED12 = initIO(PC1,OUTPUT);
		GPIO LED13 = initIO(PC2,OUTPUT);
		GPIO LED14 = initIO(PA2,OUTPUT);
		//GPIO Button0 = initIO(PA1, INPUT);
		//while(digitalRead(Button0)) doNothing();
	  while(1) {
				digitalWrite(LED0, HIGH);
				digitalWrite(LED1, HIGH);
				digitalWrite(LED2, HIGH);
				digitalWrite(LED3, HIGH);
				digitalWrite(LED4, HIGH);
				digitalWrite(LED5, HIGH);
				digitalWrite(LED6, HIGH);
				digitalWrite(LED7, HIGH);
				digitalWrite(LED8, HIGH);
				digitalWrite(LED9, HIGH);
				digitalWrite(LED10, HIGH);
				digitalWrite(LED11, HIGH);
				digitalWrite(LED12, HIGH);
				digitalWrite(LED13, HIGH);
				digitalWrite(LED14, HIGH);
			delay(1000);
				digitalWrite(LED0, LOW);
				digitalWrite(LED1, LOW);
				digitalWrite(LED2, LOW);
				digitalWrite(LED3, LOW);
				digitalWrite(LED4, LOW);
				digitalWrite(LED5, LOW);
				digitalWrite(LED6, LOW);
				digitalWrite(LED7, LOW);
				digitalWrite(LED8, LOW);
				digitalWrite(LED9, LOW);
				digitalWrite(LED10, LOW);
				digitalWrite(LED11, LOW);
				digitalWrite(LED12, LOW);
				digitalWrite(LED13, LOW);
				digitalWrite(LED14, LOW);
			delay(1000);
		}
}
void UPtester(void) {
		SysTime_Init();
	/*
		GPIO tst1 = initIO(PA4,OUTPUT);
		GPIO tst2 = initIO(PA6,OUTPUT);
		GPIO tst3 = initIO(PA7,OUTPUT);
		GPIO tst4 = initIO(PC5,OUTPUT);
		GPIO tst5 = initIO(PA5,OUTPUT);
		while(1) {
			digitalWrite(tst1, HIGH);
			digitalWrite(tst2, HIGH);
			digitalWrite(tst3, HIGH);
			digitalWrite(tst4, HIGH);
			digitalWrite(tst5, HIGH);
			delay_us(50);
			digitalWrite(tst1, LOW);
			digitalWrite(tst2, LOW);
			digitalWrite(tst3, LOW);
			digitalWrite(tst4, LOW);
			digitalWrite(tst5, LOW);
			delay_us(30);
		}*/
		initUSART(USART1, PB6, PB7, 9600);
		printfForUx(USART1);
		scanfForUx(USART1);
		printf("\rHellow World!!!!!!!!!!!!!!!!!!!!!!EL PSY CONGROO\r\n");
		
		GPIO Button0 = initIO(PC9, INPUT);
	  GPIO LED1 = initIO(PA3,OUTPUT);
		GPIO LED2 = initIO(PC4,OUTPUT);
		GPIO LED3 = initIO(PB10,OUTPUT);
		GPIO LED4 = initIO(PB11,OUTPUT);
		GPIO LED5 = initIO(PC13,OUTPUT);
		GPIO LED6 = initIO(PB4,OUTPUT);
		
		//while(digitalRead(Button0));
	
		
		char str[100];
		printf("\rEnter \"Start\" to begin\r\n");
		readLine(str);
		while(strcmp(str, "start")) readLine(str);
		int T = 100;
		while(1) {
			digitalWrite(LED1, HIGH);
			delay(T);
			digitalWrite(LED1, LOW);
			delay(T);
			
			digitalWrite(LED2, HIGH);
			delay(T);
			digitalWrite(LED2, LOW);
			delay(T);
					
			digitalWrite(LED3, HIGH);
			delay(T);
			digitalWrite(LED3, LOW);
			delay(T);

			digitalWrite(LED4, HIGH);
			delay(T);
			digitalWrite(LED4, LOW);
			delay(T);

			digitalWrite(LED6, HIGH);
			delay(T);
			digitalWrite(LED6, LOW);
			delay(T);
						
			digitalWrite(LED5, HIGH);
			delay(T);
			digitalWrite(LED5, LOW);
			delay(T);
		}
}
int main(void)
{
		UPtester();
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
