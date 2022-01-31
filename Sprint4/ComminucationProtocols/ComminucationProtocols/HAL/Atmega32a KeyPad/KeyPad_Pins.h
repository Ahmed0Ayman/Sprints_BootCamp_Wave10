/*
 * LCD_Pins.h
 *
 * Created: 1/17/2022 7:59:23 AM
 *  Author: Ahmed_Ayman
 */ 
#ifndef __KEYPAD__PINS__
#define __KEYPAD__PINS__

#include <stdint.h>
#include "HAL_GPIO.h"

#define  _NUM_OF_ROWS  3
#define  _NUM_OF_ColumnS  3



/* if Zero -> this keypad must be chanaged in hardware level to Pulldown Row Pins to Avoid noise */
#define _USE_PULL_UP    1	


typedef struct
{
	StrGPIO_t        Port ;
	uint8_t          Pin  ;
}KeyPad_Pins_t;




typedef struct
{
	KeyPad_Pins_t RowPins[_NUM_OF_ROWS];
	KeyPad_Pins_t ColumnPins[_NUM_OF_ColumnS];
}KeyPad_t;



extern KeyPad_t KeyPad ; 
extern uint8_t arr_KeyPad_char[_NUM_OF_ROWS][_NUM_OF_ColumnS];


#endif /* __KEYPAD__PINS__ */