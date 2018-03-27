#include "SPI.h"
//SPI
#define FLASH_SPI                           SPI1  
#define FLASH_SPI_CLK                       RCC_APB2Periph_SPI1  
#define FLASH_SPI_CLK_INIT                  RCC_APB1PeriphClockCmd  
//SCK  
#define FLASH_SPI_SCK_PIN                   GPIO_Pin_5  
#define FLASH_SPI_SCK_GPIO_PORT             GPIOA  
#define FLASH_SPI_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOA  
#define FLASH_SPI_SCK_PINSOURCE             GPIO_PinSource5 
#define FLASH_SPI_SCK_AF                    GPIO_AF_SPI1 
//MISO 
#define FLASH_SPI_MISO_PIN                  GPIO_Pin_6 
#define FLASH_SPI_MISO_GPIO_PORT            GPIOA 
#define FLASH_SPI_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOA 
#define FLASH_SPI_MISO_PINSOURCE            GPIO_PinSource6 
#define FLASH_SPI_MISO_AF                   GPIO_AF_SPI1 
//MOSI 
#define FLASH_SPI_MOSI_PIN                  GPIO_Pin_7 
#define FLASH_SPI_MOSI_GPIO_PORT            GPIOA 
#define FLASH_SPI_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOA
#define FLASH_SPI_MOSI_PINSOURCE            GPIO_PinSource7 
#define FLASH_SPI_MOSI_AF                    GPIO_AF_SPI1 
//CS(NSS)
#define FLASH_CS_PIN                         GPIO_Pin_4 
#define FLASH_CS_GPIO_PORT                   GPIOA 
#define FLASH_CS_GPIO_CLK                    RCC_AHB1Periph_GPIOA 
  
// CS(NSS) 
#define SPI_FLASH_CS_LOW()      GPIO_ResetBits(FLASH_CS_GPIO_PORT, FLASH_CS_PIN)
//CS(NSS)
#define SPI_FLASH_CS_HIGH()     GPIO_SetBits(FLASH_CS_GPIO_PORT, FLASH_CS_PIN) 
void SPI_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure; 
    RCC_AHB1PeriphClockCmd (FLASH_SPI_SCK_GPIO_CLK | FLASH_SPI_MISO_GPIO_CLK| 
														FLASH_SPI_MOSI_GPIO_CLK|FLASH_CS_GPIO_CLK, ENABLE);
														FLASH_SPI_CLK_INIT(FLASH_SPI_CLK, ENABLE); 
		GPIO_PinAFConfig(FLASH_SPI_SCK_GPIO_PORT,FLASH_SPI_SCK_PINSOURCE, 
										 FLASH_SPI_SCK_AF); 
		GPIO_PinAFConfig(FLASH_SPI_MISO_GPIO_PORT,FLASH_SPI_MISO_PINSOURCE, 
										 FLASH_SPI_MISO_AF); 
		GPIO_PinAFConfig(FLASH_SPI_MOSI_GPIO_PORT,FLASH_SPI_MOSI_PINSOURCE, 
										 FLASH_SPI_MOSI_AF);
		GPIO_InitStructure.GPIO_Pin = FLASH_SPI_SCK_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
		GPIO_Init(FLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure); 
		GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO_PIN; 
		GPIO_Init(FLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure); 
		GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MOSI_PIN; 
    GPIO_Init(FLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure); 
		GPIO_InitStructure.GPIO_Pin = FLASH_CS_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_Init(FLASH_CS_GPIO_PORT, &GPIO_InitStructure);
		SPI_FLASH_CS_HIGH(); 
		
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
		SPI_Init(FLASH_SPI, &SPI_InitStructure);
		SPI_Cmd(FLASH_SPI, ENABLE);		
}
#define Dummy_Byte 0xFF 
uint8_t SPI_FLASH_SendByte(uint8_t byte)
{
		//SPITimeout = SPIT_FLAG_TIMEOUT;
		while(SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET)
		{
				//if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(0);
		}
		SPI_I2S_SendData(FLASH_SPI, byte);
		//SPITimeout = SPIT_FLAG_TIMEOUT;
		while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		{
				//if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);
		}
		return SPI_I2S_ReceiveData(FLASH_SPI);
} 
uint8_t SPI_FLASH_ReadByte(void)
{  
		return (SPI_FLASH_SendByte(Dummy_Byte));
}
