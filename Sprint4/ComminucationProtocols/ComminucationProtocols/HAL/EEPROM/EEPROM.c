/*
 * EEPROM.c
 *
 * Created: 1/24/2022 4:28:59 PM
 *  Author: Ahmed_Ayman
 */ 


#include "EEPROM.h"



static I2C_Handler_t  EEPROM_I2C_Handler = {.Init.I2C_Clk_Speed  =EEPROM_I2C_SPEED  ,.Init.I2C_IT_MODE = I2C_IT_DIS , .Init.I2C_SlaveADD = 0xAA,
.buffer = 0   ,.BufferSize = 0 };



EEPROM_Status_t EEPROM_Init(void)
{
	
	I2C_Init(&EEPROM_I2C_Handler);
	return EEPROM_OK ;
}



EEPROM_Status_t EEPROM_ReadPage(uint8_t PageNum , uint8_t * RXBuffer )
{
	if ((PageNum > EEPROM_NUMBER_OF_PAGES)||(RXBuffer == NULL))
	{
		return EEPROM_PARAM_ERROR ;
	}else
	{
		;
	}
	
		
	
	HAL_I2C_Mem_Read(&EEPROM_I2C_Handler , EEPROM_DIV_ADDRESS , (PageNum -1)*(EEPROM_NUMBER_OF_BYTES_FOR_PAGE) , 2  , RXBuffer , EEPROM_NUMBER_OF_BYTES_FOR_PAGE ) ;
	return EEPROM_OK ; 
}


EEPROM_Status_t EEPROM_WritePage(uint8_t PageNum , uint8_t * TXBuffer )
{
	if ((PageNum > EEPROM_NUMBER_OF_PAGES)||(TXBuffer == NULL))
	{
		return EEPROM_PARAM_ERROR ;
	}else
	{
		;
	}
	
	
	
	HAL_I2C_Mem_Write(&EEPROM_I2C_Handler , EEPROM_DIV_ADDRESS ,(PageNum -1)*(EEPROM_NUMBER_OF_BYTES_FOR_PAGE), 2 , TXBuffer , EEPROM_NUMBER_OF_BYTES_FOR_PAGE);
	return EEPROM_OK ;
	
}


EEPROM_Status_t EEPROM_ReadByteS(uint8_t PageNum ,uint8_t ByteNum , uint8_t * RXByte , uint8_t DataSize)
{
	
	if ((PageNum > EEPROM_NUMBER_OF_PAGES)||(RXByte == NULL) || ( DataSize <= 0))
	{
		return EEPROM_PARAM_ERROR ;
	}else
	{
		;
	}
	
	
	
	
	
	HAL_I2C_Mem_Read(&EEPROM_I2C_Handler , EEPROM_DIV_ADDRESS , (PageNum -1)*(ByteNum -1) , 2  , RXByte , DataSize) ;
	return EEPROM_OK ;	
}


EEPROM_Status_t EEPROM_WriteByteS(uint8_t PageNum ,uint8_t ByteNum , uint8_t  * TXByte , uint8_t DataSize)
{
	
	if (((PageNum > EEPROM_NUMBER_OF_PAGES)||(ByteNum > EEPROM_NUMBER_OF_PAGES))
		||(TXByte == NULL) || (DataSize <= 0))
	{
		return EEPROM_PARAM_ERROR ;
	}else
	{
		;
	}
	
	
	
	
	HAL_I2C_Mem_Write(&EEPROM_I2C_Handler , EEPROM_DIV_ADDRESS ,(PageNum -1)*(ByteNum -1), 2 , TXByte , DataSize);
	return EEPROM_OK ;
}

EEPROM_Status_t EEPROM_Reset(void)
{
	DDRC = 0x03 ; 
	HAL_GPIO_WRITEPIN(GPIOC ,  GPIO_PIN_1 , GPIO_PIN_SET) ;
	HAL_GPIO_WRITEPIN(GPIOC ,  GPIO_PIN_0 , GPIO_PIN_SET) ;
	for (uint8_t i = 0 ; i < 9 ; i++)
	{
//	HAL_GPIO_WRITEPIN(GPIOC ,  GPIO_PIN_1 , GPIO_PIN_SET) ;
	HAL_GPIO_WRITEPIN(GPIOC ,  GPIO_PIN_0 , GPIO_PIN_SET) ;
	_delay_us(5);
//	HAL_GPIO_WRITEPIN(GPIOC ,  GPIO_PIN_1 , GPIO_PIN_RESET) ;
	HAL_GPIO_WRITEPIN(GPIOC ,  GPIO_PIN_0 , GPIO_PIN_RESET) ;
	_delay_us(5);
	}
	
	// now we need to generate start condition
	I2C_EN_START();
	DDRC = 0x00 ;
	I2C_EN_STOP(); 
	return EEPROM_OK ;
}