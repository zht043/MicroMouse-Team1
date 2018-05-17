#include "Timer.h"

#include "stm32f4xx_tim.h"



void ADVTIM_PWM_OUTPUT(uint8_t, uint32_t);

void NORTIM_PWM_OUTPUT(uint8_t, uint32_t);

uint16_t channel[16] = {0};

TIM initIO_TIM(uint8_t TIMERx, uint8_t Pxx, uint16_t ch) {

		GPIO_InitTypeDef GPIO_InitStructure;

	

	  //Switch Timer case

	  if(TIMERx == TIMER1) RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

		if(TIMERx == TIMER8) RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

		if(TIMERx == TIMER2) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	  if(TIMERx == TIMER3) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    if(TIMERx == TIMER4) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	

	  if(TIMERx == TIMER5) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	  if(TIMERx == TIMER9) RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

	  if(TIMERx == TIMER10) RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);

	  if(TIMERx == TIMER11) RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);

	  if(TIMERx == TIMER12) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);

	  if(TIMERx == TIMER13) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);

	  if(TIMERx == TIMER14) RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

	  

		GPIO obj;

		obj = Pxx_decoder(Pxx);

    RCC_AHB1PeriphClockCmd(obj.RCC_CMD, ENABLE);

		GPIO_InitStructure.GPIO_Pin = obj.Pin;

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;

		GPIO_Init(obj.GPIOx, &GPIO_InitStructure); 

		

		//Switch GPIO_PinAF case

		switch(TIMERx) {

			case TIMER1: GPIO_PinAFConfig(obj.GPIOx, obj.GPIO_PinSource, GPIO_AF_TIM1); break;

			case TIMER8: GPIO_PinAFConfig(obj.GPIOx, obj.GPIO_PinSource, GPIO_AF_TIM8); break;

			case TIMER2: GPIO_PinAFConfig(obj.GPIOx, obj.GPIO_PinSource, GPIO_AF_TIM2); break;

			case TIMER3: GPIO_PinAFConfig(obj.GPIOx, obj.GPIO_PinSource, GPIO_AF_TIM3); break;

			case TIMER4: GPIO_PinAFConfig(obj.GPIOx, obj.GPIO_PinSource, GPIO_AF_TIM4); break;

			case TIMER5: GPIO_PinAFConfig(obj.GPIOx, obj.GPIO_PinSource, GPIO_AF_TIM5); break;

			case TIMER9: GPIO_PinAFConfig(obj.GPIOx, obj.GPIO_PinSource, GPIO_AF_TIM9); break;

			case TIMER10: GPIO_PinAFConfig(obj.GPIOx, obj.GPIO_PinSource, GPIO_AF_TIM10); break;

			case TIMER11: GPIO_PinAFConfig(obj.GPIOx, obj.GPIO_PinSource, GPIO_AF_TIM11); break;

			case TIMER12: GPIO_PinAFConfig(obj.GPIOx, obj.GPIO_PinSource, GPIO_AF_TIM12); break;

			case TIMER13: GPIO_PinAFConfig(obj.GPIOx, obj.GPIO_PinSource, GPIO_AF_TIM13); break;

			case TIMER14: GPIO_PinAFConfig(obj.GPIOx, obj.GPIO_PinSource, GPIO_AF_TIM14); break;

			default: break;

		}

		

		/*if(TIMERx == TIMER1) {

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

		}*/

		

		channel[TIMERx] += ch;

		TIM ret;

		ret.Ch = ch;

		ret.TIMERx = TIMERx;

		return ret;

}

void PWM_ON(uint8_t TIMERx, uint32_t Frequency) 

