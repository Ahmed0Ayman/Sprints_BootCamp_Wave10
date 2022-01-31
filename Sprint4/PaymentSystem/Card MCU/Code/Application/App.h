 /******************************************************************************
 *
 * [MODULE]: APPLICATION
 *
 * [FILE NAME]: App.h
 *
 * [DESCRIPTION]: Header file for the Application
 *
 * [AUTHOR]: Ahmed Hassan
 *
 *******************************************************************************/

#ifndef APP_H_
#define APP_H_

#include "../Library/std_types.h"
#include "../Library/common_macros.h"
#include "../Library/micro_config.h"
#include "../MCAL/DIO/dio.h"
#include "../MCAL/I2C/i2c.h"
#include "../MCAL/UART/uart.h"
#include "../MCAL/SPI/spi.h"
#include "../HAL/EEPROM/external_eeprom.h"
#include "../MCAL/INTERRUPT/HAL_EXIT.h"

#define IDENTICAL             0
#define DATA_SIZE             29
#define EMPTY_EEPROM          0xFF
#define ANY_TIME_TO_LOG_IN    0x55
#define ADDRESS_SYSTEM_STATUS 0x0000
#define ADDRESS_NAME_STORED   0x0010
#define ADDRESS_PAN_STORED    0x0020
#define ADDRESS_PIN_STORED	  0x0030

/*******************************************************************************
 *                              New Prototypes                                 *
 *******************************************************************************/

/* card data struct */
typedef struct STR_cardData_t
{
   uint8_t au8_CardHolderName[11];
   uint8_t au8_PAN[11];
   uint8_t au8_PIN[6];
}STR_cardData_t;

/*******************************************************************************
 *                             Functions Prototypes                            *
 *******************************************************************************/
void App_init(void);
void App_Update(void);
void APP_receiveData(void);
void APP_NormalMode(void);
void APP_AddCard(void);
void APP_ModifyCard(void);
void APP_RemoveCard(void);
void APP_CheckSystem_Status(void);
void INT0_Init(void);

#endif /* APP_H_ */
