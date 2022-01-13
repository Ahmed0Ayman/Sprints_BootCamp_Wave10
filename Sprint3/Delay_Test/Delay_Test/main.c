/*
 * Delay_Test.c
 *
 * Created: 1/13/2022 8:34:30 PM
 * Author : Ahmed_Ayman
 */ 



#include <avr/io.h>
#include "Utilites.h"
#include <avr/interrupt.h>
#include "TIMER_Interface.h"

#define  TEST_DELAY_WITHOUT_IT					0


#define  TEST_DELAY_WITH_IT_Periodic			0


#define  TEST_DELAY_WITH_IT_once				1

void Toggle_DELAY(void);
void SETPin_DELAY(void);
void RestPin_DELAY(void);

void DelayMs(uint16_t MsDelay);



TIMInit_t Tim_Delay_With_IT = {.COMPConfig.TIM8Bit.CompAction =  TIM_COMP_PIN_OUT_Normal , .TIMMode = TIM_MODE_CTC ,.Instance = TIM2 ,
.TimPreScaler =TIM_2_Prescaler_64  , .COMPConfig.TIM8Bit.CompValue = 250 , .TIM_Interrupt = TIM_2_IT_COMP};





TIMInit_t Tim_Delay_Without_IT = {.COMPConfig.TIM8Bit.CompAction =  TIM_COMP_PIN_OUT_Normal ,.Instance = TIM0 , .TIMMode = TIM_MODE_CTC ,.TimPreScaler = TIM_0_Prescaler_64 , .COMPConfig.TIM8Bit.CompValue = 250  };


int main(void)
{
	GPIO_InitTypeDef  PIN_CONFIG = {.mode = GPIO_MODE_OUTPUT , .pin = GPIO_PIN_0 };
	HAL_GPIO_INIT_PIN(GPIOB , &PIN_CONFIG);
	

	#if		TEST_DELAY_WITHOUT_IT
	
	/* initialization for Delay without IT sequence */
	TIM_OutCompareModeInit(&Tim_Delay_Without_IT);
	TIM_Start(&Tim_Delay_Without_IT);
	#elif	TEST_DELAY_WITH_IT_Periodic

	/* initialization for Delay with IT sequence */
	Utilites_DelayMs_IT(&Tim_Delay_With_IT , 500 , Delay_Periodic ,Toggle_DELAY );
	

	

	#endif

	sei();
	while (1)
	{

		#if		TEST_DELAY_WITHOUT_IT
		
		DelayMs(300);
		PORTB ^= 0x80 ;
		DelayMs(500);
		PORTB ^= 0x80 ;	
		
			
		#elif TEST_DELAY_WITH_IT_once
			
			while(Utilites_DelayMs_IT(&Tim_Delay_With_IT , 300 , Delay_Once ,SETPin_DELAY) != 0);
			
			while(Utilites_DelayMs_IT(&Tim_Delay_With_IT , 500 , Delay_Once ,RestPin_DELAY ) != 0 );
		#endif
		
	}
}



void	DelayMs(uint16_t MsDelay)
{
	
	for(uint16_t ietrator=0;ietrator<MsDelay;ietrator++)
	{
		
		while(!(TIFR &(1<<OCF0)));
		TIFR |= 1<<OCF0;
	}
}




/* jest for test delay with IT */
void Toggle_DELAY(void)
{

	HAL_GPIO_TOGGLE_PIN(GPIOB , GPIO_PIN_7);
	
}

void SETPin_DELAY(void)
{

	HAL_GPIO_WRITEPIN(GPIOB  , GPIO_PIN_7 , GPIO_PIN_SET);

}


void RestPin_DELAY(void)
{

	HAL_GPIO_WRITEPIN(GPIOB  , GPIO_PIN_7 , GPIO_PIN_RESET);
}