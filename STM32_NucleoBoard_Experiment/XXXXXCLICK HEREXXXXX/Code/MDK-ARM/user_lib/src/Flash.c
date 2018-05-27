/**
  ******************************************************************************
  * @file    FLASH/FLASH_Program/main.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "Flash.h"

uint32_t flashCurrentAddress;


/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup FLASH_Program
  * @{
  */ 


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
	
void flashStartWriting(){
	
	FLASH_Unlock();
	
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	FLASH_EraseSector(FLASH_Sector_7, VoltageRange_3);
	flashCurrentAddress = ADDR_FLASH_SECTOR_7;
}

void flashWriteToSector(uint32_t w) {
	FLASH_ProgramWord(flashCurrentAddress, w);
	flashCurrentAddress += 4;
}


void flashFinishWriting() {
	FLASH_Lock();
}


void flashStartReading() {
	flashCurrentAddress = ADDR_FLASH_SECTOR_7;
  printf("Started reading!");
}


uint32_t flashReadFromSector() {
	
	uint32_t ret = *(__IO uint32_t*)flashCurrentAddress;
	printf("Returning: %d", ret);
	flashCurrentAddress += 4;
	return ret;
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

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
