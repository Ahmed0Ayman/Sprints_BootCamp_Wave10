/*
 * ADC.c
 *
 * Created: 5/13/2021 11:19:19 PM
 *  Author: Ahmed_Ayman
 */ 


#include "HAL_ADC.h"


float value =0 ;
/* private struct used by ADC to configure GPIO of selected pin */
PRIVATE GPIO_InitTypeDef ADC_GPIO ;


/*
 * brief  : this function used to start ADC conversion 
 * param. : void
 * return : void 
 */
PRIVATE void ADC_START(void);

PRIVATE void (*Ptr_Fun) (void) ; 



/*
 * brief  : this function used to start ADC conversion 
 * param. : void
 * return : void 
 */
PRIVATE void ADC_START(void)
{	
	ADCSRA |=1<<ADSC;
	
}/* END_FUN ADC_START()*/




/*
 * brief  : this function used to initialize ADC
 * param. : Handler pointer to the handler of ADC hold all configuration that done by user to initialize the ADC
 * return : void 
 */
PUBLIC void ADC_Init(ADC_Handler_t *Handler)
{


	/* first we here set the running mode this register not only for ADC */  
	SFIOR &=~ 0xe0; /* this step done if the application need to reconfiguration ADC */
	SFIOR |= Handler->ADC_TRIG_SOURCE << 5;



	/* then we will set control register( prescaler you also need to know ADC work only in CLK rang 50k -> 200k,interrupt ,..) */ 
	ClearREG(ADCSRA); /* clear to set a new configuration */
	ADCSRA = Handler->ADC_Intrrupet_Select | Handler->ADC_PreScaler | (1<<ADEN) | (1<<ADATE);
	
	
	ClearREG(ADMUX);
	ADMUX = Handler->ADC_Vref_Select | Handler->ADC_Adjust_Select ;
	
	
	if(Handler->ADC_Intrrupet_Select)
		sei();         /* enable global interrupt */


}/* END_FUN ADC_Init()*/







/*
 * brief  : this function used to initialize keypad
 * param. : KeyPadInit pointer to the handler of keypad
 * return : float measured voltage  
 */
PUBLIC void ADC_Get_Value(ADC_Handler_t *Handler,ADC_CH_t AdcChannel)
{
	uint16_t value =0 ;
			// first we initialize GPIO port to be ready to receive analog signal
			ADC_GPIO.mode = GPIO_MODE_INPUT ;
			ADC_GPIO.pin = (1<<AdcChannel) ;
			ADC_GPIO.pull = GPIO_NOPULL ;
			HAL_GPIO_Pin_Init(GPIOA , &ADC_GPIO);  /* set selected pin as GPIO analog pin */
		
		ADMUX &=~(0x1f);		  /* clear first before reconfiguration */
		ADMUX |= (AdcChannel);	 /* select channel */
		ADC_START();			/* start conversion */

		while(!((ADCSRA & (1<<ADIF))));   /* wait until conversion complete */
		ADCSRA |= 1<<ADIF;              /* clear interrupt flag by software in polling mode */
		
		
		if(Handler->ADC_Adjust_Select) /* if left adjust is selected */ 
		{
			value =  (ADCL>>6)|(ADCH);	/* ADCL must read first then ADCH to Re_enable access to ADCL & ADCH */
		}else{							   /* if right adjust is selected */ 
			value = (ADCL)|(ADCH<<8);
		}
		

		Handler->ADC_Value =  value;					

}/* END_FUN ADC_GET_VALUE()*/


PUBLIC void AComp_Init(AnalogComp_Handler_t * Handler)
{
	SFIOR &=  ~(1<<ACME);
	SFIOR |= (Handler->Analog_Comp_NegPin_Select) & (1<<ACME) ;
	ADMUX &=  ~(0xf8);
	ADMUX |= Handler->Analog_Comp_NegPin_Select & (0x07);
	
	if (Handler->Analog_Comp_Interrupt == AComp_IT_EN)
	{
		ACSR |= (1<<ACIE);
		sei();	
	}else{
		ACSR &=~(1<<ACIE);
	}
	
	
}


PUBLIC bool AComp_Get(void)
{
	
	return (ACSR & (1<<ACO)) ;
	
}


 void CallBackFun(void (*fun)(void))
 {
	Ptr_Fun = fun ; 
 }
 
 

 
 
 
 
 PUBLIC void ADC_Get_Value_IT(ADC_Handler_t *Handler,ADC_CH_t AdcChannel)
 {
	 // first we initialize GPIO port to be ready to receive analog signal
	 ADC_GPIO.mode = GPIO_MODE_INPUT ;
	 ADC_GPIO.pin = (1<<AdcChannel) ;
	 ADC_GPIO.pull = GPIO_NOPULL ;
	 HAL_GPIO_Pin_Init(GPIOA , &ADC_GPIO);  /* set selected pin as GPIO analog pin */
	 
	 ADMUX &=~(0x1f);		  /* clear first before reconfiguration */
	 ADMUX |= (AdcChannel);	 /* select channel */
	 ADC_START();
	 
	 
 }


 ISR(ADC_vect)
 {	

		if(ADC_Adjust_Left & ADMUX ) /* if left adjust is selected */ 
		{
			value =  (ADCL>>6)|(ADCH);	/* ADCL must read first then ADCH to Re_enable access to ADCL & ADCH */
		}else{							   /* if right adjust is selected */ 
			value = (ADCL)|(ADCH<<8);
		}
		
		value = ((( value )*0.0048828 )/0.01) ;
		if ((uint16_t)value >  Max_Temp )
		{
			SERVER_ADMIN_Error(ADMIN_ERROR_SET);
			ATM_Lock_Fun();
		}

 }