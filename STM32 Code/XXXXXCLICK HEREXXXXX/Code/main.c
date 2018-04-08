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
		GPIO LED1 = initIO(PA9,OUTPUT);
		GPIO LED2 = initIO(PA10,OUTPUT);
		digitalWrite(LED1, HIGH);
		digitalWrite(LED2, HIGH);
		/*SysTime_Init();
	  GPIO LED0 = initIO(PA0,OUTPUT);
		GPIO Button0 = initIO(PA1, INPUT);
	  while(1) {
				if(!digitalRead(Button0))  
						digitalWrite(LED0, HIGH);
				else 
						digitalWrite(LED0, LOW);
		}*/
}
void SysClock_Tester(void) {
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
		initUSART(USART1, PA9, PA10, 9600);
		printfForUx(USART1);
	  scanfForUx(USART1);
		printf("EL PSY CONGROO <<<<<>>>>> Ich Liebe dich~\r\n");
		SPI1_init();
		SPI2_init();
		
	for(int i = 0; i < 10; i++) {
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI2, 10 - i);  //SPI2 -> SPI1
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI1, i); // SPI1 -> SPI2
		printf("SENT\r\n");
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
		char b = SPI_I2S_ReceiveData(SPI2);
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		char a = SPI_I2S_ReceiveData(SPI1);
		printf("SPI1 receives %d     SPI2 receives %d\r\n", a, b);
		
	}
}
int main(void)
{
		//initAlles();
	  GPIO_Tester();
		//SysClock_Tester();
		//PWM_Tester();
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
