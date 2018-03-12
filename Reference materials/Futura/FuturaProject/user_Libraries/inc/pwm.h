#ifndef PWM_H
#define PWM_H   
//#include "stm32f10x_lib.h"
#include <stdint.h>

void TIM4_GPIO_Config(void);
void TIM4_Mode_Config(void);
void TIM4_PWM_Init(void);
void setLeftPwm(int32_t speed);
void setRightPwm(int32_t speed);

#define L_PWM_F TIM4->CCR1
#define L_PWM_R TIM4->CCR2
#define R_PWM_F TIM4->CCR3
#define R_PWM_R TIM4->CCR4

#define turnMotorOff     setLeftPwm(0);setRightPwm(0)

#endif
