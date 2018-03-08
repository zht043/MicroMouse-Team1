#include "buzzer.h"
#include "stm32f4xx.h"
#include "delay.h"

//buzzer use PB4 TIM3_CH1
//buzzer's resonant frequency is 4000+-500Hz
//use TIM3->AAR to update period

int32_t buzzerTime;

void buzzer_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;		
  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  
  /* GPIOB Configuration: TIM3 CH1 (PB4) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // alternative function mode
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//do we need this line? why?
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // push pull mode
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//can this be flow?
  GPIO_Init(GPIOA, &GPIO_InitStructure); 

  /* Connect TIM3 pins to AF */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);


	//TIM3 clock = APB1 clock * 2 = 84MHz
	//TIM3 clock = (period+1) * (prescaler+1) * PWM_frequency
    //   ==> 84MHz = (period+1) * (prescaler+1) * PWM_frequency(Hz)
    //   ==>  PWM_frequency(Hz) = 84000000Hz / (period+1) / (prescaler+1)
    //   usually, we only change the period(the corresponding register is TIM3->AAR, so we change the value of TIM3->AAR) in order to change
    //   the frequency of the frequency of the buzzer beeping. you can either write a function or have
    //   a macro like this:      #define setBuzzerFrequency(f)    TIM3->ARR=84000000/(f)/140-1 
	//PWM frequency = 4KHz as default because the buzzer has a 4KHz+-500Hz max resonant range.
    //any thing beyond the max resonant range will still work

    //you can also change the value for prescaler in order to change the frequency
    //the period and prescaler are 150 and 140, since the registers start to count from 0,
	//so the actual value should +1 when you are calculate the frequency and anything else
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 149;//150  TIM3->AAR       
	TIM_TimeBaseStructure.TIM_Prescaler = 139;//140
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;//TIM3 clock(84MHz here) divide by 1(0+1) to be the clock to be the base clock of TIM3 PWM
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//PWM mode 1, most commond mode
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//if polarity is high, when you set PWM at 25% duty cycle, the 25% will be high and 75% will be low
	                                                         //when the polarity is LOW, 75% will be high and 25% will be low
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//enable the preload for PWM channel 1
	 
	TIM_ARRPreloadConfig(TIM3, ENABLE);              //enable the proload for TIM3-ARR register
	TIM_Cmd(TIM3, ENABLE);	// enable TIM3
}

void beep(int times)
{
	int i;
	buzzerTime = 140*times;//this function takes about 140ms to finish when int times = 1, we have this line here is because of the function void shortBeep(int duration, int freq) below. 
	                       //we set buzzerTime to 140 multiply how many times to beep to prevent the buzzer being turned off at the first millisecond.
	setBuzzerFrequency(4000);  //set buzzer beep at 4000Hz
	for(i=0; i<times; i++)
	{
		beep_on;
		delay_ms(70);
		beep_off;
		delay_ms(70);
	}
}


//this is the kinda of beep that you can use when the mouse is running.
//for example, if you want to mouse to beep for 100ms, we turn on the buzzer and set the buzzerTime as the beeping duration
//we also call buzzerTime--; inside of SysTick_Handler inside of stm32f4xx_it.c . so the buzzerTime will reduce by 1 every milliseoncd
//since SysTick_Handler runs every 1 ms.  We also have to include inside of SysTick_Handler something like 	
//         if(buzzerTime < 0)
//		       beep_off;
//in order to turn off the buzzer after the designated time elaspes. By this way, the MCU doesn't have to wait and't can't do anything else until the buzzer is off.
//this can be use to tell some information such as when the wall-to-no-wall or post-to-no-post transition is detected when mouse is running.
//this is a smarter way than the funtion void beep(int times). However, you can still use void beep(int times) when the mouse stops before anything else going to happen.
void shortBeep(int duration, int freq)
{
	//beep_on;
	TIM3->CCR1 = (TIM3->ARR+1)/4;
	setBuzzerFrequency(freq);
	buzzerTime = duration;
}


 
