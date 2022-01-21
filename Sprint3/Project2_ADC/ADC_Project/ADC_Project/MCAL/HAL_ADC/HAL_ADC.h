
/*
 * ADC.h
 *
 * Created: 5/13/2021 11:19:31 PM
 *  Author: Ahmed_Ayman
 */ 

#ifndef __ADC__
#define __ADC__


#include <stdint.h>
#include "HAL_GPIO.h"
#include <avr/interrupt.h>
#include <stdbool.h>


#define  PRIVATE static            /* file access only */
#define  PUBLIC                   /* client access */

/* channel number select the user must select one of them */

typedef enum {ADC_CH_0 , ADC_CH_1 ,ADC_CH_2 ,ADC_CH_3 ,ADC_CH_4,ADC_CH_5,ADC_CH_6,ADC_CH_7  }ADC_CH_t;


/* prescaler select value as far as you know the ADC in ATMEGA32a work only in clock range 50K - 200K */
typedef enum { ADC_Presaler_2=0 , ADC_Presaler_4 ,	ADC_Presaler_16 ,ADC_Presaler_32
,ADC_Presaler_64 ,ADC_Presaler_128}ADC_Prescaller_t;


/* trigger source select the user must select one of these */

typedef enum {ADC_TRIG_FREE_RUNNING =0 ,ADC_TRIG_ANALOG_COMP ,ADC_TRIG_EXTI_0, ADC_TRIG_TIM0_COMP , ADC_TRIG_TIM0_OV
,ADC_TRIG_TIM1_COMPB ,ADC_TRIG_TIM1_OV,ADC_TRIG_TIM1_IC_CAPTURE }ADC_Trigger_t;


typedef enum {	ACOMP_PIN_AIN_1 =0x00 , ACOMP_PIN_ADC_0= 0x08 ,AComp_PIN_ADC1, AComp_PIN_ADC2 ,AComp_PIN_ADC3 ,
AComp_PIN_ADC4,AComp_PIN_ADC5 ,AComp_PIN_ADC6 ,AComp_PIN_ADC7}ACOMP_PIN_t;




typedef enum { AComp_OUT_DIS,AComp_OUT_EN=0x20}AComp_OUT_t;
typedef enum { AComp_IT_DIS,AComp_IT_EN = 0x08u}Acomp_IT_t;




typedef struct
{
	ADC_Trigger_t		ADC_TRIG_SOURCE ;		   /* select one value of  ADC_TRIG     _ */
	ADC_Prescaller_t	ADC_PreScaler ;			  /* select one value of ADC_Presaler_  */
	uint8_t ADC_Adjust_Select ;		 /* select one value of ADC_Adjust_   */
	uint8_t ADC_Intrrupet_Select;	/* select one value of ADC_INIT_    */
	uint8_t ADC_Vref_Select ;	   /* select one value of ADC_Vref_   */
	uint16_t ADC_Value ;
	
}ADC_Handler_t;     /* struct used to hold all ADC configurations */

typedef struct
{
	ACOMP_PIN_t		Analog_Comp_NegPin_Select ; /* must be one of AComp_PIN_ */
	AComp_OUT_t		Analog_Comp_OutEnable ;     /* must be AComp_EN or AComp_DIS */
	Acomp_IT_t		Analog_Comp_Interrupt ;    /* must be one of AComp_INIT_ */
	
}AnalogComp_Handler_t;  /* struct used to hold all AComp configurations */



	
/* adjust value left or right select one of these */
#define ADC_Adjust_Left              0x20u
#define ADC_Adjust_Right  		     0x00u

#define  ADC_INIT_ENABLE             0x08u
#define  ADC_INIT_DISABLE            0x00u


/* hint if you try to use external voltage reference you will make a lite bit modification is this library */
#define  ADC_Vref_Intrnal2_56v       0xc0u
#define  ADC_Vref_AVCC               0x40u

/* Analog comparator Negative Pin select */



#define  AComp_EN                   0x00u
#define  AComp_DIS					0x80u











/*
 * brief  : this function used to initialize ADC
 * param. : Handler pointer to the handler of ADC hold all configuration that done by user to initialize the ADC
 * return : void 
 */
PUBLIC void ADC_Init(ADC_Handler_t *Handler);





/*
 * brief  : this function used to initialize keypad
 * param. : KeyPadInit pointer to the handler of keypad
 * return : void 
 */
PUBLIC void ADC_Get_Value(ADC_Handler_t *Handler,ADC_CH_t AdcChannel);


PUBLIC void AComp_Init(AnalogComp_Handler_t * Handler);

PUBLIC void AComp_Start(AnalogComp_Handler_t * handler);


PUBLIC bool AComp_Get(void);


PUBLIC  void CallBackFun(void (*fun)(void));


PUBLIC void ADC_Get_Value_IT(ADC_Handler_t *Handler,ADC_CH_t AdcChannel);


#endif