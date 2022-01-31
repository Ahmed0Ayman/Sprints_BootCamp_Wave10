this is a brief of how to use this driver 

/*  just for simple operation follow the following instruction */

1 - create an ADC  handler 

ADC_Handler_t ADCHandler = {
	.ADC_Intrrupet_Select = ADC_INIT_ENABLE ,
	.ADC_Adjust_Select    = ADC_Adjust_Right ,
	.ADC_PreScaler        = ADC_Presaler_128 ,
	.ADC_TRIG_SOURCE      = ADC_TRIG_EXTI_0 ,
	.ADC_Vref_Select      = ADC_Vref_AVCC 
};

2-  call initialization function 

	ADC_INIT(&ADCHandler);

3- call the get value function 

		ADC_Get_Value(&ADCHandler,ADC_CH_0);

4 - you can during initialization choose one of trigger avalible mode 

5 - you need to no that you are choose external Volatage referance AVCC 
so you need to conect it through Proteous or Real MCU */


 