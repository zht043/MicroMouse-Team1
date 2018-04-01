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
		TIM pwm1 = initIO_TIM(TIMER1, PA8);
		TIM pwm2 = initIO_TIM(TIMER1, PA9);
		PWM_ON(pwm1.TIMERx,10000); //pwm frequency = 10khz
		while(1) {
			  setPWM(pwm1, 666);
				setPWM(pwm2, 333);
		}
}
void USART_Tester(void) {
	SysTime_Init();
	initUSART(USART1, PA9, PA10, 9600);
	printfForUx(USART1);
	scanfForUx(USART1);
	printf("EL PSY CONGROO <<<<<>>>>> Ich Liebe dich~\r\n");
	char str[100];
	while(1) {
		readLine(str);
		printf("%s\r\n",str);
	}
}
void SPI_Tester(void) {
		SysTime_Init();
		//initUSART(USART1, PA9, PA10, 9600);
		//printfForUx(USART1);
	  //scanfForUx(USART1);
		//printf("EL PSY CONGROO <<<<<>>>>> Ich Liebe dich~\r\n");
		SPI_init();
		GPIO LED = initIO(PD13, OUTPUT);
		digitalWrite(LED, HIGH);
		delay(300);
		digitalWrite(LED, LOW);
		delay(300);
		digitalWrite(LED, HIGH);
		delay(300);
		digitalWrite(LED, LOW);
		delay(300);
		digitalWrite(LED, HIGH);
		delay(1000);
		while(1) {
			digitalWrite(LED, LOW);
			SPI_FLASH_SendByte(0x01);
			delay(100);
			digitalWrite(LED, HIGH);
		}
		while(1) {
			char c = SPI_FLASH_ReadByte();
			printf("%c",c);
		}
}
int main(void)
{
		//initAlles();
	  //GPIO_Tester();
		//SysClock_Tester();
		//PWM_Tester();
		//USART_Tester();
		SPI_Tester();
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
