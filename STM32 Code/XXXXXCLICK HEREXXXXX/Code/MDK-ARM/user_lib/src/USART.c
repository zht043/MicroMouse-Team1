#include "USART.h"
USART USART_decoder(USART_TypeDef* USARTx) {
		USART U;
		U.USARTx = USARTx;
		if(USARTx == USART1) {
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
				U.USARTx_AF = GPIO_AF_USART1;
		}
		return U;
}
void initUSART(USART_TypeDef* USARTx, uint8_t TX_Pxx, uint8_t RX_Pxx, uint32_t USARTx_BAUDRATE)  
{  
		GPIO_InitTypeDef GPIO_InitStructure;  
		USART_InitTypeDef USART_InitStructure;
		GPIO TX;
		TX = Pxx_decoder(TX_Pxx);
		GPIO RX;
		RX = Pxx_decoder(RX_Pxx);
	  USART U;
		U = USART_decoder(USARTx);
		RCC_AHB1PeriphClockCmd(TX.RCC_CMD, ENABLE);
		RCC_AHB1PeriphClockCmd(RX.RCC_CMD, ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz ;
		 
		GPIO_InitStructure.GPIO_Pin =  TX.Pin; 
		GPIO_Init(TX.GPIOx, &GPIO_InitStructure); 
	
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
		GPIO_InitStructure.GPIO_Pin =  RX.Pin; 
		GPIO_Init(RX.GPIOx, &GPIO_InitStructure);
	
    GPIO_PinAFConfig(TX.GPIOx, TX.GPIO_PinSource, U.USARTx_AF); 
		GPIO_PinAFConfig(RX.GPIOx, RX.GPIO_PinSource, U.USARTx_AF); 
		
		USART_InitStructure.USART_BaudRate = USARTx_BAUDRATE; 
		USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
    USART_Init(USARTx, &USART_InitStructure);
		/*
		NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
    NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);*/		
	  USART_Cmd(USARTx, ENABLE); 
}
USART_TypeDef* prtUSARTx;
void printfForUx(USART_TypeDef* USARTx) {
		prtUSARTx = USARTx;
}
int fputc(int ch, FILE *f)  
{ 
    USART_SendData(prtUSARTx, (uint8_t) ch);
    while (USART_GetFlagStatus(prtUSARTx, USART_FLAG_TXE) == RESET) ;  
    return (ch); 
} 
USART_TypeDef* scnUSARTx;
void scanfForUx(USART_TypeDef* USARTx) {
		scnUSARTx = USARTx;
}
int fgetc(FILE *f)
{
		while(USART_GetFlagStatus(scnUSARTx, USART_FLAG_RXNE) == RESET);
		return (int)USART_ReceiveData(scnUSARTx);
}
void readLine(char* str) {
		int i = 0;
		str[i] = getchar();
		while(str[i++] != '\r') str[i] = getchar();
		str[i] = '\0';
			
}
