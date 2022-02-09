

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#define  F_CPU 16000000
#include <stdint.h>
#include <util/delay.h>
#include "HAL_GPIO.h"
#include "LCD_Pins.h"
#include <stdlib.h>
 #include "HAL_EXIT.h"
 #include "Stack.h"

typedef enum {LCD_Send_Char ,LCD_Send_Str , LCD_Send_Int , LCD_Send_Float , LCD_Send_Com}LCD_Oper_t;
typedef struct 
{
		StrGPIO_t        Port ;
		uint8_t          Pin  ;
}LCD_bit;

typedef struct   
{
	LCD_bit LcdBits[7];
}LcdBitSelect_t;

typedef enum  { LCD_OK , LCD_PARAM_ERROR , LCD_CONFIG_ERROR , LCD_BUSY }LCD_Status_t;

extern LcdBitSelect_t LcdBitSelect ;


#define RESET_CONTROL_BITS()																		\
for(int i =0 ; i < 3 ;i++)																			\
HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[i].Port,LcdBitSelect.LcdBits[i].Pin,GPIO_PIN_RESET);			\

#define SET_CONTROL_BITS()																			\
for(int i =0 ; i < 3 ;i++)																			\
HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[i].Port,LcdBitSelect.LcdBits[i].Pin,GPIO_PIN_SET);			\



/*some of common commands that used with LCD*/
#define LCD_COMMANED_CLEAR_LCD						0X01U
#define LCD_COMMANED_RETURN_HOME					0X02U
#define LCD_COMMANED_SHIFT_RIGHT					0X05U
#define LCD_COMMANED_SHIFT_LEFT						0X07U
#define LCD_COMMANED_CLEAR_CURSOR_ON				0X0AU
#define LCD_COMMANED_CLEAR_CURSOR_OFF				0X0CU
#define LCD_COMMANED2LINE_4_BIT_MODE                0x28U


void LCD_OS_Delay(uint16_t DelayMs);

void OS_LCD_Handler(LCD_Oper_t  Operation , uint8_t x , uint8_t y , void * Param);

/*
 *brief  : this function used to initialize (GPIO &LCD) 
 * return : void 
 */  
LCD_Status_t LCD_Initializaion(void);

/* 
 *brief  : this function used to send an character to LCD with the current location 
 * param. : Character the specific character to send to LCD 
 * return : void 
 */  
LCD_Status_t LCD_Send_Character_CurrLoc(uint8_t character);
uint8_t Static_LCD_Send_4BitData(uint8_t data);
/*
 * brief  : this function used to send an character to LCD with the chosen location 
 * param. :  y  is specify the new Y axises
 * param. :  x  is specify the new X axises
 * param. : character the specific character to send to LCD 
 * return : void 
 */
LCD_Status_t LCD_Send_Character_WithLoc(uint8_t y,uint8_t x,uint8_t character);

/*
 * brief  : this function used to send an string to LCD with the current location 
 * param. : Character the specific character to send to LCD 
 * return : void 
 */
LCD_Status_t LCD_Send_String_CurrLoc(char * StringOfCharacters);

/*
 * brief  : this function used to send command to LCD  
 * param. : command the specific command to send to LCD chose one of @ LCD_COMMANED_ 
 * return : void 
 */
LCD_Status_t LCD_Send_Command(uint8_t command);

/*
 * brief  : this function used to modify the current cursor location 
 * param. :  y  is specify the new Y axises
 * param. :  x  is specify the new X axises
 * return : void 
 */
LCD_Status_t LCD_Goto_Location(uint8_t y , uint8_t x);




/*
 * brief  : this function used to send an floating point number to LCD with the chosen location 
 * param. :  y  is specify y axises location start from 1 
 * param. :  x  is specify y axises location start from 1
 * param. : IntegerToDisplay this is the integer value that you want to display
 * return : void 
 */
LCD_Status_t LCD_Send_Float_CurLoc( float number );

/* 
 * brief  : this function used to send an 16 bit integer to LCD with the current location 
 * param. : IntegerToDisplay this is the integer value that you want to display
 * param. : NumberOfDigits number of digits of the integer number that you want to display
 * return : void 
 */
LCD_Status_t LCD_Send_Integer_CurrLoc(uint16_t IntegerToDisplay, uint8_t NumberOfDigits);





uint8_t LCD_Send_4BitData(uint8_t data);
#endif /* LCD-DRIVER_H_ */
