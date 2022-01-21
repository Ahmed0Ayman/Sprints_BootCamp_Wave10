/*
 * KedPad.c
 *
 * Created: 5/5/2021 11:20:00 AM
 *  Author: Ahmed_Ayman
 */ 


#include  "KeyPad.h"


/* gpio structure used by this file to handle all gpio functions */
static GPIO_InitTypeDef KeyPad_gpio ;



/*
 * brief  : this function used to initialize keypad
 * param. : KeyPadInit pointer to the handler of keypad
 * return : void 
 */
void KeyPad_Initialization(KeyPad_t * KeyPad)
{
    /* for output pins  --> all colomn will set as autput pins*/
	KeyPad_gpio.mode = GPIO_MODE_OUTPUT ;
	for(uint8_t iter =0 ; iter < _NUM_OF_ColumnS ;iter++)
	{
		KeyPad_gpio.pin = KeyPad->ColumnPins[iter].Pin ;
		HAL_GPIO_INIT_PIN(KeyPad->ColumnPins[iter].Port , &KeyPad_gpio);
		HAL_GPIO_WRITEPIN(KeyPad->ColumnPins[iter].Port , KeyPad->ColumnPins[iter].Pin , WRIGHT_SECOND);
	}


	KeyPad_gpio.mode = GPIO_MODE_INPUT ;
	KeyPad_gpio.pull = WRIGHT_SECOND ;
	for(uint8_t iter =0 ; iter < _NUM_OF_ROWS ;iter++)
	{
		KeyPad_gpio.pin = KeyPad->RowPins[iter].Pin ;
		HAL_GPIO_INIT_PIN(KeyPad->RowPins[iter].Port , &KeyPad_gpio);
	}	
	


}/* END_FUN KeyPad_Initialization()*/


/*
 * brief  : this function used to return the pressed key 
 * param. : void
 * return : pressed character 
 */
char KeyPad_GetPressedKey(KeyPad_t * KeyPad)
{
	char Key =' ';
	for (uint8_t iterCOL = 0  ; iterCOL < _NUM_OF_ColumnS ; iterCOL++)
	{

		HAL_GPIO_WRITEPIN(KeyPad->ColumnPins[iterCOL].Port  , KeyPad->ColumnPins[iterCOL].Pin , WRIGHT_FIRST) ;
		for (uint8_t iterROW = 0 ; iterROW < _NUM_OF_ROWS ; iterROW++)
		{
			
			if ( HAL_GPIO_READPIN(KeyPad->RowPins[iterROW].Port ,KeyPad->RowPins[iterROW].Pin ) == WRIGHT_FIRST )
			{
				HAL_GPIO_WRITEPIN(KeyPad->ColumnPins[iterCOL].Port  , KeyPad->ColumnPins[iterCOL].Pin , WRIGHT_SECOND) ;
				return arr_KeyPad_char[iterROW][iterCOL] ;
			}else{
				;
			}
		}
		HAL_GPIO_WRITEPIN(KeyPad->ColumnPins[iterCOL].Port  , KeyPad->ColumnPins[iterCOL].Pin , WRIGHT_SECOND) ;

	}
	
return Key ;
}/* END_FUN GetPressedKey()*/