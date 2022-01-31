/*
 * ATM.h
 *
 * Created: 1/24/2022 11:24:46 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef APP_UTILITIES_H_
#define APP_UTILITIES_H_


#include <stdlib.h>
#include <string.h>
#include "HAL_Uart.h"
#include "HAL_SPI.h"
#include "HAL_GPIO.h"
#include "Lcd-Driver.h"
#include "stdio.h"
#include "But_LED.h"
#include "APP_Library.h"
#include "Server.h"
#include "KeyPad.h"
#include <avr/pgmspace.h>

#define  MaxDailyWithDraw_Size  CARD_NAME_LEN 

extern UART_Handler_t  UART_Handler;
extern SPI_Handler_t SPI_Handler;


uint8_t ATM_Terminal_GetString(uint8_t * RxBuffer , uint8_t BufferSize );


uint8_t ATM_Terminal_PutString(char * RxBuffer );



extern ButtonConfig_t ATM_Buttons[2] ;


void ATM_Button_Init(void);



void ATM_Programming_mode(void);


void ATM_Lock_Fun(void);



void ATM_Operation_mode(void);



uint8_t * Print_F(uint8_t const * const Str_F);



#endif /* APP_UTILITIES_H_ */