#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "SysTime.h"
#include "GPIO.h"
#include "Timer.h"
#include "USART.h"
#include "SPI.h"
#include "ADC.h"
///////////////////////////////
#include "Motor.h"
#include "Led.h"
#include "IR.h"
#include "StartGesture.h"
///////////////////////////////
extern __IO uint16_t IR_values[6];
///////////////////////////////
double f_abs(double a) {
	return a < 0 ? -a : a;
}
uint8_t equal(double x, double y, double errorRange) {
    if(f_abs(x-y) < errorRange) return 1;
    else return 0;
}
typedef struct {
    double Pout, Iout, Dout;
    double Ep, Ei, Ed;
    double Kp, Ki, Kd;
    double integral, differential;
    double pExp;
    double pAct;
    uint64_t T;

} PID;

PID Angular;
void initAngular_PID(double Kp, double Ki, double Kd, double Exp, double Act) {
    Angular.Kp = Kp;
    Angular.Ki = Ki;
    Angular.Kd = Kd;
    Angular.pExp = Exp;
    Angular.pAct = Act;
    Angular.integral = 0.000f;
    Angular.Pout = Kp * (Exp - Act); 
    Angular.Iout = 0.000f; 
    Angular.Dout = 0.000f;
    Angular.T = micros();
}

double Angular_PID(double Exp, double Act) {
    double dT = (double)(micros() - Angular.T) / 1000000.000f;
    //-------Pout--------//
    Angular.Ep = Exp - Act;
    double Pout = Angular.Kp * Angular.Ep;

    if(dT > 0.01000f) {
        Angular.pExp = Exp;
        Angular.pAct = Act;
        Angular.T = micros();
        return Pout + Angular.Iout + Angular.Dout;
    }

    //-------Iout--------//
    if(Angular.pExp != Exp) Angular.integral = 0.000f;
    Angular.integral += (((Exp - Act) + (Angular.pExp - Angular.pAct)) / 2.0000000000f) * dT ;
    double Iout = Angular.Ki * Angular.integral;

    //-------Dout--------//
    double Dout;
    if(equal(Act, Angular.pAct, 0.000001)) Dout = 0.000f;
    else {
        Angular.differential = (Angular.pAct - Act) / (dT * 1000.000f);
        Dout = Angular.differential * Angular.Kd;
    }

    //----update-----//
    Angular.pExp = Exp;
    Angular.pAct = Act;
    Angular.T = micros();
    //----Tester-----//
    //PTester[Tindex] = Pout; ITester[Tindex] = Iout; DTester[Tindex] = Dout; Ttrac[Tindex] = Angular.T;
    //Tindex++;
    //----return-----//
    Angular.Pout = Pout; Angular.Iout = Iout; Angular.Dout = Dout;
    return (Pout + Iout + Dout);
}

double Angle(void) {
		return (double)(REnc() - LEnc()) * 90.00f / 30000.000f;
}

int main(void)
{
		SysTime_Init();
		initLED();
		blinkLED(10);
	
		initUSART(USART1, PB6, PB7, 9600);
		printfForUx(USART1);
		scanfForUx(USART1);
		printf("\rHellow World! El Psy Congroo!!!\r\n");

		//IR_Tester();

		initIR();
		startGesture();

		initMotor();
		initEncoder();
		
		//while(1) printf("\r%d %d [%lf]r\n", LEnc(), REnc(), Angle());
		double refExp = Angle();
		initAngular_PID(10.750f, 0.300f, 33.733f, refExp, Angle());
		uint32_t t0;
		t0 = millis();
		while(millis() - t0 < 800) {
				curve(20, Angular_PID(refExp, Angle()));
		}
		halt();
}























#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
