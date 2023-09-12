#include "SPI.h"

#define USER_TIMEOUT                    ((uint32_t)0x64)

#define SPIx_DMA                       DMA1
  #define SPIx_DMA_CLK                   RCC_AHB1Periph_DMA1
  #define SPIx_TX_DMA_CHANNEL            DMA_Channel_0
  #define SPIx_TX_DMA_STREAM             DMA1_Stream4
  #define SPIx_TX_DMA_FLAG_TCIF          DMA_FLAG_TCIF4
  #define SPIx_RX_DMA_CHANNEL            DMA_Channel_0
  #define SPIx_RX_DMA_STREAM             DMA1_Stream3
  #define SPIx_RX_DMA_FLAG_TCIF          DMA_FLAG_TCIF3
		
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
void SPI1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 	
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_SPI1, ENABLE);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
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
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
}
void SPI2_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 	
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_SPI2, ENABLE);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource2,GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource3,GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_SPI2);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
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
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_Cmd(SPI2, ENABLE);
}

#define Dummy_Byte 0xFF 
uint8_t SPI_SendByte(uint8_t byte, SPI_TypeDef * SPIx)
{
		//SPITimeout = SPIT_FLAG_TIMEOUT;
		while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)
		{
				//if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(0);
		}
		SPI_I2S_SendData(SPIx, byte);
		//SPITimeout = SPIT_FLAG_TIMEOUT;
		
		while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)
		{
				//if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);
		}
		return SPI_I2S_ReceiveData(SPIx);
} 
uint8_t SPI_ReadByte(SPI_TypeDef * SPIx)
{  
		return (SPI_SendByte(Dummy_Byte, SPIx));
}
