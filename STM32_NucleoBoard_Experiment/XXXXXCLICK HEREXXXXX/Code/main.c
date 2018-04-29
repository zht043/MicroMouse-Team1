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
#include "Stack.h"
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

void SysClock_Tester() {
		SysTime_Init();
		GPIO LED1 = initIO(PA9,OUTPUT);
		GPIO LED2 = initIO(PA10,OUTPUT);
		while(1) {
				digitalWrite(LED1, HIGH);
				delay(100);
				digitalWrite(LED1, LOW);
				delay(100);
				digitalWrite(LED2, HIGH);
				delay(100);
				digitalWrite(LED2, LOW);
				delay(100);
		}
}
void PWM_Tester(void) {
		SysTime_Init();
//ADVTIM Testing
		TIM pwm1 = initIO_TIM(TIMER1, PA8, Ch1);
		TIM pwm2 = initIO_TIM(TIMER1, PA9, Ch2);
//		TIM pwm1 = initIO_TIM(TIMER8, PC6, Ch1);
//	  TIM pwm2 = initIO_TIM(TIMER8, PC7, Ch2);
//NORTIM Testing	
//		TIM pwm1 = initIO_TIM(TIMER2, PA0, Ch1);
//	  TIM pwm2 = initIO_TIM(TIMER2, PA1, Ch2);
	
//		TIM pwm1 = initIO_TIM(TIMER3, PA6, Ch1);
//	  TIM pwm2 = initIO_TIM(TIMER3, PA7, Ch2);
	
//	  TIM pwm1 = initIO_TIM(TIMER4, PB6, Ch1);
//	  TIM pwm2 = initIO_TIM(TIMER4, PB7, Ch2);

//		TIM pwm1 = initIO_TIM(TIMER5, PA0, Ch1);
//	  TIM pwm2 = initIO_TIM(TIMER5, PA1, Ch2);

//    TIM pwm1 = initIO_TIM(TIMER9, PA2, Ch1);
//	  TIM pwm2 = initIO_TIM(TIMER9, PA3, Ch2);

//		No Use of TIMER10, 11 

//		TIM pwm1 = initIO_TIM(TIMER12, PB14, Ch1);
//	  TIM pwm2 = initIO_TIM(TIMER12, PB15, Ch2);

//		No Use of TIMER13, 14
		PWM_ON(pwm1.TIMERx,10000); //pwm frequency = 10khz
		while(1) {
			  setPWM(pwm1, 250);
				setPWM(pwm2, 750);
		}
}
void USART_Tester(void) {
	SysTime_Init();
	initUSART(USART1, PA9, PA10, 9600);
	printfForUx(USART1);
	scanfForUx(USART1);
	printf("a");
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
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) {
	//		printf("SPI2 status = Reset");
		}
					printf("SPI2 status != Reset");

		char b = SPI_I2S_ReceiveData(SPI2);
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		char a = SPI_I2S_ReceiveData(SPI1);
		printf("SPI1 receives %d     SPI2 receives %d\r\n", a, b);
		
	}
}
static void Stack_Tester(void){
	SystemInit();
	initUSART(USART2, PA2, PA3, 9600);
	printfForUx(USART2);
	scanfForUx(USART2);
	printf("\rEL PSY CONGROO <<<<<>>>>> Ich Liebe dich~\r\n");
	Stack* stack = newStack(MAX);
	static int store[MAX];
	if(isEmpty(store, stack)){
		printf("\rStack is Empty\r\n");
	}
	for(int i = 1;i <= MAX;i++){
 		push(store, stack, i);
	}
	printf("\rSize of StackNode is %d\r\n", sizeof(stack));
	printf("\rStack is pushed \r\n");
	while(!isEmpty(store, stack)){
		printf("\rStack has %d \r\n", peek(store, stack));
		pop(store, stack);
	}
	if(isEmpty(store, stack)){
		printf("\rStack is Empty\r\n");
	}
}

/*static void Checkstack_Tester(void){
	//int ar[100]
	//for loop access memory, each value 2 * i
	//print memory
	SystemInit();
	initUSART(USART2, PA2, PA3, 9600);
	printfForUx(USART2);
	scanfForUx(USART2);
	printf("\rEL PSY CONGROO <<<<<>>>>> Ich Liebe dich~\r\n");
	const int maxsize = 2000;
	static int arr[maxsize];
	for (int i = 0; i < maxsize; i++){
		arr[i] = i * 2;
	}
	for (int i = 0; i < maxsize; i ++){
		printf("\rWe have %d\n\r", arr[i]);
	}
	printf("\rWe are done\n\r");
}*/
void Floodfill_Tester(void){
}
int main(void)
{
		//initAlles();
	  //GPIO_Tester();
		//SysClock_Tester();
		//PWM_Tester();
		//USART_Tester();
		//SPI_Tester();
	  Stack_Tester();
	  //Checkstack_Tester();  
	  //Floodfill_Tester();
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
