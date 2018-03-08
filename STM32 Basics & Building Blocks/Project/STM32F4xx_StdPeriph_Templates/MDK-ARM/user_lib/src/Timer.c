#include "Timer.h"
#include "stm32f4xx_tim.h"

uint8_t ADVTIM_PWM_OUTPUT(uint8_t, uint16_t, uint32_t);
uint8_t NORTIM_PWM_OUTPUT(uint8_t, uint16_t, uint32_t);

TIM initIO_TIM(uint8_t TIMERx, uint8_t Pxx) {
		GPIO_InitTypeDef GPIO_InitStructure;
	  if(TIMERx == TIMER1) RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		if(TIMERx == TIMER8) RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
		GPIO obj;
		switch((Pxx /0x10) % 0x10) {
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
				break;
			*/
			default: break;
		}	
    RCC_AHB1PeriphClockCmd(obj.RCC_CMD, ENABLE);
		switch(Pxx %0x10) {
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
			case 0x10: 
				obj.Pin = GPIO_Pin_10; 
			  obj.GPIO_PinSource = GPIO_PinSource10;
				break;
			case 0x11: 
				obj.Pin = GPIO_Pin_11; 
				obj.GPIO_PinSource = GPIO_PinSource11;
				break;
			case 0x12: 
				obj.Pin = GPIO_Pin_12; 
				obj.GPIO_PinSource = GPIO_PinSource12;
				break;
			case 0x13: 
				obj.Pin = GPIO_Pin_13; 
				obj.GPIO_PinSource = GPIO_PinSource13;
				break;
			case 0x14: 
				obj.Pin = GPIO_Pin_14; 
				obj.GPIO_PinSource = GPIO_PinSource14;
				break;
			case 0x15: 
				obj.Pin = GPIO_Pin_15; 
				obj.GPIO_PinSource = GPIO_PinSource15;
				break;
			default : break;
		}
		GPIO_InitStructure.GPIO_Pin = obj.Pin;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
		GPIO_Init(obj.GPIOx, &GPIO_InitStructure); 
		switch(TIMERx) {
			case TIMER1: GPIO_PinAFConfig(obj.GPIOx, obj.GPIO_PinSource, GPIO_AF_TIM1); break;
			case TIMER8: GPIO_PinAFConfig(obj.GPIOx, obj.GPIO_PinSource, GPIO_AF_TIM8); break;
			default: break;
		}
		uint16_t ch;
		if(TIMERx == TIMER1) {
			switch(Pxx) {
				case PA8: ch = Ch1; break;
				case PE9: ch = Ch1; break;
				case PC9: ch = Ch1; break;
				case PE11: ch = Ch2; break;
				case PA9: ch = Ch2; break;
				case PE13: ch = Ch3; break;
				case PA10: ch = Ch3; break;
				case PE14: ch = Ch4; break;
				case PA11: ch = Ch4; break;
				default: break;
			}
		}
		if(TIMERx == TIMER8) {
			switch(Pxx) {
				case PC6: ch = Ch1; break;
				case PI5: ch = Ch1; break;
				case PC7: ch = Ch2; break;
				case PI6: ch = Ch2; break;
				case PC8: ch = Ch3; break;
				case PI7: ch = Ch3; break;
				case PA3: ch = Ch4; break;
				case PB11: ch = Ch4; break;
				default: break;
			}
		}
		TIM ret;
		ret.Ch = ch;
		ret.TIMERx = TIMERx;
		return ret;
}

void initTimer_PWM_OUTPUT(uint8_t TIMERx, uint16_t Ch, uint32_t Frequency) 
{
		switch(TIMERx) {
			case TIMER1: ADVTIM_PWM_OUTPUT(TIMERx, Ch, Frequency); break;
			case TIMER8: ADVTIM_PWM_OUTPUT(TIMERx, Ch, Frequency); break;
			case TIMER2: NORTIM_PWM_OUTPUT(TIMERx, Ch, Frequency); break;
			case TIMER3: NORTIM_PWM_OUTPUT(TIMERx, Ch, Frequency); break;
			case TIMER4: NORTIM_PWM_OUTPUT(TIMERx, Ch, Frequency); break;
			case TIMER5: NORTIM_PWM_OUTPUT(TIMERx, Ch, Frequency); break;
			case TIMER9: NORTIM_PWM_OUTPUT(TIMERx, Ch, Frequency); break;
			case TIMER10: NORTIM_PWM_OUTPUT(TIMERx, Ch, Frequency); break;
			case TIMER11: NORTIM_PWM_OUTPUT(TIMERx, Ch, Frequency); break;
			case TIMER12: NORTIM_PWM_OUTPUT(TIMERx, Ch, Frequency); break;
			case TIMER13: NORTIM_PWM_OUTPUT(TIMERx, Ch, Frequency); break;
			case TIMER14: NORTIM_PWM_OUTPUT(TIMERx, Ch, Frequency); break;
			default: break;
		}
}  
uint8_t ADVTIM_PWM_OUTPUT(uint8_t TIMERx, uint16_t Ch, uint32_t Frequency) {
		TIM_TypeDef * TIMx;
		switch(TIMERx) {
			case TIMER1: TIMx = TIM1; break;
			case TIMER8: TIMx = TIM8; break;			
			default: break;
		}
		uint16_t PrescalerValue = 0;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
		TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	
		PrescalerValue = (uint16_t) ((SystemCoreClock)/1000/Frequency) - 1;
		TIM_TimeBaseStructure.TIM_Period = 999;
		TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0; 
		TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
		//-------------------------------------------------------------
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0;
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset; 
	  //-------------------------------------------------------------
		if(Ch%10) {
			TIM_OC1Init(TIMx, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
		}
		Ch/=10;
		if(Ch%10) {
			TIM_OC2Init(TIMx, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
		}
		Ch/=10;
		if(Ch%10) {
			TIM_OC3Init(TIMx, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
		}
		Ch/=10;
		if(Ch) {
			TIM_OC4Init(TIMx, &TIM_OCInitStructure);
			TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
		}
		//--------------------------------------------------------------
		TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
		TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
		TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
		TIM_BDTRInitStructure.TIM_DeadTime = 11;
		TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
		TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;
		TIM_BDTRInitStructure.TIM_AutomaticOutput=TIM_AutomaticOutput_Enable;
		TIM_BDTRConfig(TIMx, &TIM_BDTRInitStructure);
		//--------------------------------------------------------------
		TIM_CtrlPWMOutputs(TIMx,ENABLE);
		TIM_ARRPreloadConfig(TIMx, ENABLE);
		TIM_Cmd(TIMx, ENABLE);
}
uint8_t NORTIM_PWM_OUTPUT(uint8_t TIMx, uint16_t Pxx, uint32_t Frequency) {
}
void PWM_OUT(TIM port, uint32_t dutyCircle) {
		switch(port.TIMERx) {
			case TIMER1: 
				if(port.Ch == Ch1) TIM1->CCR1 = dutyCircle;
				if(port.Ch == Ch2) TIM1->CCR2 = dutyCircle;
				if(port.Ch == Ch3) TIM1->CCR3 = dutyCircle;
				if(port.Ch == Ch4) TIM1->CCR4 = dutyCircle;
			break; 
			case TIMER2: 
				if(port.Ch == Ch1) TIM1->CCR1 = dutyCircle;
				if(port.Ch == Ch2) TIM1->CCR2 = dutyCircle;
				if(port.Ch == Ch3) TIM1->CCR3 = dutyCircle;
				if(port.Ch == Ch4) TIM1->CCR4 = dutyCircle;
			break; 
			default: break;
		}
}