{

		switch(TIMERx) {

			case TIMER1: ADVTIM_PWM_OUTPUT(TIMERx, Frequency); break;

			case TIMER8: ADVTIM_PWM_OUTPUT(TIMERx, Frequency); break;

			case TIMER2: NORTIM_PWM_OUTPUT(TIMERx, Frequency); break;

			case TIMER3: NORTIM_PWM_OUTPUT(TIMERx, Frequency); break;

			case TIMER4: NORTIM_PWM_OUTPUT(TIMERx, Frequency); break;

			case TIMER5: NORTIM_PWM_OUTPUT(TIMERx, Frequency); break;

			case TIMER9: NORTIM_PWM_OUTPUT(TIMERx, Frequency); break;

			case TIMER10: NORTIM_PWM_OUTPUT(TIMERx, Frequency); break;

			case TIMER11: NORTIM_PWM_OUTPUT(TIMERx, Frequency); break;

			case TIMER12: NORTIM_PWM_OUTPUT(TIMERx, Frequency); break;

			case TIMER13: NORTIM_PWM_OUTPUT(TIMERx, Frequency); break;

			case TIMER14: NORTIM_PWM_OUTPUT(TIMERx, Frequency); break;

			default: break;

		}

}  

void ADVTIM_PWM_OUTPUT(uint8_t TIMERx, uint32_t Frequency) {

		TIM_TypeDef * TIMx;

		

	  //Initialize TIMx_CLK

	  switch(TIMERx) {

			case TIMER1: TIMx = TIM1; break;

			case TIMER8: TIMx = TIM8; break;			

			default: break;

		}

		

		//Initialize

		uint16_t PrescalerValue = 0;

		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    TIM_OCInitTypeDef TIM_OCInitStructure;

		TIM_BDTRInitTypeDef TIM_BDTRInitStructure;

		

		//Config PrescalarValue

		PrescalerValue = (uint16_t) ((SystemCoreClock)/1000/Frequency) - 1;

		TIM_TimeBaseStructure.TIM_Period = 999;

		TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;

		TIM_TimeBaseStructure.TIM_ClockDivision = 0;

		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

		TIM_TimeBaseStructure.TIM_RepetitionCounter=0; 

		TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

		

		//Config PWM to 1

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 

		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;

		TIM_OCInitStructure.TIM_Pulse = 0;

		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;

		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;

		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset; 

	  

		//Config channel

		uint16_t Ch = channel[TIMERx];

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

		

		//Ouput Break and DeadLock 

		TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;

		TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;

		TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;

		TIM_BDTRInitStructure.TIM_DeadTime = 11;

		TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;

		TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;

		TIM_BDTRInitStructure.TIM_AutomaticOutput=TIM_AutomaticOutput_Enable;

		TIM_BDTRConfig(TIMx, &TIM_BDTRInitStructure);

		

		//Enable Output

		TIM_CtrlPWMOutputs(TIMx,ENABLE);

		TIM_ARRPreloadConfig(TIMx, ENABLE);

		TIM_Cmd(TIMx, ENABLE);

}

void NORTIM_PWM_OUTPUT(uint8_t TIMERx, uint32_t Frequency) {

		TIM_TypeDef * TIMx;

	

		//Initialize TIMx_CLK

		switch(TIMERx){

			case TIMER2: TIMx = TIM2; break;

			case TIMER3: TIMx = TIM3; break;

			case TIMER4: TIMx = TIM4; break;

			case TIMER5: TIMx = TIM5; break;

			case TIMER9: TIMx = TIM9; break;

			case TIMER10: TIMx = TIM10; break;

			case TIMER11: TIMx = TIM11; break;

			case TIMER12: TIMx = TIM12; break;

			case TIMER13: TIMx = TIM13; break;

  		case TIMER14: TIMx = TIM14; break;

			default:break;

		}

	

		//Initialize

		uint16_t PrescalerValue = 0;

		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

		TIM_OCInitTypeDef TIM_OCInitStructure;

	

		//Config PrescalarValue

		PrescalerValue = (uint16_t) ((SystemCoreClock)/1000/Frequency) - 1;

		TIM_TimeBaseStructure.TIM_Period = 999;

		TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;

		TIM_TimeBaseStructure.TIM_ClockDivision = 0;

		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

		TIM_TimeBaseStructure.TIM_RepetitionCounter=0; 

		TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

		

		//Config PWM to 1

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 

		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;

		TIM_OCInitStructure.TIM_Pulse = 0;

		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;

		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;

		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset; 

	  

		//Config channel

		uint16_t Ch = channel[TIMERx];

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

		

		//Enable Output

		TIM_CtrlPWMOutputs(TIMx,ENABLE);

		TIM_ARRPreloadConfig(TIMx, ENABLE);

		TIM_Cmd(TIMx, ENABLE);

}

