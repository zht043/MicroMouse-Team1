//#include "global.h"
#include "sensor_Function.h"
#include "adc.h"
#include "delay.h"
#include "pwm.h"
#include "matrixDisplay.h"
#include "led.h"
#include <stdio.h>
#include "encoder.h"

int reflectionRate = 1000;//which is 1.000 (converted to ingeter)

int32_t volMeter = 0;
int32_t voltage = 0;
int32_t LFSensor = 0;
int32_t RFSensor = 0;
int32_t DLSensor = 0;
int32_t DRSensor = 0;
int32_t Outz = 0;
int32_t aSpeed = 0;//angular velocity
int32_t angle = 0; 


/*read IR sensors*/
void readSensor(void)
{
	u32 curt;
//read DC value		
	
	LFSensor = read_LF_Sensor;	
	RFSensor = read_RF_Sensor;	
	DLSensor = read_DL_Sensor;
	DRSensor = read_DR_Sensor;	
	
	curt = micros();
	
//left front sensor
	LF_EM_ON;
	elapseMicros(60,curt);
	LFSensor = read_LF_Sensor - LFSensor;
	LF_EM_OFF;
	if(LFSensor < 0)//error check
		LFSensor = 0;
 	elapseMicros(140,curt);
//right front sensor	
	RF_EM_ON;
	elapseMicros(200,curt);	
	RFSensor = read_RF_Sensor - RFSensor;
	RF_EM_OFF;
	if(RFSensor < 0)
		RFSensor = 0;
 	elapseMicros(280,curt);
//diagonal sensors
	SIDE_EM_ON;
	elapseMicros(340,curt);	
	DLSensor = read_DL_Sensor - DLSensor;
	DRSensor = read_DR_Sensor - DRSensor;
  SIDE_EM_OFF;
	if(DLSensor < 0)
		DLSensor = 0;
	if(DRSensor < 0)
		DRSensor = 0;
	
	readVolMeter();
	
	LFSensor = LFSensor*reflectionRate/1000;
	RFSensor = RFSensor*reflectionRate/1000;
	DLSensor = DLSensor*reflectionRate/1000;
	DRSensor = DRSensor*reflectionRate/1000;
	
	//delay_us(80);
	//elapseMicros(500,curt);
}
//there are 1000 - 340 = 660 us remaining in a 1ms_ISR

/*read gyro*/
void readGyro(void)
{	                      //k=19791(sum for sample in 1 second)    101376287 for 50 seconds with 5000 samples
	int i;
	int sampleNum = 20;
	aSpeed = 0;
	for(i=0;i<sampleNum;i++)
		aSpeed += read_Outz;
    aSpeed *= 50000/sampleNum;
	aSpeed -= 92980000;
	aSpeed /= 50000;	
	aSpeed /= 4;
	angle += aSpeed; 
}


/*read voltage meter*/
void readVolMeter(void)
{          //3240 = 7.85V
	volMeter = read_Vol_Meter;//raw value
	voltage = volMeter*809/3248;//actual voltage value  ex) 8.2V = 8200
}

void lowBatCheck(void)
{
  if(voltage < 700) //alert when battery Voltage lower than 7V
	{	
		
		setLeftPwm(0);
		setRightPwm(0);
		
		while(1)
		{
			displayMatrix("Lbat");
			//beep_on;      
			ALL_LED_OFF;
			delay_ms(200);

			clearScreen();
			//beep_off;      
			ALL_LED_ON;
			delay_ms(200);			
		}
	}
  else {
		  displayInt(voltage);
		  delay_ms(1000);
	}		
}


