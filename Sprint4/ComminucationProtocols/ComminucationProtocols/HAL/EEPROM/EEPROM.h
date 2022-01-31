/*
 * EEPROM.h
 *
 * Created: 1/24/2022 4:29:11 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#define  F_CPU 16000000u
#include "HAL_I2c.h"
#include "EEPROM_Config.h"
#include "HAL_GPIO.h"
#include <util/delay.h>

#define NULL ((void *)0)

typedef enum {EEPROM_OK , EEPROM_PARAM_ERROR , EEPROM_ERROR  }EEPROM_Status_t;


EEPROM_Status_t EEPROM_Init(void);

EEPROM_Status_t EEPROM_ReadPage(uint8_t PageNum , uint8_t * RXBuffer );


EEPROM_Status_t EEPROM_WritePage(uint8_t PageNum , uint8_t * TXBuffer );


EEPROM_Status_t EEPROM_ReadByteS(uint8_t PageNum ,uint8_t ByteNum , uint8_t * RXByte  , uint8_t DataSize);


EEPROM_Status_t EEPROM_WriteByteS(uint8_t PageNum ,uint8_t ByteNum , uint8_t  * TXByte , uint8_t DataSize);

EEPROM_Status_t EEPROM_Reset(void);



#endif /* EEPROM_H_ */