/*
 * LCD_Pins.c
 *
 * Created: 1/17/2022 7:59:40 AM
 *  Author: Ahmed_Ayman
 */ 

#include "KeyPad_Pins.h"
#include "HAL_GPIO.h"



uint8_t arr_KeyPad_char[_NUM_OF_ROWS][_NUM_OF_ColumnS] =

 						#if ((_NUM_OF_ColumnS == 4)&&(_NUM_OF_ROWS == 4))
								{{'7' , '8' , '9' ,'/'},
								{'4' , '5' , '6' , '*'},
								{'1' , '2' , '3' , '-'},
								{'c' , '0' , '=' , '+'}};
 						#elif ((_NUM_OF_ColumnS ==3)&&(_NUM_OF_ROWS == 4))
								{{'3' ,'2' , '1'},
								{'6' , '5' , '4'},
								{'9' , '8' , '7'},
								{'*' , '0' , '#'}};
 						#elif ((_NUM_OF_ColumnS ==3 )&&(_NUM_OF_ROWS == 3))										
								{{'1' , '2' , '3'},
								{'4' , '5' , '6'},
								{'7' , '8', '9'}};	
						#endif	/* if there is any none correct configuration this will generate an error */												 

	KeyPad_t KeyPad={	
						#if (_NUM_OF_ColumnS == 4)
						.ColumnPins[3].Port =	GPIOC,
						.ColumnPins[3].Pin	=	GPIO_PIN_7,
						#endif
						.ColumnPins[2].Port	=	GPIOC,
						.ColumnPins[2].Pin	=	GPIO_PIN_6,
						.ColumnPins[1].Port =	GPIOC,
						.ColumnPins[1].Pin	=	GPIO_PIN_5,
						.ColumnPins[0].Port =	GPIOC,
						.ColumnPins[0].Pin	=	GPIO_PIN_4,


						#if (_NUM_OF_ROWS == 4)
						.RowPins[3].Port	=	GPIOC ,
						.RowPins[3].Pin		=	GPIO_PIN_3,
						#endif						
						.RowPins[2].Port	=	GPIOC ,
						.RowPins[2].Pin		=	GPIO_PIN_2 ,
						.RowPins[1].Port	=	GPIOC ,
						.RowPins[1].Pin		=	GPIO_PIN_1 ,
						.RowPins[0].Port	=	GPIOC ,
						.RowPins[0].Pin		=	GPIO_PIN_0
				
		};