#ifndef LED_H
#define LED_H

#include "stm32f4xx.h"

#define LED1_ON    GPIO_SetBits(GPIOA, GPIO_Pin_11)
#define LED1_OFF   GPIO_ResetBits(GPIOA, GPIO_Pin_11)
#define LED2_ON    GPIO_SetBits(GPIOA, GPIO_Pin_12)
#define LED2_OFF   GPIO_ResetBits(GPIOA, GPIO_Pin_12)
#define LED3_ON    GPIO_SetBits(GPIOC, GPIO_Pin_10)
#define LED3_OFF   GPIO_ResetBits(GPIOC, GPIO_Pin_10)
#define LED4_ON    GPIO_SetBits(GPIOC, GPIO_Pin_11)
#define LED4_OFF   GPIO_ResetBits(GPIOC, GPIO_Pin_11)
#define LED5_ON    GPIO_SetBits(GPIOC, GPIO_Pin_12)
#define LED5_OFF   GPIO_ResetBits(GPIOC, GPIO_Pin_12)
#define LED6_ON    GPIO_SetBits(GPIOD, GPIO_Pin_2)
#define LED6_OFF   GPIO_ResetBits(GPIOD, GPIO_Pin_2)
#define LED7_ON    GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define LED7_OFF   GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define LED8_ON    GPIO_SetBits(GPIOB, GPIO_Pin_4)
#define LED8_OFF   GPIO_ResetBits(GPIOB, GPIO_Pin_4)
#define LED9_ON    GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define LED9_OFF   GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define LED10_ON    GPIO_SetBits(GPIOA, GPIO_Pin_2)
#define LED10_OFF   GPIO_ResetBits(GPIOA, GPIO_Pin_2)
#define LED11_ON    GPIO_SetBits(GPIOB, GPIO_Pin_11)
#define LED11_OFF   GPIO_ResetBits(GPIOB, GPIO_Pin_11)

#define RF_EM_ON   GPIO_SetBits(GPIOC, GPIO_Pin_1)
#define RF_EM_OFF  GPIO_ResetBits(GPIOC, GPIO_Pin_1)
#define LF_EM_ON   GPIO_SetBits(GPIOC, GPIO_Pin_7)
#define LF_EM_OFF  GPIO_ResetBits(GPIOC, GPIO_Pin_7)
#define SIDE_EM_ON   GPIO_SetBits(GPIOA, GPIO_Pin_7)
#define SIDE_EM_OFF  GPIO_ResetBits(GPIOA, GPIO_Pin_7)

#define ALL_LED_OFF LED1_OFF; \
                    LED2_OFF; \
                    LED3_OFF; \
										LED4_OFF; \
										LED5_OFF; \
										LED6_OFF; \
                    LED7_OFF; \
                    LED8_OFF; \
										LED9_OFF; \
										LED10_OFF; \
										LED11_OFF
										
										
#define ALL_LED_ON  LED1_ON; \
                    LED2_ON; \
										LED3_ON; \
										LED4_ON; \
										LED5_ON; \
										LED6_ON; \
                    LED7_ON; \
                    LED8_ON; \
										LED9_ON; \
										LED10_ON; \
										LED11_ON

void LED_Configuration(void);

#endif /* LED_H */
