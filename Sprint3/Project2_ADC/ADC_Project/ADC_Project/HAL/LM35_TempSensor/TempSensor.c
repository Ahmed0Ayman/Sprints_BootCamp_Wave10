/*
 * TempSensor.c
 *
 * Created: 1/17/2022 10:23:44 AM
 *  Author: Ahmed_Ayman
 */ 


#include "TempSensor.h"
#include "HAL_ADC.h"



static	ADC_Handler_t ADC_Handler = {	.ADC_Intrrupet_Select = ADC_INIT_DISABLE ,.ADC_PreScaler = ADC_Presaler_2 ,
										.ADC_TRIG_SOURCE =ADC_TRIG_FREE_RUNNING ,.ADC_Vref_Select = ADC_Vref_AVCC,
										.ADC_Adjust_Select = ADC_Adjust_Right };


LM35_Status_t  LM35_Init(uint8_t Pin_Num , StrGPIO_t PORT)
{	
			 
		GPIO_InitTypeDef   PIN_CONFIG = {.mode = GPIO_MODE_OUTPUT , .pull = GPIO_NOPULL ,.pin = Pin_Num }; 
		HAL_GPIO_INIT_PIN(PORT , &PIN_CONFIG) ;	
		ADC_Init(&ADC_Handler);	
		return LM35_OK ;
}


float LM35_Read(void)
{
	float Res = 0 ; 
	ADC_Get_Value(&ADC_Handler , ADC_CH_0);
	Res = ((( ADC_Handler.ADC_Value )* 0.0048828 )/0.01);
	return Res;
	
}