/*
 * APP_Library.h
 *
 * Created: 1/26/2022 9:33:23 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef APP_LIBRARY_H_
#define APP_LIBRARY_H_
/*
#include "ATM.h"
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
#include <stdlib.h>
#include <avr/pgmspace.h>
*/


#define  ADMIN_PASSWARD_LEN								(0x0au)
#define  ADMIN_USERNAME_LEN								ADMIN_PASSWARD_LEN
#define  ADMIN_ERROR_LEN								ADMIN_PASSWARD_LEN	
#define  ADMIN_TEMP_LEN									(0x05u)
#define	 ADMIN_MAX_DAILY_LEN							(0x06u)
#define  CARD_BALANCE_LEN								ADMIN_MAX_DAILY_LEN
#define  CARD_NAME_LEN									(0x0au)
#define  CARD_PAN_LEN									(0x0au)
#define  CARD_PIN_LEN									(0x05u)

#define ATM_UART_RXBuffer_SIZE							(0x0fu)
#define ATM_SPI_RXBuffer_SIZE							(CARD_NAME_LEN+1)


#define ATM_Request_Card_DATA_Pin						GPIO_PIN_7
#define ATM_Request_Card_DATA_Port						GPIOD


#define ATM_Card_Insert_Button_Pin						GPIO_PIN_5
#define ATM_Card_Insert_Button_Port						GPIOD

#define ATM_FORCE_MODE_Button_Pin						GPIO_PIN_6
#define ATM_FORCE_MODE_Button_Port						GPIOD

#define ATM_SELECT_MODE_Button_INDEX					(0x01u)
#define ATM_Insert_Card_Button_INDEX					(0x00u)


#define  ATM_SERVER_TOTAL_CAPCITY						(13797u)		/* Card */
#define  ATM_SERVER_CARD_START_ADD						(27594u)
#define  ATM_SERVER_FIRST_ADDRESS						(0x000u)




#define I2C_Buffer_SIZE									(0x0fu)
#define SPI_RXBuffer_SIZE								(0x0fu)
#define SPI_TXBuffer_SIZE								(0x0fu)
#define UART_RXBuffer_SIZE								(0x0fu)	
#define UART_TXBuffer_SIZE								(0x0fu)



#define SERVER_ADMIN_STEPSIZE							(0x0au)
#define SERVER_ADMIN_FLAG_START_ADD						(65000U)
#define SERVER_ADMIN_NAME_START_ADD						((uint16_t)SERVER_ADMIN_FLAG_START_ADD + (SERVER_ADMIN_STEPSIZE * 1 ))
#define SERVER_ADMIN_PASS_START_ADD						((uint16_t)SERVER_ADMIN_FLAG_START_ADD + (SERVER_ADMIN_STEPSIZE * 2 ))
#define SERVER_ADMIN_TEMP_START_ADD						((uint16_t)SERVER_ADMIN_FLAG_START_ADD + (SERVER_ADMIN_STEPSIZE * 3 ))
#define SERVER_ADMIN_ERROR_START_ADD					((uint16_t)SERVER_ADMIN_FLAG_START_ADD + (SERVER_ADMIN_STEPSIZE * 4 ))
#define SERVER_ADMIN_MAX_DAILY_AMOUNT					((uint16_t)SERVER_ADMIN_FLAG_START_ADD + (SERVER_ADMIN_STEPSIZE * 5 ))
#define SERVER_ADMIN_LOCK_START_ADD						((uint16_t)SERVER_ADMIN_FLAG_START_ADD + (SERVER_ADMIN_STEPSIZE * 6 ))





#define  ATM_SEARCH_BY_PAN								(0u)
#define  ATM_SEARCH_BY_NAME								(1u) 




#define	  ATM_ADD_Card									'1'
#define   ATM_REMOVE_CARD								'2'
#define   ATM_SEARCH_FOR_CARD_PAN						'3'
#define   ATM_SEARCH_FOR_CARD_NAME						'4'
#define   ATM_TOTAL_NUM_OF_CARDs						'5'
#define   ATM_RESET_DATA_BASE							'6'
#define   ATM_ADMIN_MODIFY								'7'
#define   ATM_EXIT_PROGRAMMING_MODE						'8'



#define  ATM_ADMIN_COMMAN_SET_PASS						'1' 
#define  ATM_ADMIN_COMMAN_SET_TEMP						'2'
#define  ATM_ADMIN_ERROR_CLEAR							'3'
#define  ATM_ADMIN_MAX_Daliy_Amount						'4'
#define  ATM_ADMIN_Exit									'5'
	
	
#define  ATM_DLEAY_IN_S									1500u







typedef enum {	SERVER_OPER_OK , SERVER_OPER_Exist , SERVER_OPER_Not_Exist ,
SERVER_OPER_FullSpace , SERVER_OPER_ERROR}SERVER_OPER_Status_t;



typedef enum {ADMIN_ERROR_SET , ADMIN_ERROR_CLEAR }Admin_ErrorAction_t;
	
	
	
	

typedef struct
{
	uint8_t CardName[CARD_NAME_LEN + 1 ] ;
	uint8_t CardPAN[CARD_PAN_LEN  + 1 ] ;
	uint8_t CardPIN[CARD_PIN_LEN  + 1 ] ;
	uint8_t	CardBalance[CARD_BALANCE_LEN +1]   ;
	
}CardData_t;




#define  ATM_CARD_BLOCK_SIZE							(sizeof(CardData_t)+1)





#endif /* APP_LIBRARY_H_ */