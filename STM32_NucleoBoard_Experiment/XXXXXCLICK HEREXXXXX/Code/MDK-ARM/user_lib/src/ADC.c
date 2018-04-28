#include "ADC.h"
volatile uint16_t ADC1_Value[4];
/*
void initADC()  
{  
		GPIO_InitTypeDef GPIO_InitStructure;    
		RCC_AHB1PeriphClockCmd(ADC1_GPIO_CLK1, ENABLE);  
		GPIO_InitStructure.GPIO_Pin = ADC1_GPIO_PIN1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ; 
		GPIO_Init(ADC1_GPIO_PORT1, &GPIO_InitStructure); 
	
	  RCC_AHB1PeriphClockCmd(ADC1_GPIO_CLK2, ENABLE);  
		GPIO_InitStructure.GPIO_Pin = ADC1_GPIO_PIN2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ; 
		GPIO_Init(ADC1_GPIO_PORT2, &GPIO_InitStructure);

		RCC_AHB1PeriphClockCmd(ADC1_GPIO_CLK3, ENABLE);  
		GPIO_InitStructure.GPIO_Pin = ADC1_GPIO_PIN3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ; 
		GPIO_Init(ADC1_GPIO_PORT3, &GPIO_InitStructure); 
	
		RCC_AHB1PeriphClockCmd(ADC1_GPIO_CLK4, ENABLE);  
		GPIO_InitStructure.GPIO_Pin = ADC1_GPIO_PIN4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ; 
		GPIO_Init(ADC1_GPIO_PORT4, &GPIO_InitStructure); 
		
    DMA_InitTypeDef DMA_InitStructure;  
    ADC_InitTypeDef ADC_InitStructure;  
		ADC_CommonInitTypeDef ADC_CommonInitStructure;  
    RCC_APB2PeriphClockCmd(ADC1_CLK , ENABLE);  
	  RCC_AHB1PeriphClockCmd(ADC1_DMA_CLK, ENABLE); 
	  DMA_InitStructure.DMA_Channel = ADC1_DMA_CHANNEL; 
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_ADDR; 
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)ADC1_Value; 
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; 
    DMA_InitStructure.DMA_BufferSize = ADC1_NofCHANEL; 
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
    DMA_InitStructure.DMA_PeripheralDataSize = 
    DMA_PeripheralDataSize_HalfWord; 
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; 
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;   //priority
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull; 
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
    DMA_Init(ADC1_DMA_STREAM, &DMA_InitStructure); 
    DMA_Cmd(ADC1_DMA_STREAM, ENABLE); 
		
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent; 
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4; 
    ADC_CommonInitStructure.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled; 
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles; //10 
    ADC_CommonInit(&ADC_CommonInitStructure); 
		
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; 
    ADC_InitStructure.ADC_ScanConvMode = ENABLE; 
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;  
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 
    ADC_InitStructure.ADC_NbrOfConversion = ADC1_NofCHANEL;
    ADC_Init(ADC1, &ADC_InitStructure); 
		
    ADC_RegularChannelConfig(ADC1, ADC1_CHANNEL1, 1, ADC1_SampleTime_xxxCycles); 
    ADC_RegularChannelConfig(ADC1, ADC1_CHANNEL2, 2, ADC1_SampleTime_xxxCycles);
    ADC_RegularChannelConfig(ADC1, ADC1_CHANNEL3, 3, ADC1_SampleTime_xxxCycles); 
  	ADC_RegularChannelConfig(ADC1, ADC1_CHANNEL4, 4, ADC1_SampleTime_xxxCycles); 
    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE); 
    ADC_DMACmd(ADC1, ENABLE); 
    ADC_Cmd(ADC1, ENABLE); 
    ADC_SoftwareStartConv(ADC1); 
} */