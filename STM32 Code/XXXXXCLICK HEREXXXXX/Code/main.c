#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "SysTime.h"
#include "GPIO.h"
#include "Initiation.h"
#include "Timer.h"
#include "USART.h"
#include "SPI.h"
void initAlles() {
		SysTime_Init();
}
void GPIO_Tester(void) {
		SysTime_Init();
	  GPIO LED0 = initIO(PA0,OUTPUT);
		GPIO Button0 = initIO(PA1, INPUT);
	  while(1) {
				if(!digitalRead(Button0))  
						digitalWrite(LED0, HIGH);
				else 
						digitalWrite(LED0, LOW);
		}
}
void SysClock_Tester(void) {
		SysTime_Init();
		GPIO LED0 = initIO(PC0,OUTPUT);
		//GPIO Button0 = initIO(PA1, INPUT);
		//while(digitalRead(Button0)) doNothing();
	  while(1) {
				digitalWrite(LED0, HIGH);
				delay_us(10);
				digitalWrite(LED0, LOW);
				delay_us(10);
		}
}
void PWM_Tester(void) {
		SysTime_Init();

//ADVTIM Testing
		TIM pwm1 = initIO_TIM(TIMER1, PA8, Ch1);
		TIM pwm2 = initIO_TIM(TIMER1, PA9, Ch2);
	
//		TIM pwm1 = initIO_TIM(TIMER8, PC6, Ch1);
//	  TIM pwm2 = initIO_TIM(TIMER8, PC7, Ch2);
		
//NORTIM Testing	
//		TIM pwm1 = initIO_TIM(TIMER2, PA0, Ch1);
//	  TIM pwm2 = initIO_TIM(TIMER2, PA1, Ch2);
	
//		TIM pwm1 = initIO_TIM(TIMER3, PA6, Ch1);
//	  TIM pwm2 = initIO_TIM(TIMER3, PA7, Ch2);
	
//	  TIM pwm1 = initIO_TIM(TIMER4, PB6, Ch1);
//	  TIM pwm2 = initIO_TIM(TIMER4, PB7, Ch2);
	
//		TIM pwm1 = initIO_TIM(TIMER5, PA0, Ch1);
//	  TIM pwm2 = initIO_TIM(TIMER5, PA1, Ch2);

//    TIM pwm1 = initIO_TIM(TIMER9, PA2, Ch1);
//	  TIM pwm2 = initIO_TIM(TIMER9, PA3, Ch2);

//		No Use of TIMER10, 11 
		
//		TIM pwm1 = initIO_TIM(TIMER12, PB14, Ch1);
//	  TIM pwm2 = initIO_TIM(TIMER12, PB15, Ch2);
    
//		No Use of TIMER13, 14
		
		PWM_ON(pwm1.TIMERx,10000); //pwm frequency = 10khz
	
		while(1) {
			  setPWM(pwm1, 250);
				setPWM(pwm2, 750);
		}
}
void USART_Tester(void) {
	SysTime_Init();
	
	/*initUSART(USART1, PA9, PA10, 9600);
		printfForUx(USART1);
		scanfForUx(USART1);
	*/
	
	// Warning USART2 doesn't work, rest do
	//initUSART(USART2, PA2, PA3, 9600);
	//printfForUx(USART2);
	//scanfForUx(USART2);
	
	/*initUSART(USART3, PB10, PC5, 9600);
		printfForUx(USART3);
		scanfForUx(USART3);
	*/

	/*initUSART(UART4, PA0, PA1, 9600);
		printfForUx(UART4);
		scanfForUx(UART4);
	*/
	
	/*initUSART(UART5, PC12, PD2, 9600);
		printfForUx(UART5);
		scanfForUx(UART5);
	*/
	
	initUSART(USART6, PC6, PC7, 9600);
	printfForUx(USART6);
	scanfForUx(USART6);
	
	printf("EL PSY CONGROO <<<<<>>>>> Ich Liebe dich~\r\n");
	printf("Float = %.2f", (float)32.0);
	printf("Double = %.2f", (double)42.0);
	printf("Int = %d", -77);
	printf("Long = %ld", (long)2147483647);
	printf("Char = %c", 'y');
	
	char str[100];
	while(1) {
		readLine(str);
		printf("%s\r\n",str);
	}
}
void SPI_Tester(void) {
		SPI_init();
		while(1) {
				SPI_FLASH_SendByte(0x05);
		}
	
}
int main(void)
{
		//initAlles();
	  //GPIO_Tester();
		//SysClock_Tester();
		PWM_Tester();
		//USART_Tester();
		//SPI_Tester();
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










