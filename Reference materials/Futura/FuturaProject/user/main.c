#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "button.h"
#include <stdio.h>
#include "usart.h"
#include "SPI.h"
#include "matrixDisplay.h"
#include "pwm.h"
#include "encoder.h"
#include "buzzer.h"
#include "main.h"
#include "sensor_Function.h"
#include "adc.h"

void systick(void) {
}

void button1_interrupt(void) {
}


void button2_interrupt(void) {
}

int main(void) {
	Systick_Configuration();
	LED_Configuration();
	button_Configuration();
	usart1_Configuration(9600);
	SPI_Configuration();
  TIM4_PWM_Init();
	Encoder_Configration();
	buzzer_Configuration();
	ADC_Config();
	
	
	shortBeep(2000, 8000);
	while(1) {
		readSensor();
		readGyro();
		readVolMeter();
		printf("LF %d RF %d DL %d DR %d aSpeed %d angle %d voltage %d lenc %d renc %d\r\n", LFSensor, RFSensor, DLSensor, DRSensor, aSpeed, angle, voltage, getLeftEncCount(), getRightEncCount());
		displayMatrix("mous");
		
		setLeftPwm(100);
		setRightPwm(100);
		delay_ms(1000);
	}
}
