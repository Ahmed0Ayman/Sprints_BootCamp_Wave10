 /*
 * Lcd_Driver.c
 *
 * Created: 4/12/2021 3:14:06 PM
 * Author : Ahmed_Ayman
 */
#include "LCD-Driver.h"


pstr_Stack_t Stack_Handler;




/* start position for x & y location as described in data sheet*/ 
static uint8_t column_position [2] = {0x80,0xc0};
uint16_t LCD_DelayOS = 0  ; 
extern uint8_t LCD_PendingStart ; 
extern EXIT_Handler_t  EXIT_Handler ;
uint8_t LCD_PendingStat = 0 ; 
void LCD_OS_Delay(uint16_t DelayMs);

/*
 * brief  : this function used to send Data to LCD in 4 bit form 
 * param. : data the specific byte that you want to send to LCD 
 * return : void 
 */

/*
 * brief  : this function used to set enable bit in LCD
 * return : void 
 */
static void LCD_Triger_Enable(void);


/*
 * brief  : this function used to set enable bit in LCD
 * return : void 
 */


static void LCD_Triger_Enable(void)
{
	
	HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[LCD_BIT_E_PIN].Port,LcdBitSelect.LcdBits[LCD_BIT_E_PIN].Pin,GPIO_PIN_SET);  // set enable pin
	_delay_us(1);
	HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[LCD_BIT_E_PIN].Port,LcdBitSelect.LcdBits[LCD_BIT_E_PIN].Pin,GPIO_PIN_RESET);  // set enable pin
//	_delay_ms(1);	
	//LCD_OS_Delay(2);
} /* END_FUN LCD_Triger_Enable()*/

/*
 * brief  : this function used to send Data to LCD in 4 bit form 
 * param. : data the specific byte that you want to send to LCD 
 * return : void 
 */

#define  HighNibble 0
#define  LowNibble	1
#define  WaitDelay	2


uint8_t TempData  = 0;
uint8_t LCD_State = 0 , LCD_Prev_State;
uint8_t LCD_Send_4BitData(uint8_t data)
{

static uint8_t Tempdata1 ; 
switch(LCD_State)
{ 
	case HighNibble :
		Tempdata1  = data;
		for(int i =3 ; i < 7 ;i++)																			
		HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[i].Port,LcdBitSelect.LcdBits[i].Pin,((1<<(i+1))&(Tempdata1))>>(i+1));	/* set the high nibble */
		LCD_Triger_Enable();
		LCD_State = WaitDelay ; 
		LCD_Prev_State = HighNibble ;	
		break;
	case LowNibble :
		for(int i =3 ; i < 7 ;i++)
		HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[i].Port,LcdBitSelect.LcdBits[i].Pin,((1<<(i-3))&(Tempdata1))>>(i-3));	/* set the high nibble */
		LCD_Triger_Enable();
		LCD_State = WaitDelay ;
		LCD_Prev_State = LowNibble ;
		break; 
	case  WaitDelay : 
			if(LCD_PendingStat == 0)
			{

				if(LCD_Prev_State == HighNibble)
				{
					LCD_State = LowNibble ;
				}else if (LCD_Prev_State == LowNibble)
				{
					LCD_State = HighNibble ;
					return 1 ;
				}	
			}	
		break;
		
	default: 
	break;
}
		return 0 ;

} /* END_FUN LCD_Send_4BitData()*/



/*
 * brief  : this function used to send an character to LCD with the current location 
 * param. : Character the specific character to send to LCD 
 * return : void 
 */ 
LCD_Status_t LCD_Send_Character_CurrLoc(uint8_t character)
{
	TempData = character ;
	if (LCD_PendingStart == 1)
	{
		return LCD_BUSY ;
	}else
	{
		HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[LCD_BIT_RS_PIN].Port,LcdBitSelect.LcdBits[LCD_BIT_RS_PIN].Pin,GPIO_PIN_SET);  // set enable pin
		HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[LCD_BIT_RW_PIN].Port,LcdBitSelect.LcdBits[LCD_BIT_RW_PIN].Pin,GPIO_PIN_RESET);  // set enable pin
		LCD_PendingStart = 1  ;
	}
	
	return LCD_OK ;
} /* END_FUN LCD_Send_Character_CurrLoc()*/




/*
 * brief  : this function used to send command to LCD  
 * param. : command the specific command to send to LCD chose one of @ LCD_COMMANED_ 
 * return : void 
 */
LCD_Status_t LCD_Send_Command(uint8_t command)
{
	static uint8_t StatCommand ; 
	LCD_Status_t RetVal = 0 ; 
	switch(StatCommand)
	{
		case 0 : 
			if (LCD_PendingStart == 1)
			{
				return LCD_BUSY ; 
			}
			TempData = command ;
			HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[LCD_BIT_RS_PIN].Port,LcdBitSelect.LcdBits[LCD_BIT_RS_PIN].Pin,GPIO_PIN_RESET);  // set enable pin
			HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[LCD_BIT_RW_PIN].Port,LcdBitSelect.LcdBits[LCD_BIT_RW_PIN].Pin,GPIO_PIN_RESET);  // set enable pin
			LCD_PendingStart = 1  ;
			StatCommand = 1 ;
			RetVal  = LCD_BUSY ; 
			break;
			
		case 1 :
			if (LCD_PendingStart == 0)
			{
					RetVal = LCD_OK ;
					StatCommand = 0 ; 
			}else
			{
				RetVal = LCD_BUSY ; 

			}
			break; 
		default: 
		
		break; 

	}
