#ifndef USART_H
#define USART_H

void usart1_Configuration(u32 baudrate);
void usart2_Configuration(u32 baudrate);
//void TxUSART(char byte);
int PutChar (int ch);
int GetChar(void);
char inputChar(void);
int inputDigit(void);
void inputString(char target[]);
void inputDigits(int target);


#endif
