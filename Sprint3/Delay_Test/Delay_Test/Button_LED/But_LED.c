/*
 * But_LED.c
 *
 * Created: 1/11/2022 9:40:13 PM
 *  Author: Ahmed_Ayman
 */ 

#include "But_LED.h"




/* 
 * brief : this function used to initialize all Buttons  
 * parameter(input) : Buttons pointer to array of Buttons configurations 
 * return : status  
 */
ButtonStatus_t Button_Init(ButtonConfig_t * Buttons )
{
	
	if(Buttons == NULL )
	{
		return FUN_Param_ERROR ;
	}
	else
	{
		
		GPIO_InitTypeDef ButtoninInit ; 
		ButtoninInit.mode = GPIO_MODE_INPUT ; 
	
	
		for (uint8_t itera = 0 ; itera < NumberOFButtons ; itera++ )
		{
			ButtoninInit.pin = 	Buttons[itera].PINNum ;
			HAL_GPIO_INIT_PIN(Buttons[itera].PORT , &ButtoninInit) ;
		}
	
	
	
	}
	
	return  FUN_Ok ;
	
	
}






/* 
 * brief : this function used to read a specific Button 
 * parameter(input) : Buttons pointer to array of Buttons configurations 
 * parameter(input) : ButtonIndex index to the specific point that you need to read 
 * return : states of specified pin 
 */
ButtonState_t Button_Read( uint8_t ButtonIndex , ButtonConfig_t * Buttons )
{
	
	if ((Buttons == NULL) || (ButtonIndex > NumberOFButtons))
	{
		return -1 ;
	}else
	{
		return HAL_GPIO_READPIN(Buttons[ButtonIndex].PORT , Buttons[ButtonIndex].PINNum) ;
	}
	
}





/* 
 * brief : this function used to read a specific Button 
 * parameter(input) : Buttons pointer to array of Buttons configurations 
 * parameter(input) : ButtonIndex index to the specific point that you need to read 
 * return : array to all Buttons states  
 */
 uint8_t * Button_Read_ALL( uint8_t ButtonIndex , ButtonConfig_t * Buttons )
{
	
	static	uint8_t  ArrResult[NumberOFButtons] = {0};
		
	
	for (uint8_t itera = 0 ; itera < NumberOFButtons ; itera++ )
	{
		ArrResult[itera] =  HAL_GPIO_READPIN(Buttons[ButtonIndex].PORT , Buttons[ButtonIndex].PINNum) ;
	}
		
	
	return ArrResult ;
	
}




/* 
 * brief : this function used to initialize LEDs 
 * parameter(input) : LEDs pointer to array of LEDs  configurations 
 * parameter(input) : LEDIndex index to the specific point that you need to read 
 * return : array to all Function  states  
 */
LEDStatus_t LED_Init(LEDConfig_t * LEDs )
{
	
	if(LEDs == NULL)
	{
		return FUN_Param_ERROR ;
	}else
	{
	
	GPIO_InitTypeDef LEDinInit ;
	LEDinInit.mode = GPIO_MODE_OUTPUT ;
	
	
	for (uint8_t itera = 0 ; itera < NumberOFLEDs ; itera++ )
	{
		LEDinInit.pin = LEDs[itera].PINNum ;
		HAL_GPIO_INIT_PIN(LEDs[itera].PORT , &LEDinInit) ;
	}
	
	
	return  FUN_Ok ;
	
	
	}

}






/* 
 * brief : this function used to Write to specific LEDs 
 * parameter(input) : LEDs pointer to array of LEDs  configurations 
 * parameter(input) : LEDIndex index to the specific point that you need to write
 * return :			 Function  states  
 */
LEDState_t LED_Write( uint8_t LEDIndex , LEDState_t  LEDState ,  LEDConfig_t * LEDs )
{
	
		if((LEDs == NULL) ||(LEDIndex > NumberOFLEDs) )
		{
			return FUN_Param_ERROR ;
		}
		
		HAL_GPIO_WRITEPIN(LEDs[LEDIndex].PORT , LEDs[LEDIndex].PINNum , LEDState) ;
		
		
		return FUN_Ok ; 
	
	
}






/* 
 * brief : this function used to toggle Specific LED  
 * parameter(input) : LEDs pointer to array of LEDs  configurations 
 * parameter(input) : LEDIndex index to the specific point that you need to toggle  
 * return : array to all Function  states  
 */
LEDState_t LED_Toggle( uint8_t LEDIndex ,  LEDConfig_t * LEDs )
{
	
	if((LEDs == NULL) ||(LEDIndex > NumberOFLEDs) )
	{
		return FUN_Param_ERROR ;
	}
	
	HAL_GPIO_TOGGLE_PIN(LEDs[LEDIndex].PORT , LEDs[LEDIndex].PINNum ) ;
	
	
	return FUN_Ok ;
	
	
}




/* 
 * brief : this function used to toggle all LEDs  
 * parameter(input) : LEDs pointer to array of LEDs  configurations 
 * return : array to all Function  states  
 */

LEDState_t LED_Toggle_ALL( LEDConfig_t * LEDs )
{
	
		if((LEDs == NULL))
		{
			return FUN_Param_ERROR ;
		}else
		{
				for (uint8_t itera = 0 ; itera < NumberOFLEDs ; itera++ )
				{
					HAL_GPIO_TOGGLE_PIN(LEDs[itera].PORT , LEDs[itera].PINNum ) ;
				}
					
			}
				
			return  FUN_Ok ;
	
	
}




/* 
 * brief : this function used to Write 
 * parameter(input) : LEDs pointer to array of LEDs  configurations 
 * parameter(input) : ArrStates array of status that you need to write 
 * return : array to all Function  states  
 */
LEDStatus_t LED_Write_ALL( ButtonConfig_t * LEDs , LEDState_t* ArrStates)
{
	
	
	if((LEDs == NULL)||(ArrStates == NULL))
	{
		return FUN_Param_ERROR ;
	}else
	{
		
		
		for (uint8_t itera = 0 ; itera < NumberOFLEDs ; itera++ )
		{
			HAL_GPIO_WRITEPIN(LEDs[itera].PORT , LEDs[itera].PINNum , ArrStates[itera]) ;
		}
		
	}
		
		return  FUN_Ok ;	
	
	
}

