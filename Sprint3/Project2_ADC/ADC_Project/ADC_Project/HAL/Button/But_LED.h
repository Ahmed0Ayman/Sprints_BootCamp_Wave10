/*
 * But_LED.h
 *
 * Created: 1/11/2022 9:40:33 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef BUT_LED_H_
#define BUT_LED_H_
#include "HAL_GPIO.h"

#define		NumberOFButtons			2u
#define		NumberOFLEDs			NumberOFButtons


#define  NULL					((void *)0)

typedef struct
{
	GPIO_TypeDef * PORT ;
	uint8_t      PINNum  ;
}ButtonConfig_t;

typedef struct
{
	GPIO_TypeDef * PORT ;
	uint8_t      PINNum  ;
	
}LEDConfig_t;

typedef enum { FUN_Ok = 0  , FUN_Param_ERROR , FUN_Config_ERROR }ButtonStatus_t;

typedef enum  { State_LOW =0  ,  State_HIGH  }ButtonState_t;
	
typedef  ButtonStatus_t LEDStatus_t; 
typedef  ButtonState_t  LEDState_t ;




/* 
 * brief : this function used to initialize all Buttons  
 * parameter(input) : Buttons pointer to array of Buttons configurations 
 * return : status  
 */
ButtonStatus_t Button_Init(ButtonConfig_t * Buttons );





/* 
 * brief : this function used to read a specific Button 
 * parameter(input) : Buttons pointer to array of Buttons configurations 
 * parameter(input) : ButtonIndex index to the specific point that you need to read 
 * return : states of specified pin 
 */
ButtonState_t Button_Read( uint8_t ButtonIndex , ButtonConfig_t * Buttons );





/* 
 * brief : this function used to read a specific Button 
 * parameter(input) : Buttons pointer to array of Buttons configurations 
 * parameter(input) : ButtonIndex index to the specific point that you need to read 
 * return : array to all Buttons states  
 */
uint8_t * Button_Read_ALL( uint8_t ButtonIndex , ButtonConfig_t * Buttons );
 
 
 
 
 
 /* 
 * brief : this function used to initialize LEDs 
 * parameter(input) : LEDs pointer to array of LEDs  configurations 
 * parameter(input) : LEDIndex index to the specific point that you need to read 
 * return : array to all Function  states  
 */
LEDStatus_t LED_Init(LEDConfig_t * LEDs );







/* 
 * brief : this function used to Write to specific LEDs 
 * parameter(input) : LEDs pointer to array of LEDs  configurations 
 * parameter(input) : LEDIndex index to the specific point that you need to write
 * return :			 Function  states  
 */
LEDState_t LED_Write( uint8_t LEDIndex , LEDState_t  LEDState ,  LEDConfig_t * LEDs );





/* 
 * brief : this function used to toggle Specific LED  
 * parameter(input) : LEDs pointer to array of LEDs  configurations 
 * parameter(input) : LEDIndex index to the specific point that you need to toggle  
 * return : array to all Function  states  
 */

LEDState_t LED_Toggle( uint8_t LEDIndex ,  LEDConfig_t * LEDs );



/* 
 * brief : this function used to toggle all LEDs  
 * parameter(input) : LEDs pointer to array of LEDs  configurations 
 * parameter(input) : LEDIndex index to the specific point that you need to toggle  
 * return : array to all Function  states  
 */

LEDState_t LED_Toggle_ALL( LEDConfig_t * LEDs );



/* 
 * brief : this function used to Write 
 * parameter(input) : LEDs pointer to array of LEDs  configurations 
 * parameter(input) : ArrStates array of status that you need to write 
 * return : array to all Function  states  
 */
LEDStatus_t LED_Write_ALL( ButtonConfig_t * LEDs , LEDState_t* ArrStates);












#endif /* BUT_LED_H_ */