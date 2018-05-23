#include "Motor.h"

TIM LpwmA, LpwmB, RpwmA, RpwmB;
volatile double LpwrMem, RpwrMem;
void initMotor(void) {
		LpwrMem = 0;
		RpwrMem = 0;
		LpwmA = initIO_TIM(TIMER1, PA8, Ch1);
		LpwmB = initIO_TIM(TIMER1, PA9, Ch2);
		RpwmA = initIO_TIM(TIMER1, PA10, Ch3);
		RpwmB = initIO_TIM(TIMER1, PA11, Ch4);
		PWM_ON(TIMER1,10000);
		stop();
}
void motor(double Lpwr, double Rpwr) {
		Rpwr	*= -1.00f;
		if(LpwrMem != Lpwr) {
				if(Lpwr > 0.00f) {
						if(Lpwr > 100.00f) Lpwr = 100.00f;
						Lpwr*=10.00f; 
						setPWM(LpwmA, (uint32_t)Lpwr);
						setPWM(LpwmB, 0);
				}
				else {
						if(Lpwr < -100.00f) Lpwr = -100.00f;
						Lpwr*=-10.00f; 
						setPWM(LpwmB, (uint32_t)Lpwr);
						setPWM(LpwmA, 0);
				}
		}
		if(RpwrMem != Rpwr) {
				if(Rpwr > 0.00f) {
						if(Rpwr > 100.00f) Rpwr = 100.00f;
						Rpwr*=10.00f; 
						setPWM(RpwmA, (uint32_t)Rpwr);
						setPWM(RpwmB, 0);
				}
				else {
						if(Rpwr < -100.00f) Rpwr = -100.00f;
						Rpwr*=-10.00f; 
						setPWM(RpwmB, (uint32_t)Rpwr);
						setPWM(RpwmA, 0);
				}
		}
		LpwrMem = Lpwr;
		RpwrMem = Rpwr;
}

/* MatLab
>> rref([R/2 R/2 v;-1/2 1/2 w])
				[  R/2, R/2, v] [wL]
				[ -1/2, 1/2, w]	[wR]
ans =
[ 1, 0, (v - R*w)/R] wL
[ 0, 1, (v + R*w)/R] wR
*/
void curve(double v, double w) {
		//motor((v/Radius-w)/LwDp,(v/Radius+w)/RwDp);
		motor((v-w),(v+w));
}
void stop(void) {
		motor(0,0);
}


void motorTester(void) {
		while(1) {
				for(double pwr = 0.00f; pwr <= 100.00f; pwr+=0.1) {
						motor(pwr, pwr);
						delay(3);
				}
				
				for(double pwr = 100.00f; pwr > 0.00f; pwr-=0.1) {
						motor(pwr, pwr);
						delay(3);
				}
				for(double pwr = 0.00f; pwr >= -100.00f; pwr-=0.1) {
						motor(pwr, pwr);
						delay(3);
				}
				for(double pwr = -100.00f; pwr <= 0.00f; pwr+=0.1) {
						motor(pwr, pwr);
						delay(3);
				}
		}
}

