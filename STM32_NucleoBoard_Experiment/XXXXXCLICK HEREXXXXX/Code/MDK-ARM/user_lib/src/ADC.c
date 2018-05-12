#include "ADC.h" 
#include <stdio.h>
#include <stdlib.h>
#define ADC_DMA_CLK      RCC_AHB1Periph_DMA2 
#define ADC_DMA_CHANNEL  DMA_Channel_0 
#define ADC_DMA_STREAM   DMA2_Stream0 
#define ADC_SampleTime_xxxCycles ADC_SampleTime_56Cycles  
#define ADC_TwoSamplingDelay_xxCycles ADC_TwoSamplingDelay_10Cycles
uint8_t adcs[8];
int8_t adcs_index = 0;
volatile uint16_t ADC_Value[1];

int addADC(uint8_t Pxx, uint8_t ADCchannel) {
		if(adcs_index > 8) return 0;
		GPIO obj = Pxx_decoder(Pxx);
		GPIO_InitTypeDef GPIO_InitStructure;    
		RCC_AHB1PeriphClockCmd(obj.RCC_CMD, ENABLE);  
		GPIO_InitStructure.GPIO_Pin = obj.Pin;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
		GPIO_Init(obj.GPIOx, &GPIO_InitStructure);
		adcs[adcs_index++] = ADCchannel;
		return 1;
}
void initADC(ADC_TypeDef * ADCx)  
{  
    DMA_InitTypeDef DMA_InitStructure;  
    ADC_InitTypeDef ADC_InitStructure;  
		ADC_CommonInitTypeDef ADC_CommonInitStructure;  
		if(ADCx == ADC1)	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
		if(ADCx == ADC2)	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 , ENABLE);
		if(ADCx == ADC3)	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3 , ENABLE);   
	  RCC_AHB1PeriphClockCmd(ADC_DMA_CLK, ENABLE); 
	  DMA_InitStructure.DMA_Channel = ADC_DMA_CHANNEL; 
		if(ADCx == ADC1)	DMA_InitStructure.DMA_PeripheralBaseAddr = ((uint32_t)ADC1+0x4c) ; 
		if(ADCx == ADC2)	DMA_InitStructure.DMA_PeripheralBaseAddr = ((uint32_t)ADC2+0x4c);
		if(ADCx == ADC3)	DMA_InitStructure.DMA_PeripheralBaseAddr = ((uint32_t)ADC3+0x4c);
	
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)ADC_Value; 
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; 
    DMA_InitStructure.DMA_BufferSize = adcs_index; 
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
   // DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; 
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; 
    //DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word; 
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;   //priority
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull; 
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
    DMA_Init(ADC_DMA_STREAM, &DMA_InitStructure); 
    DMA_Cmd(ADC_DMA_STREAM, ENABLE); 
		
		
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent; 
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4; 
    ADC_CommonInitStructure.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled; 
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_xxCycles;
    ADC_CommonInit(&ADC_CommonInitStructure); 
		
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; 
    ADC_InitStructure.ADC_ScanConvMode = ENABLE; 
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;  
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 
    ADC_InitStructure.ADC_NbrOfConversion = adcs_index;
    ADC_Init(ADCx, &ADC_InitStructure); 
		
		//int temp = adcs_index - 1;
		//for(; temp >=0; temp--) 
		ADC_RegularChannelConfig(ADCx, ADC_Channel_1, 1, ADC_SampleTime_xxxCycles); 
    ADC_DMARequestAfterLastTransferCmd(ADCx, ENABLE); 
    ADC_DMACmd(ADCx, ENABLE); 
    ADC_Cmd(ADCx, ENABLE); 
    ADC_SoftwareStartConv(ADCx); 
} 
int getIndexValue(void) {
		return adcs_index;
}
int getADCValue(int index){
	int tmp = ADC_Value[index];
	//ADC_Value[index] = 0;
	return tmp;
}