return RetVal ; 
} /* END_FUN LCD_Send_Command()*/






/*
 * brief  : this function used to send an string to LCD with the current location 
 * param. : Character the specific character to send to LCD 
 * return : void 
 */
LCD_Status_t LCD_Send_String_CurrLoc(char *StringOfCharacters)
{
		uint8_t  TempChar = 0 ;
		while (1)
		{
			Stack_Push(&Stack_Handler, (uint8_t *)StringOfCharacters);
			if (*StringOfCharacters == '\0')
			{
				break;
			}
			StringOfCharacters++ ;
		}
		Stack_Pop(&Stack_Handler, &TempChar);
		LCD_Send_Character_CurrLoc(TempChar) ;

	return LCD_OK ;
} /* END_FUN LCD_Send_String_CurrLoc()*/




/*
 * brief  : this function used to modify the current cursor location 
 * param. :  y  is specify the new Y axises
 * param. :  x  is specify the new X axises
 * return : void 
 */
LCD_Status_t LCD_Goto_Location(uint8_t y , uint8_t x)
{
	while( LCD_Send_Command(column_position[y-1]+(x-1)) == LCD_BUSY );

	return LCD_OK ;	
} /* END_FUN LCD_Goto_Location()*/




/*
 * brief  : this function used to initialize (GPIO &LCD) 
 * return : void 
 */ 
LCD_Status_t LCD_Initializaion(void)
{
	GPIO_InitTypeDef LCD_GPIO_Handler ;
	
	
	_delay_ms(20);
	/* Set portB pin 1,2,3 as output */
	LCD_GPIO_Handler.mode = GPIO_MODE_OUTPUT ;
	LCD_GPIO_Handler.pull =GPIO_NOPULL ;
	
	
	
	
	for(int i =0 ; i < 7 ;i++)
	{
		LCD_GPIO_Handler.pin = LcdBitSelect.LcdBits[i].Pin ;
		HAL_GPIO_INIT_PIN(LcdBitSelect.LcdBits[i].Port,&LCD_GPIO_Handler);
	}

	/* LCD Initialization command*/
	while( LCD_Send_Command(0x33U) == LCD_BUSY ) ; 
	while( LCD_Send_Command(0x32U)== LCD_BUSY ) ; 	
	while( LCD_Send_Command(LCD_COMMANED2LINE_4_BIT_MODE)== LCD_BUSY ) ; 	
	while( LCD_Send_Command(LCD_COMMANED_CLEAR_CURSOR_OFF)== LCD_BUSY ) ; 	
	while( LCD_Send_Command(LCD_COMMANED_CLEAR_LCD)== LCD_BUSY ) ; 	
	

	return LCD_OK ;
	
} /* END_FUN LCD_Initializaion()*/




/*
 * brief  : this function used to send an string to LCD with the chosen location 
 * param. :  y  is specify y axises location start from 1
 * param. :  x  is specify y axises location start from 1
 * param. : StringOfCharacters pointer to string that you want to display
 * return : void 
 */



/*
 * brief  : this function used to send an floating point number to LCD with the chosen location 
 * param. :  y  is specify y axises location start from 1 
 * param. :  x  is specify y axises location start from 1
 * param. : IntegerToDisplay this is the integer value that you want to display
 * return : void 
 */
LCD_Status_t LCD_Send_Float_CurLoc( float number )
{
	uint16_t intValue = (uint16_t)number;                    /* calculate the int value */
	float diffValue = (number - (float)intValue);              
	uint16_t decimalValue = (uint16_t)(diffValue * pow(10,2));  /* calculate the float value */
	
	
	LCD_Send_Integer_CurrLoc(intValue,5);
	LCD_Send_Character_CurrLoc('.');
	LCD_Send_Integer_CurrLoc(decimalValue,5);
	
	
		return LCD_OK ;
} /* END_FUN LCD_Send_Float_Withloc()*/





/*
 * brief  : this function used to send an 16 bit integer to LCD with the current location 
 * param. : IntegerToDisplay this is the integer value that you want to display
 * param. : NumberOfDigits number of digits of the integer number that you want to display
 * return : void 
 */
LCD_Status_t LCD_Send_Integer_CurrLoc(uint16_t IntegerToDisplay, uint8_t NumberOfDigits)
{
		char StringToDisplay[NumberOfDigits];   /* create array with required size */ 
		itoa(IntegerToDisplay, StringToDisplay,10); /* convert from int num. to char num. */
		LCD_Send_String_CurrLoc(StringToDisplay);  /* print char array on the screen */
		return LCD_OK ;
} /* END_FUN LCD_Send_Integer_CurrLoc()*/




