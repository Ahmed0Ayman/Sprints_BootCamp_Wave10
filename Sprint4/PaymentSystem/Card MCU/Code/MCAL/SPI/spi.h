 /******************************************************************************
 *
 * [MODULE]: SPI
 *
 * [FILE NAME]: spi.h
 *
 * [DESCRIPTION]: Header file for the SPI AVR driver
 *
 * [AUTHOR]: Ahmed Hassan
 *
 *******************************************************************************/
 
#ifndef SPI_H_
#define SPI_H_

#include "../../Library/micro_config.h"
#include "../../Library/std_types.h"
#include "../../Library/common_macros.h"
#include "../../Library/atmega32.h"
#include "../../MCAL/DIO/dio.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void SPI_initMaster(void); 
void SPI_initSlave(void);
void SPI_sendByte(const uint8_t data);
uint8_t SPI_recieveByte(void);
void SPI_sendString(const uint8_t * Str);
void SPI_receiveString(char * Str);

#endif
