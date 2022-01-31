/*
 * APP.h
 *
 * Created: 1/23/2022 6:21:17 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef APP_H_
#define APP_H_


#include <avr/io.h>
#include "HAL_GPIO.h"
#include "HAL_EXIT.h"
#include "HAL_I2c.h"
#include "HAL_SPI.h"
#include "HAL_Uart.h"
#include "MCP2515.h"

#include "KeyPad.h"
#include "Lcd-Driver.h"
#include "But_LED.h"
#include "EEPROM.h"

#include <stdlib.h>




//typedef enum {Wait_Action ,  TEST_UART_ONLY, TEST_SPI_ONLY, TEST_I2C_ONLY, TEST_ALL_COM_PROTOCOLs , EndOFStatus}FLowControl_t;

//extern FLowControl_t	ControlFlag  ; 


void APP_Init(void);


void APP_UPdate(void);



#endif /* APP_H_ */