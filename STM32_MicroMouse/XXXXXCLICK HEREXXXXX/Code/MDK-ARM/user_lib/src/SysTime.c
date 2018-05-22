#include "SysTime.h"
static __IO uint32_t Tick_CNT;
void SysTick_Init(uint32_t ticks)  {       
    /*                   ticks
			 SystemFrequency / 1000    1ms   interrupt
       SystemFrequency / 100000  10us  interrupt
       SystemFrequency / 1000000 1us   interrupt
      */ 
    if (SysTick_Config(SystemCoreClock / ticks)) { 
		 /* Capture error */ 
				
    } 
}
void SysTick_Increment(void) {
		Tick_CNT++;
}	
uint32_t millis(void) {
		return Tick_CNT;
}
uint32_t micros(void) {
	  return Tick_CNT*1000 + 1000 - (uint32_t)((SysTick->VAL)/(SystemCoreClock / 1000000)); 
}
void delay_us(uint32_t Time) {
		uint32_t T_init = micros(); 
		while(micros() - T_init < Time); 
}
void delay(uint32_t Time) {
		uint32_t T_init = millis(); 
		while(millis() - T_init < Time); 
}

#define OneMillSecInterr 1000
void SysTime_Init(void) {
		SysTick_Init(OneMillSecInterr);

}


