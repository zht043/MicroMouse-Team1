#include "GPIO.h"
void initGPIO(GPIO* obj) {
		RCC_AHB1PeriphClockCmd(obj->RCC_CMD, ENABLE);
	  GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin   = obj->Pin;
		GPIO_InitStructure.GPIO_Mode  = obj->Mode; 
		GPIO_InitStructure.GPIO_OType = obj->OType; 
		GPIO_InitStructure.GPIO_PuPd  = obj->PuPd; 
		GPIO_InitStructure.GPIO_Speed = obj->Speed; 
		GPIO_Init(obj->GPIOx, &GPIO_InitStructure);
}
GPIO Pxx_decoder(uint8_t Pxx) {
		GPIO obj;		
		switch((Pxx / 0x10) % 0x10) {
			case A:
				obj.GPIOx = GPIOA;
				obj.RCC_CMD = RCC_AHB1Periph_GPIOA; 
				break;
			case B:
				obj.GPIOx = GPIOB;
				obj.RCC_CMD = RCC_AHB1Periph_GPIOB; 
				break;
			case C:
				obj.GPIOx = GPIOC;
				obj.RCC_CMD = RCC_AHB1Periph_GPIOC; 
				break;
			case D:
				obj.GPIOx = GPIOD;
				obj.RCC_CMD = RCC_AHB1Periph_GPIOD; 
				break;
			case E:
				obj.GPIOx = GPIOE;
				obj.RCC_CMD = RCC_AHB1Periph_GPIOE; 
				break;
			case F: 
				obj.GPIOx = GPIOF;
				obj.RCC_CMD = RCC_AHB1Periph_GPIOF; 
				break;
			case G:
				obj.GPIOx = GPIOG;
				obj.RCC_CMD = RCC_AHB1Periph_GPIOG; 
				break;
			case H: 
				obj.GPIOx = GPIOH;
				obj.RCC_CMD = RCC_AHB1Periph_GPIOH; 
				break;
			/*F405 doesn't have GPIO group 'I'
			case I: 
				obj.GPIOx = GPIOI;
				obj.RCC_CMD = RCC_AHB1Periph_GPIOI; 
				break;*/
			default: break;
		}
		switch(Pxx % 0x10) {
			case 0x00: obj.Pin = 
				GPIO_Pin_0;
				obj.GPIO_PinSource = GPIO_PinSource0;
				break;
			case 0x01: 
				obj.Pin = GPIO_Pin_1; 
				obj.GPIO_PinSource = GPIO_PinSource1;
				break;
			case 0x02: 
				obj.Pin = GPIO_Pin_2; 
				obj.GPIO_PinSource = GPIO_PinSource2;
				break;
			case 0x03: 
				obj.Pin = GPIO_Pin_3; 
				obj.GPIO_PinSource = GPIO_PinSource3;
				break;
			case 0x04: 
				obj.Pin = GPIO_Pin_4; 
				obj.GPIO_PinSource = GPIO_PinSource4;
				break;
			case 0x05: 
				obj.Pin = GPIO_Pin_5; 
				obj.GPIO_PinSource = GPIO_PinSource5;
				break;
			case 0x06: 
				obj.Pin = GPIO_Pin_6; 
				obj.GPIO_PinSource = GPIO_PinSource6;
				break;
			case 0x07: 
				obj.Pin = GPIO_Pin_7; 
				obj.GPIO_PinSource = GPIO_PinSource7;
				break;
			case 0x08: 
				obj.Pin = GPIO_Pin_8; 
			  obj.GPIO_PinSource = GPIO_PinSource8;
			  break;
			case 0x09: 
				obj.Pin = GPIO_Pin_9; 
			  obj.GPIO_PinSource = GPIO_PinSource9;
			  break;
			case 0x0A: 
				obj.Pin = GPIO_Pin_10; 
			  obj.GPIO_PinSource = GPIO_PinSource10;
				break;
			case 0x0B: 
				obj.Pin = GPIO_Pin_11; 
				obj.GPIO_PinSource = GPIO_PinSource11;
				break;
			case 0x0C: 
				obj.Pin = GPIO_Pin_12; 
				obj.GPIO_PinSource = GPIO_PinSource12;
				break;
			case 0x0D: 
				obj.Pin = GPIO_Pin_13; 
				obj.GPIO_PinSource = GPIO_PinSource13;
				break;
			case 0x0E: 
				obj.Pin = GPIO_Pin_14; 
				obj.GPIO_PinSource = GPIO_PinSource14;
				break;
			case 0x0F: 
				obj.Pin = GPIO_Pin_15; 
				obj.GPIO_PinSource = GPIO_PinSource15;
				break;
			default : break;
		}
		return obj;
}
GPIO initIO(uint8_t Pxx, uint8_t Mode) {
	  GPIO obj;
		obj = Pxx_decoder(Pxx);
		RCC_AHB1PeriphClockCmd(obj.RCC_CMD, ENABLE);
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin   = obj.Pin;
		switch(Mode) {
			case OUTPUT: 
				GPIO_InitStructure.GPIO_Mode  = OUT; 
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
				obj.Mode = OUT;
				obj.OType = GPIO_OType_PP;
				break;
			case INPUT:  
				GPIO_InitStructure.GPIO_Mode  = IN;  
				GPIO_InitStructure.GPIO_PuPd  = NOPULL;
				obj.Mode = IN;
				obj.PuPd = NOPULL;
				break;
			case INPUT_PULLUP: 
				GPIO_InitStructure.GPIO_Mode  = IN;  
				GPIO_InitStructure.GPIO_PuPd  = PULLUP;
				obj.Mode = IN;
				obj.PuPd = PULLUP;
				break;
			case INPUT_PULLDOWN: 
				GPIO_InitStructure.GPIO_Mode  = IN;  
				GPIO_InitStructure.GPIO_PuPd  = PULLDOWN;
				obj.Mode = IN;
				obj.PuPd = PULLDOWN;
				break;
			default: break;
		}
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		obj.Speed = GPIO_Speed_100MHz;
		GPIO_Init(obj.GPIOx, &GPIO_InitStructure);
		return obj;
}
void digitalWrite(GPIO port, uint8_t state) {
		if(state == HIGH) GPIO_SetBits(port.GPIOx, port.Pin);
	  else if(state == LOW)  GPIO_ResetBits(port.GPIOx, port.Pin);
}
uint8_t digitalRead(GPIO port) {
	  return GPIO_ReadInputDataBit(port.GPIOx, port.Pin);
}