void setPWM(TIM port, uint32_t dutyCircle) {

		switch(port.TIMERx) {

			case TIMER1: 

				if(port.Ch == Ch1) TIM1->CCR1 = dutyCircle;

				if(port.Ch == Ch2) TIM1->CCR2 = dutyCircle;

				if(port.Ch == Ch3) TIM1->CCR3 = dutyCircle;

				if(port.Ch == Ch4) TIM1->CCR4 = dutyCircle;

			break; 

			case TIMER8: 

				if(port.Ch == Ch1) TIM8->CCR1 = dutyCircle;

				if(port.Ch == Ch2) TIM8->CCR2 = dutyCircle;

				if(port.Ch == Ch3) TIM8->CCR3 = dutyCircle;

				if(port.Ch == Ch4) TIM8->CCR4 = dutyCircle;

			break; 

			case TIMER2: 

				if(port.Ch == Ch1) TIM2->CCR1 = dutyCircle;

				if(port.Ch == Ch2) TIM2->CCR2 = dutyCircle;

				if(port.Ch == Ch3) TIM2->CCR3 = dutyCircle;

				if(port.Ch == Ch4) TIM2->CCR4 = dutyCircle;

			break; 

			case TIMER3: 

				if(port.Ch == Ch1) TIM3->CCR1 = dutyCircle;

				if(port.Ch == Ch2) TIM3->CCR2 = dutyCircle;

				if(port.Ch == Ch3) TIM3->CCR3 = dutyCircle;

				if(port.Ch == Ch4) TIM3->CCR4 = dutyCircle;

			break; 

			case TIMER4: 

				if(port.Ch == Ch1) TIM4->CCR1 = dutyCircle;

				if(port.Ch == Ch2) TIM4->CCR2 = dutyCircle;

				if(port.Ch == Ch3) TIM4->CCR3 = dutyCircle;

				if(port.Ch == Ch4) TIM4->CCR4 = dutyCircle;

			break; 

			case TIMER5: 

				if(port.Ch == Ch1) TIM5->CCR1 = dutyCircle;

				if(port.Ch == Ch2) TIM5->CCR2 = dutyCircle;

				if(port.Ch == Ch3) TIM5->CCR3 = dutyCircle;

				if(port.Ch == Ch4) TIM5->CCR4 = dutyCircle;

			break; 

			case TIMER9: 

				if(port.Ch == Ch1) TIM9->CCR1 = dutyCircle;

				if(port.Ch == Ch2) TIM9->CCR2 = dutyCircle;

				if(port.Ch == Ch3) TIM9->CCR3 = dutyCircle;

				if(port.Ch == Ch4) TIM9->CCR4 = dutyCircle;

			break; 

			case TIMER10: 

				if(port.Ch == Ch1) TIM10->CCR1 = dutyCircle;

				if(port.Ch == Ch2) TIM10->CCR2 = dutyCircle;

				if(port.Ch == Ch3) TIM10->CCR3 = dutyCircle;

				if(port.Ch == Ch4) TIM10->CCR4 = dutyCircle;

			break; 

			case TIMER11: 

				if(port.Ch == Ch1) TIM11->CCR1 = dutyCircle;

				if(port.Ch == Ch2) TIM11->CCR2 = dutyCircle;

				if(port.Ch == Ch3) TIM11->CCR3 = dutyCircle;

				if(port.Ch == Ch4) TIM11->CCR4 = dutyCircle;

			break; 

			case TIMER12: 

				if(port.Ch == Ch1) TIM12->CCR1 = dutyCircle;

				if(port.Ch == Ch2) TIM12->CCR2 = dutyCircle;

				if(port.Ch == Ch3) TIM12->CCR3 = dutyCircle;

				if(port.Ch == Ch4) TIM12->CCR4 = dutyCircle;

			break;

			case TIMER13: 

				if(port.Ch == Ch1) TIM13->CCR1 = dutyCircle;

				if(port.Ch == Ch2) TIM13->CCR2 = dutyCircle;

				if(port.Ch == Ch3) TIM13->CCR3 = dutyCircle;

				if(port.Ch == Ch4) TIM13->CCR4 = dutyCircle;

			break; 

			case TIMER14: 

				if(port.Ch == Ch1) TIM14->CCR1 = dutyCircle;

				if(port.Ch == Ch2) TIM14->CCR2 = dutyCircle;

				if(port.Ch == Ch3) TIM14->CCR3 = dutyCircle;

				if(port.Ch == Ch4) TIM14->CCR4 = dutyCircle;

			break; 

			default: break;

		}

}

