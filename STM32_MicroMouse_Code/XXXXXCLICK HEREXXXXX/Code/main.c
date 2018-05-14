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
	GPIO_InitTypeDef GPIO_InitStructure; 	
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_SPI2, ENABLE);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/*
	GPIO_InitStructure.GPIO_Pin = FLASH_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(FLASH_CS_GPIO_PORT, &GPIO_InitStructure);*/
	//SPI_FLASH_CS_HIGH(); 
	SPI_InitTypeDef  SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_Cmd(SPI2, ENABLE);
	
	while(1) { 
		SPI_SendByte('F',SPI2); 
		//delay(1000);
	}
	/*
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
		}*/
}
void UPtestor(void) {
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
		/*GPIO f1 = initIO(PB6, OUTPUT);
		GPIO f2 = initIO(PB7, OUTPUT);
		while(1) {
			digitalWrite(f1,HIGH); digitalWrite(f2, LOW); delay_us(10); 
			digitalWrite(f1,LOW); digitalWrite(f2, HIGH); delay_us(10); 
		}*/
			
		
		initUSART(USART1, PB6, PB7, 9600);
		printfForUx(USART1);
		scanfForUx(USART1);
		//while(1) printf("%d",2);
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
		GPIO_InitTypeDef GPIO_InitStructure; 	
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_SPI2, ENABLE);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/*
	GPIO_InitStructure.GPIO_Pin = FLASH_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(FLASH_CS_GPIO_PORT, &GPIO_InitStructure);*/
	//SPI_FLASH_CS_HIGH(); 
	SPI_InitTypeDef  SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_Cmd(SPI2, ENABLE);
	int r;
	while(1) { 
			r = SPI_ReadByte(SPI2);
			printf("\r%d\r\n", r);
	}
}

int main(void)
{
		UPtestor();
		//DownTester();
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
