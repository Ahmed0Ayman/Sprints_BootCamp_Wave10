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
#include "HAL_ADC.h"
#include "KeyPad.h"
#include "Lcd-Driver.h"
#include "But_LED.h"
#include "EEPROM.h"
#include "ATM.h"
#include "TIMER_Interface.h"
#include "Motor.h"
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <string.h>




extern UART_Handler_t  UART_Handler;
extern SPI_Handler_t SPI_Handler;




void APP_Init(void);


void APP_UPdate(void);



#endif /* APP_H_ */