#define T3Freq 6000000
__IO uint16_t CCR1_Val = 0;  
__IO uint16_t CCR2_Val = 0;
__IO uint16_t CCR3_Val = 0;  
__IO uint16_t CCR4_Val = 0; 
uint16_t usToCCR(uint16_t us) {
		return (uint16_t)(T3Freq / 1000000) * us;
}
void TIM3_initIT(void) {
		NVIC_InitTypeDef NVIC_InitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		uint16_t PrescalerValue = (uint16_t) ((SystemCoreClock / 2) / T3Freq) - 1;
		TIM_TimeBaseStructure.TIM_Period = 65535;
		TIM_TimeBaseStructure.TIM_Prescaler = 0;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);	
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	
		TIM_OC1Init(TIM3, &TIM_OCInitStructure);
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);
		
		/*
   	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
		TIM_OC2Init(TIM3, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);
		
		*/
		
		/*
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

  TIM_OC3Init(TIM3, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable);
	
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

  TIM_OC4Init(TIM3, &TIM_OCInitStructure);

  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Disable);*/
		
		//TIM_ClearITPendingBit (TIM3, TIM_IT_CC1 | TIM_IT_CC2);
		//TIM_ITConfig(TIM3, TIM_IT_CC1 | TIM_IT_CC2, ENABLE);
		TIM_ClearITPendingBit (TIM3, TIM_IT_CC1);
		TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
		TIM_Cmd(TIM3, ENABLE);
}

void initEncoder(void) {
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                           
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);
		TIM_SetAutoreload (TIM2, 0xffffffff);
		TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);
		TIM_Cmd(TIM2, ENABLE);

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;  
		GPIO_Init(GPIOA, &GPIO_InitStructure);	
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
		TIM_SetAutoreload (TIM5, 0xffffffff);
		TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);
		TIM_Cmd(TIM5, ENABLE);
		ResetEnc();
}
int64_t   REnc_mem = 0,  LEnc_mem = 0;
void ResetREnc(void) {
		TIM2->CNT = 0;
		REnc_mem = 0;
}
void ResetLEnc(void) {
		TIM5->CNT = 0;
		LEnc_mem = 0;
}
void ResetEnc(void) {
		ResetLEnc();
		ResetREnc();
}
int32_t REnc(void) 
{
		if(abs((int)((int32_t)(TIM2->CNT))) >= 400000000) {
				REnc_mem += TIM2->CNT;
				ResetREnc();
		}
	  return TIM2->CNT + REnc_mem;
}
int32_t LEnc(void) 
{
		if(abs((int)((int32_t)(TIM5->CNT))) >= 400000000) {
				LEnc_mem += TIM5->CNT;
				ResetLEnc();
		}
	  return TIM5->CNT + LEnc_mem;
}