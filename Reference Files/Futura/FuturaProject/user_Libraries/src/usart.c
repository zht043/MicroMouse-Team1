#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "delay.h"


/* USARTx configured as follow:
	- BaudRate = 5250000 baud
	   - Maximum BaudRate that can be achieved when using the Oversampling by 8
		 is: (USART APB Clock / 8)
		 Example:
			- (USART3 APB1 Clock / 8) = (42 MHz / 8) = 5250000 baud
			- (USART1 APB2 Clock / 8) = (84 MHz / 8) = 10500000 baud
	   - Maximum BaudRate that can be achieved when using the Oversampling by 16
		 is: (USART APB Clock / 16)
		 Example: (USART3 APB1 Clock / 16) = (42 MHz / 16) = 2625000 baud
		 Example: (USART1 APB2 Clock / 16) = (84 MHz / 16) = 5250000 baud
	- Word Length = 8 Bits
	- one Stop Bit
	- No parity
	- Hardware flow control disabled (RTS and CTS signals)
	- Receive and transmit enabled
*/


void usart1_Configuration(u32 baudrate)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  USART_ClockInitTypeDef USART_ClockInitstructure;

//   /* Enable GPIOB clock */
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  /* Enable USART1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//usart1 is on APB2 at 84Mhz max, usart2,3,6 are on APB1 at 42Mhz max

  /* Connect PXx to USARTx_Tx*/
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

  /* Connect PXx to USARTx_Rx*/
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

  /* Configure USART as alternate function  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
                                   //  Tx           Rx     
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_OverSampling8Cmd(USART1, ENABLE);

  USART_InitStructure.USART_BaudRate   = baudrate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits   = USART_StopBits_1;
  USART_InitStructure.USART_Parity     = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode       =  USART_Mode_Rx | USART_Mode_Tx;

/* USART Clock Initialization  */
  USART_ClockInitstructure.USART_Clock   = USART_Clock_Disable ;
  USART_ClockInitstructure.USART_CPOL    = USART_CPOL_High ;
  USART_ClockInitstructure.USART_LastBit = USART_LastBit_Disable;
  USART_ClockInitstructure.USART_CPHA    = USART_CPHA_1Edge;

  /* USART configuration */
  USART_Init(USART1, &USART_InitStructure);
  USART_ClockInit(USART1, &USART_ClockInitstructure);

  /* Enable USART */
  USART_Cmd(USART1, ENABLE);
}



void usart2_Configuration(u32 baudrate)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  USART_ClockInitTypeDef USART_ClockInitstructure;

  /* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  /* Enable USART clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//usart1 is on APB2 at 84Mhz max, usart2,3,6 are on APB1 at 42Mhz max

  /* Connect PXx to USARTx_Tx*/
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

  /* Connect PXx to USARTx_Rx*/
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

  /* Configure USART as alternate function  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
                                   //  Tx           Rx     
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_OverSampling8Cmd(USART2, ENABLE);

  USART_InitStructure.USART_BaudRate   = baudrate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits   = USART_StopBits_1;
  USART_InitStructure.USART_Parity     = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode       =  USART_Mode_Rx | USART_Mode_Tx;

/* USART Clock Initialization  */
  USART_ClockInitstructure.USART_Clock   = USART_Clock_Disable ;
  USART_ClockInitstructure.USART_CPOL    = USART_CPOL_High ;
  USART_ClockInitstructure.USART_LastBit = USART_LastBit_Disable;
  USART_ClockInitstructure.USART_CPHA    = USART_CPHA_1Edge;

  /* USART configuration */
  USART_Init(USART2, &USART_InitStructure);
  USART_ClockInit(USART2, &USART_ClockInitstructure);

  /* Enable USART */
  USART_Cmd(USART2, ENABLE);
}

/*
void TxUSART(char byte)
{
   while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
   USART_SendData(USART2, (uint8_t)byte);
}
*/

#pragma import(__use_no_semihosting)  

struct __FILE { int handle;};
FILE __stdout;
FILE __stdin;
_sys_exit(int x)  
{  
x = x;  
}   

int fputc(int ch, FILE *f) 
{ 
	//ITM_SendChar(ch);
	USART_SendData(USART1, (u8)ch); 
    //USART_SendData(USART2, (u8)ch); 	
    // or USART2->DR = (u8) ch; 
	
    /* Loop until the end of transmission */ 
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 	
    return ch; 
} 

int fgetc(FILE *f)
{
  u16 temp;
 
  /* Loop until the end of reception */
  while(!(USART1->SR & USART_SR_RXNE));
  /* Read a character from the USART */
  temp = (u16)(USART1->DR & (u16)0x01FF);
 
  return temp;
}

int PutChar (int ch)
{
//   if (!usart_enabled) {
//     return EOF;
//   }
  while (USART_GetFlagStatus (USART1, USART_FLAG_TXE) == RESET);
  USART_SendData (USART1, ch);
  return (ch);
}

 int GetChar(void)  
{
	//delay_ms(0);
	printf("\r\npress any key to continue...\r\n\r\n");	
	while (USART_GetFlagStatus (USART1, USART_FLAG_RXNE) == RESET);
    //printf("%d\r\n",(USART_ReceiveData (USART1)&0xFF));
	return ( (int) (USART_ReceiveData (USART1)&0xFF) );
} 

char inputChar(void)
{
	printf("please enter a charactor...\r\n");
	while (USART_GetFlagStatus (USART1, USART_FLAG_RXNE) == RESET);
	printf("%c\r\n", USART_ReceiveData(USART1));
	return USART_ReceiveData(USART1);
}

int inputDigit(void)
{
	printf("please enter a digit...\r\n");
	while (USART_GetFlagStatus (USART1, USART_FLAG_RXNE) == RESET);
	printf("%d\r\n", ((int)USART_ReceiveData(USART1)-48));
	return ((int)USART_ReceiveData(USART1)-48);
}



//string input test
void inputString(char target[])
{
	char uiTemp[20];

	printf("Press %s to Continue... :",target); 
	scanf("%s",uiTemp);
	printf("%s\r\n",uiTemp);
	while((strcmp(uiTemp, target) != 0))// && (uiTemp != 'C'))
	{
		
		printf("Invalid input, press %s to Continue... :", target); 
		scanf("%s",uiTemp);
		printf("%s\r\n",uiTemp);
	}
}
	



//digits input test
void inputDigits(int target)
{
    int uiTemp;
	printf("Press %d to Continue... :", target); 
	scanf("%d",&uiTemp);
	printf("%d\r\n",uiTemp);
	while(uiTemp != target)// && (uiTemp != 'C'))
	{
		
		printf("Invalid input, press %d to Continue... :",  target); 
		scanf("%d",&uiTemp);
		printf("%d\r\n",uiTemp);
	}
}
