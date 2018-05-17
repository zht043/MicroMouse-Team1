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
#include "Motor.h"
int main(void)
{
		
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
