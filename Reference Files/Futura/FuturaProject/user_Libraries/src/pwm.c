#include "pwm.h"
#include "stm32f4xx.h"

//TIM4 CH1 (PB6), TIM4 CH2 (PB7), TIM4 CH3 (PB8) and TIM4 CH4 (PB9)
u16 CCR1_Val = 0; //set initial PWM as 0
u16 CCR2_Val = 0;
u16 CCR3_Val = 0;
u16 CCR4_Val = 0;

// forward:
// 			TIM4->CCR1=0;
// 			TIM4->CCR2=spd;
// 			TIM4->CCR3=0;
// 			TIM4->CCR4=spd;

void TIM4_GPIO_Config()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  
  /* GPIOB Configuration: TIM4 CH1 (PB6), TIM4 CH2 (PB7), TIM4 CH3 (PB8) and TIM4 CH4 (PB9) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        // motors pins: PB6 PB7 PB8 PB9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 

  /* Connect TIM4 pins to AF */  
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4); 
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM4); 
}

void TIM4_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;		
	//TIM4 clock = APB1 clock * 2 = 84MHz
	//Tim4 clock = (period+1) * (prescaler+1) * PWM_frequency
	//PWM frequency = 84000000 / (999+1) / (3+1) = 21000Hz = 21KHz
	//the value for TIM_TimeBaseStructure.TIM_Period is the scale for PWM
	//for example, if the value is 999, which mean the PWM is scaled from 0-999,
	//where motor don't move when at 0 and move output max power when at 999.
	//we actually devided pwm to 1000 parts evenly, however since it starts with 0 instead
	//of 1, the max is 999. the scale for the pwm is based on your reference. usually 999(1000)
	//is enough for a 6V faulfalber motor, you might need larger value if useing 3V version since it's more powerful

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 999;
	TIM_TimeBaseStructure.TIM_Prescaler = 3;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);


	//since we use all 4 channels for TIM4 as PWM. we need to set all 4 channels here.
	//even though there are likely 4 or more channels for each general purpose timer, the frequency can be one frequency for each timer
	//which means the PWM frequencies are all same for all 4 channel if all PWM pins are from TIM4
	//we change the duty cycle in order to change the motor PWM speed.
	//so we change the "TIM_OCInitStructure.TIM_Pulse"(TIM4->CCRx  x is 1 to 4) for duty cycle for each PWM channels
	//since the PWM frequency we set is 21KHz, so every 1/21000 second the Timer check the value for TIM4->CCRx to update the motor value)
	//motor is more responsive than your sensor sample rate in this case which is what we wanted
	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM4, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);


	/* PWM1 Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

	TIM_OC2Init(TIM4, &TIM_OCInitStructure);

	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	/* PWM1 Mode configuration: Channel3 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

	TIM_OC3Init(TIM4, &TIM_OCInitStructure);

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

	/* PWM1 Mode configuration: Channel4 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

	TIM_OC4Init(TIM4, &TIM_OCInitStructure);

	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM4, ENABLE);

	/* TIM4 enable counter */
	TIM_Cmd(TIM4, ENABLE);
}

void TIM4_PWM_Init(void)
{
	TIM4_GPIO_Config();
	TIM4_Mode_Config();
}

//call the functions below whenever you need to set the motor to a new speed.
//when the parameter input is negative, the motor spin backwards.
//the range for PWM input is -999 to 999 the absolution value for the max input is based on the value
//you set for TIM_TimeBaseStructure.TIM_Period (which is register TIM4->ARR)
void setLeftPwm(int32_t speed)
{
	if(speed > 999)//parameter check
		speed = 999;
	if(speed < -999)
		speed = -999;

    if(speed >= 0)//forward
    {
        L_PWM_F = speed;
        L_PWM_R	= 0; 
    }          
    else//rewind
    {        
        L_PWM_F = 0;
        L_PWM_R	= -speed; 
    }
}

void setRightPwm(int32_t speed)
{
	if(speed > 999)
		speed = 999;
	if(speed < -999)
		speed = -999;	
	
    if(speed >= 0)//forward
    {
        R_PWM_F = speed;
        R_PWM_R	= 0; 
    }          
    else//rewind
    {    
        R_PWM_F = 0;
        R_PWM_R	= -speed; 
    }
}
