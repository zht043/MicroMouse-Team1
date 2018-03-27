#include "main.h"
#include "SysTime.h"
#include "GPIO.h"
#include "Initiation.h"
#include "Timer.h"
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
		SysClock_Tester();
		//PWM_Tester();
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
