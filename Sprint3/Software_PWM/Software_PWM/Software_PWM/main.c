/*
 * Software_PWM.c
 *
 * Created: 1/14/2022 2:21:20 PM
 * Author : Ahmed_Ayman
 */ 
#define  F_CPU 16000000u
#include <avr/io.h>
#include "HAL_GPIO.h"
#include "TIMER_Interface.h"
#include "Utilites.h"
#include "util/delay.h"

#define TIM1_IN_USE				0
#define TIM2_IN_USE				1
#define TIM0_IN_USE				0



#if TIM1_IN_USE
TIMInit_t  Tim_PWM_Handler ={ .Instance = TIM1 ,.COMPConfig.TIM16Bit.CompAction = TIM_COMP_PIN_OUT_Normal  , .COMPConfig.TIM16Bit.CompNum = COMP_A_ , .TIM_Interrupt = TIM_1_IT_COMPA ,.TimPreScaler = TIM_1_Prescaler_1  }; 
	

#elif TIM2_IN_USE
TIMInit_t  Tim_PWM_Handler ={ .Instance = TIM2 ,.COMPConfig.TIM8Bit.CompAction = TIM_COMP_PIN_OUT_Normal   , .TIM_Interrupt = TIM_2_IT_COMP ,.TimPreScaler = TIM_2_Prescaler_1024 };

#elif TIM0_IN_USE
TIMInit_t  Tim_PWM_Handler ={ .Instance = TIM0 ,.COMPConfig.TIM8Bit.CompAction = TIM_COMP_PIN_OUT_Normal   , .TIM_Interrupt = TIM_0_IT_COMP ,.TimPreScaler = TIM_0_Prescaler_256 };	
#endif
	
uint8_t Speed[5] = {0,30,60,90,30} ; 
uint8_t SpeedIndex ; 


int main(void)
{
	
		DDRB = 0x40 ;
		DDRD = 0xff ;  
		Software_PWM_Init( GPIOD , GPIO_PIN_5 ,  &Tim_PWM_Handler );
		Software_PWM_Start (&Tim_PWM_Handler);
		Software_PWM_UpdateDuty(5 ,&Tim_PWM_Handler );
		sei();
		

		
		DDRC = 0x08 ; 
		PORTC = 0x08;
		
		
    /* Replace with your application code */
    while (1) 
    {
		



    }
}

