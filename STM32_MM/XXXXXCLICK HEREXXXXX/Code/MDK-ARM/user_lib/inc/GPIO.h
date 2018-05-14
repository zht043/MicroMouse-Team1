#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define HIGH 0x0001
#define LOW  0x0000
#define PULLUP    GPIO_PuPd_UP
#define PULLDOWN  GPIO_PuPd_DOWN
#define NOPULL    GPIO_PuPd_NOPULL
#define OUT 	  GPIO_Mode_OUT
#define IN     GPIO_Mode_IN
#define OUTPUT (uint8_t)0x00
#define INPUT  (uint8_t)0x01
#define INPUT_PULLUP (uint8_t)0x02
#define INPUT_PULLDOWN (uint8_t)0x03
typedef struct 
{
		uint32_t          RCC_CMD;
	  uint16_t          Pin;
	  GPIOMode_TypeDef  Mode;
	  GPIOOType_TypeDef OType; 
		GPIOPuPd_TypeDef  PuPd; 
		GPIOSpeed_TypeDef Speed; 
		GPIO_TypeDef*     GPIOx;
		uint8_t           GPIO_PinSource;
}GPIO;

void initGPIO(GPIO* obj);
GPIO initIO(uint8_t Pxx, uint8_t Mode);
void digitalWrite(GPIO port, uint8_t state);
uint8_t digitalRead(GPIO port);
GPIO Pxx_decoder(uint8_t Pxx);
#define A 0x00
#define B 0x01
#define C 0x02
#define D 0x03
#define E 0x04
#define F 0x05
#define G 0x06
#define H 0x07
#define I 0x08

#define PA0  0x00
#define PA1  0x01
#define PA2  0x02
#define PA3  0x03
#define PA4  0x04
#define PA5  0x05
#define PA6  0x06
#define PA7  0x07
#define PA8  0x08
#define PA9  0x09
#define PA10 0x0A
#define PA11 0x0B
#define PA12 0x0C
#define PA13 0x0D
#define PA14 0x0E
#define PA15 0x0F

#define PB0  0x10
#define PB1  0x11
#define PB2  0x12
#define PB3  0x13
#define PB4  0x14
#define PB5  0x15
#define PB6  0x16
#define PB7  0x17
#define PB8  0x18
#define PB9  0x19
#define PB10 0x1A
#define PB11 0x1B
#define PB12 0x1C
#define PB13 0x1D
#define PB14 0x1E
#define PB15 0x1F

#define PC0  0x20
#define PC1  0x21
#define PC2  0x22
#define PC3  0x23
#define PC4  0x24
#define PC5  0x25
#define PC6  0x26
#define PC7  0x27
#define PC8  0x28
#define PC9  0x29
#define PC10 0x2A
#define PC11 0x2B
#define PC12 0x2C
#define PC13 0x2D
#define PC14 0x2E
#define PC15 0x2F

#define PD0  0x30
#define PD1  0x31
#define PD2  0x32
#define PD3  0x33
#define PD4  0x34
#define PD5  0x35
#define PD6  0x36
#define PD7  0x37
#define PD8  0x38
#define PD9  0x39
#define PD10 0x3A
#define PD11 0x3B
#define PD12 0x3C
#define PD13 0x3D
#define PD14 0x3E
#define PD15 0x3F

#define PE0  0x40
#define PE1  0x41
#define PE2  0x42
#define PE3  0x43
#define PE4  0x44
#define PE5  0x45
#define PE6  0x46
#define PE7  0x47
#define PE8  0x48
#define PE9  0x49
#define PE10 0x4A
#define PE11 0x4B
#define PE12 0x4C
#define PE13 0x4D
#define PE14 0x4E
#define PE15 0x4F

#define PF0  0x50
#define PF1  0x51
#define PF2  0x52
#define PF3  0x53
#define PF4  0x54
#define PF5  0x55
#define PF6  0x56
#define PF7  0x57
#define PF8  0x58
#define PF9  0x59
#define PF10 0x5A
#define PF11 0x5B
#define PF12 0x5C
#define PF13 0x5D
#define PF14 0x5E
#define PF15 0x5F

#define PG0  0x60
#define PG1  0x61
#define PG2  0x62
#define PG3  0x63
#define PG4  0x64
#define PG5  0x65
#define PG6  0x66
#define PG7  0x67
#define PG8  0x68
#define PG9  0x69
#define PG10 0x6A
#define PG11 0x6B
#define PG12 0x6C
#define PG13 0x6D
#define PG14 0x6E
#define PG15 0x6F

#define PH0  0x70
#define PH1  0x71
#define PH2  0x72
#define PH3  0x73
#define PH4  0x74
#define PH5  0x75
#define PH6  0x76
#define PH7  0x77
#define PH8  0x78
#define PH9  0x79
#define PH10 0x7A
#define PH11 0x7B
#define PH12 0x7C
#define PH13 0x7D
#define PH14 0x7E
#define PH15 0x7F

#define PI0  0x80
#define PI1  0x81
#define PI2  0x82
#define PI3  0x83
#define PI4  0x84
#define PI5  0x85
#define PI6  0x86
#define PI7  0x87
#define PI8  0x88
#define PI9  0x89
#define PI10 0x8A
#define PI11 0x8B
#define PI12 0x8C
#define PI13 0x8D
#define PI14 0x8E
#define PI15 0x8F

#endif 
