/*
 * KeyPad.h
 *
 * Created: 5/5/2021 11:20:19 AM
 *  Author: Ahmed_Ayman
 */ 
# ifndef __KEYPAD_H__
#define __KEYPAD_H__


#include <stdint.h>
#include "HAL_GPIO.h"
#include "stdbool.h"

#include "KeyPad_Pins.h"

#if(!_USE_PULL_UP)

#define  WRIGHT_FIRST			GPIO_PIN_SET
#define  WRIGHT_SECOND			GPIO_PIN_RESET

#elif(_USE_PULL_UP)

#define  WRIGHT_FIRST			GPIO_PIN_RESET
#define  WRIGHT_SECOND			GPIO_PIN_SET


#endif

typedef struct
{
	  GPIO_TypeDef * Port ;
	   uint8_t      PinNum ;
	
}KeyPad_PinTypeDef;      /* this struct used to hold the config of each pin of keypad */


/*
 * brief : this typedef struct is a handler to the keypad hold 
 * all required information a bout keypad so this function first 
 * need this handler to initialize the keypad
 */
typedef struct 
{
  KeyPad_PinTypeDef PortColumn1 ;
  KeyPad_PinTypeDef PortColumn2 ;
  KeyPad_PinTypeDef PortColumn3 ;

  KeyPad_PinTypeDef PortRow1 ;
  KeyPad_PinTypeDef PortRow2 ;
  KeyPad_PinTypeDef PortRow3 ;
  
#if(!__Keypad_3_3__)
	#if (__Keypad_4_3__)
	KeyPad_PinTypeDef PortRow4 ;
	#endif
	#if(__Keypad_4_4__)    /* here this code will insert or removed depending on preprocessor configuration */
	KeyPad_PinTypeDef PortRow4 ;
	KeyPad_PinTypeDef PortColumn4 ;
 	#endif

#endif
}KeyPad_Handler_t ;


/*
 * brief  : this function used to return the pressed key 
 * param. : KeyPadInit pointer to the handler of keypad
 * return : pressed character 
 */
char KeyPad_GetPressedKey(KeyPad_t * KeyPad);

/*
 * brief  : this function used to initialize keypad
 * param. : KeyPadInit pointer to the handler of keypad
 * return : void 
 */
void KeyPad_Initialization(KeyPad_t * KeyPad);





#endif /*__KEYPAD_H__ */