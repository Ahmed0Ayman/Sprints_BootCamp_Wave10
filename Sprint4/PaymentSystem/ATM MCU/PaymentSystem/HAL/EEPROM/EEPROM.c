/*
 * EEPROM.c
 *
 * Created: 1/24/2022 4:28:59 PM
 *  Author: Ahmed_Ayman
 */ 


#include "EEPROM.h"




extern I2C_Handler_t I2C_Handler ; 


EEPROM_Status_t EEPROM_Init(void)
{
	
	I2C_Init(&I2C_Handler);
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
	
		
	
	HAL_I2C_Mem_Read(&I2C_Handler , EEPROM_DIV_ADDRESS , (PageNum )*(EEPROM_NUMBER_OF_BYTES_FOR_PAGE) , ATM_CARD_ADDRESS_SIZE  , RXBuffer , EEPROM_NUMBER_OF_BYTES_FOR_PAGE ) ;
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
	
	
	
	HAL_I2C_Mem_Write(&I2C_Handler , EEPROM_DIV_ADDRESS ,(PageNum )*(EEPROM_NUMBER_OF_BYTES_FOR_PAGE), ATM_CARD_ADDRESS_SIZE , TXBuffer , EEPROM_NUMBER_OF_BYTES_FOR_PAGE);
	return EEPROM_OK ;
	
}


EEPROM_Status_t EEPROM_ReadByteS(uint16_t StartByteNum , uint8_t * RXByte , uint8_t DataSize)
{
	
	if ((RXByte == NULL) || ( DataSize <= 0))
	{
		return EEPROM_PARAM_ERROR ;
	}else
	{
		;
	}
	
		

		
		uint16_t PageNum =0 , ByteAddress =0 ;
		PageNum = StartByteNum/EEPROM_NUMBER_OF_BYTES_FOR_PAGE ;
		ByteAddress = StartByteNum%EEPROM_NUMBER_OF_BYTES_FOR_PAGE ;
		if((ByteAddress + DataSize ) > EEPROM_NUMBER_OF_BYTES_FOR_PAGE )
		{
			HAL_I2C_Mem_Read(&I2C_Handler , EEPROM_DIV_ADDRESS , StartByteNum , ATM_CARD_ADDRESS_SIZE , RXByte ,
							  EEPROM_NUMBER_OF_BYTES_FOR_PAGE - ByteAddress);
			HAL_I2C_Mem_Read(&I2C_Handler , EEPROM_DIV_ADDRESS , (PageNum +1)*(EEPROM_NUMBER_OF_BYTES_FOR_PAGE)   ,
						ATM_CARD_ADDRESS_SIZE , RXByte + EEPROM_NUMBER_OF_BYTES_FOR_PAGE - ByteAddress , DataSize - EEPROM_NUMBER_OF_BYTES_FOR_PAGE + ByteAddress);
		}
		else{
			HAL_I2C_Mem_Read(&I2C_Handler , EEPROM_DIV_ADDRESS , StartByteNum , ATM_CARD_ADDRESS_SIZE , RXByte , DataSize );
		}
	
	return EEPROM_OK ;	
}

EEPROM_Status_t EEPROM_WriteByteS(uint16_t StartByteNum , uint8_t  * TXByte , uint8_t BufferSize)
{
	uint16_t PageNum =0 , ByteAddress =0  ;
	if ((TXByte == NULL) || (BufferSize <= 0))
	{
		return EEPROM_PARAM_ERROR ;
	}else
	{
		;
	}
	

		PageNum = StartByteNum/EEPROM_NUMBER_OF_BYTES_FOR_PAGE ;
		ByteAddress = StartByteNum%EEPROM_NUMBER_OF_BYTES_FOR_PAGE ;

	if((ByteAddress + BufferSize ) > EEPROM_NUMBER_OF_BYTES_FOR_PAGE )
	{
		HAL_I2C_Mem_Write(&I2C_Handler , EEPROM_DIV_ADDRESS , StartByteNum , ATM_CARD_ADDRESS_SIZE , TXByte ,  
							EEPROM_NUMBER_OF_BYTES_FOR_PAGE - ByteAddress );
		HAL_I2C_Mem_Write(&I2C_Handler , EEPROM_DIV_ADDRESS , (PageNum +1)*(EEPROM_NUMBER_OF_BYTES_FOR_PAGE) , ATM_CARD_ADDRESS_SIZE , TXByte + (EEPROM_NUMBER_OF_BYTES_FOR_PAGE - ByteAddress), 
							 BufferSize - EEPROM_NUMBER_OF_BYTES_FOR_PAGE + ByteAddress);	
	}else{
		HAL_I2C_Mem_Write(&I2C_Handler , EEPROM_DIV_ADDRESS , StartByteNum , ATM_CARD_ADDRESS_SIZE , TXByte , BufferSize);
	}
		/*	
	to specify page number Byte address / 128 
		to specify the Byte number in page Byte address % 128
		to specify if this write can be used in one write
		if(buffer size + byte address in p[age  > 128 )
		{
			this mean we need to write into to times 	
		}else
		{
			this means this can be done in one transaction 
		}
	*/
return EEPROM_OK ; 	

}


