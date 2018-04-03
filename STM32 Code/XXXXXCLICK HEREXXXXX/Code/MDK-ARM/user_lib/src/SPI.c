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


#define USER_TIMEOUT                    ((uint32_t)0x64)

#define BUFFERSIZE                       100
uint8_t aTxBuffer[BUFFERSIZE] = "SPI Master/Slave : Communication between two SPI using DMA";
__IO uint8_t aRxBuffer [BUFFERSIZE];
__IO uint8_t ubRxIndex = 0;
__IO uint8_t ubTxIndex = 0;
__IO uint32_t TimeOut = 0;


#define countof(a)   (sizeof(a) / sizeof(*(a)))
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
static TestStatus Buffercmp(uint8_t* pBuffer1, __IO uint8_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }
    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;
}
#define SPIx_DMA                       DMA1
  #define SPIx_DMA_CLK                   RCC_AHB1Periph_DMA1
  #define SPIx_TX_DMA_CHANNEL            DMA_Channel_0
  #define SPIx_TX_DMA_STREAM             DMA1_Stream4
  #define SPIx_TX_DMA_FLAG_TCIF          DMA_FLAG_TCIF4
  #define SPIx_RX_DMA_CHANNEL            DMA_Channel_0
  #define SPIx_RX_DMA_STREAM             DMA1_Stream3
  #define SPIx_RX_DMA_FLAG_TCIF          DMA_FLAG_TCIF3
void SPI1_init(void)
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
		
		SPI_I2S_DeInit(FLASH_SPI);
		SPI_InitTypeDef  SPI_InitStructure;
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 	
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
		SPI_InitStructure.SPI_CRCPolynomial = 7;
		SPI_Init(FLASH_SPI, &SPI_InitStructure);
		
/*
	DMA_DeInit(SPIx_TX_DMA_STREAM);
  DMA_DeInit(SPIx_RX_DMA_STREAM);
	
  DMA_InitTypeDef DMA_InitStructure;
  
  DMA_InitStructure.DMA_BufferSize = BUFFERSIZE ;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable ;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull ;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single ;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) (&(FLASH_SPI->DR)) ;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  
  DMA_InitStructure.DMA_Channel = SPIx_TX_DMA_CHANNEL ;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral ;
  DMA_InitStructure.DMA_Memory0BaseAddr =(uint32_t)aTxBuffer ;
  DMA_Init(SPIx_TX_DMA_STREAM, &DMA_InitStructure);
 
  DMA_InitStructure.DMA_Channel = SPIx_RX_DMA_CHANNEL ;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory ;
  DMA_InitStructure.DMA_Memory0BaseAddr =(uint32_t)aRxBuffer ; 
  DMA_Init(SPIx_RX_DMA_STREAM, &DMA_InitStructure);
	
	DMA_Cmd(SPIx_TX_DMA_STREAM,ENABLE);

  DMA_Cmd(SPIx_RX_DMA_STREAM,ENABLE);  
  SPI_I2S_DMACmd(FLASH_SPI, SPI_I2S_DMAReq_Tx, ENABLE);
  SPI_I2S_DMACmd(FLASH_SPI, SPI_I2S_DMAReq_Rx, ENABLE);*/
	SPI_Cmd(FLASH_SPI, ENABLE);	
}
void SPI2_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure; 
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOB, ENABLE);
		
		GPIO_PinAFConfig(GPIOC, , 
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
		
		SPI_I2S_DeInit(FLASH_SPI);
		SPI_InitTypeDef  SPI_InitStructure;
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 	
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
		SPI_InitStructure.SPI_CRCPolynomial = 7;
		SPI_Init(FLASH_SPI, &SPI_InitStructure);
	SPI_Cmd(FLASH_SPI, ENABLE);	
}
#define Dummy_Byte 0xFF 
uint8_t SPI1_FLASH_SendByte(uint8_t byte)
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
uint8_t SPI1_FLASH_ReadByte(void)
{  
		return (SPI1_FLASH_SendByte(Dummy_Byte));
}
