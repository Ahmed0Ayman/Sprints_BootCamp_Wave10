/*
 * SERVER_oper.c
 *
 * Created: 1/25/2022 9:46:54 PM
 *  Author: Ahmed_Ayman
 */ 


#include "Server.h"


SERVER_OPER_Status_t SERVER_OPER_DataBase_Reset(void)
{

	// add dummy card 
	uint16_t TXBuffer[2]  ={0,ATM_SERVER_CARD_START_ADD};
	EEPROM_WriteByteS(0, (uint8_t *)&TXBuffer ,4);			// write number of card 
	
	return SERVER_OPER_OK ;
}




SERVER_OPER_Status_t SERVER_OPER_Add_CARD(CardData_t * CardData)
{

	uint16_t NewAdd = 0 , NumOfCards  =0	;
	EEPROM_ReadByteS(0, (uint8_t *)&NumOfCards ,2);
	if(NumOfCards >= ATM_SERVER_TOTAL_CAPCITY)
	{
		return SERVER_OPER_FullSpace ; 
	}else if (SERVER_OPER_Search_CARD(CardData , ATM_SEARCH_BY_PAN) == -1 )
	{
		NewAdd = ATM_SERVER_CARD_START_ADD + ( NumOfCards++ * ATM_CARD_BLOCK_SIZE) ;
		EEPROM_WriteByteS(NewAdd , (uint8_t *)CardData , ATM_CARD_BLOCK_SIZE );											// store card data
		EEPROM_WriteByteS(NumOfCards*ATM_CARD_ADDRESS_SIZE+2 ,  (uint8_t *)&NewAdd , ATM_CARD_ADDRESS_SIZE );			// store card address
		EEPROM_WriteByteS(ATM_SERVER_FIRST_ADDRESS , (uint8_t *)&NumOfCards , ATM_CARD_ADDRESS_SIZE );
	}else
	{
		return SERVER_OPER_Exist ;
	}

	
	
	return SERVER_OPER_OK ;
}

	CardData_t TempCardData = {0};	uint16_t TempAdd = 0 , TempNumCards =0 ;
uint16_t SERVER_OPER_Search_CARD(CardData_t * CardData , uint8_t SearchBase )
{

	EEPROM_ReadByteS(0,(uint8_t*)&TempNumCards , 2);
	if(TempNumCards == 0)	{printf_P(PSTR("Hint!!!! Empty DataBase \n")) ; return -1  ;}
	for (uint16_t iter = 2 ; iter < ATM_SERVER_TOTAL_CAPCITY *  ATM_CARD_ADDRESS_SIZE ; iter += ATM_CARD_ADDRESS_SIZE)
	{
		EEPROM_ReadByteS(iter ,(uint8_t *)&TempAdd  , ATM_CARD_ADDRESS_SIZE);
		if (TempAdd != 0xffffu)
		{
			TempNumCards--;
			EEPROM_ReadByteS(TempAdd , (uint8_t *)&TempCardData , ATM_CARD_BLOCK_SIZE );
			if ( ATM_SEARCH_BY_PAN == SearchBase)
			{
				if (strcmp((char *)TempCardData.CardPAN,(char *)CardData->CardPAN)== 0 )
				{
					return TempAdd ;
				}
			}else{
				
				if (strcmp((char *)TempCardData.CardName,(char *)CardData->CardName)== 0 )
				{
					return TempAdd ;
				}

								
			}
			
							
			if (TempNumCards == 0)
			{
				return -1 ;
			}
		}else
		{
			;
		}
	}
	
	return -1 ; 
}



SERVER_OPER_Status_t SERVER_OPER_Remove_CARD(CardData_t * CardData)
{
	uint16_t TempIndex = SERVER_OPER_Search_CARD(CardData , ATM_SEARCH_BY_PAN) ;
	uint16_t ResetIndex = 0xffffu ;
	uint16_t NumOfCards =0 ; 
	if(TempIndex != -1)
	{
		EEPROM_WriteByteS(TempIndex ,(uint8_t *)&ResetIndex , 2 );
		EEPROM_ReadByteS(0 ,(uint8_t * )&NumOfCards ,2 );
		--NumOfCards ;
		EEPROM_WriteByteS(0 , (uint8_t * )&NumOfCards , 2);
	}else
	{
		return SERVER_OPER_Not_Exist ; 
	}
	

	return SERVER_OPER_OK ;
}




uint16_t SERVER_OPER_GetTotal_CARDNum(void)
{
		uint16_t Totla_CardNum  = 0 ;
		EEPROM_ReadByteS(ATM_SERVER_FIRST_ADDRESS ,(uint8_t *)&Totla_CardNum  , ATM_CARD_ADDRESS_SIZE);
		return Totla_CardNum ;
}





SERVER_OPER_Status_t SERVER_ADMIN_Set_Pass(uint8_t * StrName , uint8_t * Password)
{
		uint8_t AdminFlag  = 'S';
		EEPROM_WriteByteS(SERVER_ADMIN_FLAG_START_ADD ,(uint8_t *)&AdminFlag	, 1);		
		EEPROM_WriteByteS(SERVER_ADMIN_NAME_START_ADD ,(uint8_t *)StrName		, ADMIN_USERNAME_LEN-1);
		EEPROM_WriteByteS(SERVER_ADMIN_PASS_START_ADD ,(uint8_t *)Password		, ADMIN_PASSWARD_LEN-1);
	return SERVER_OPER_OK ;

}







SERVER_OPER_Status_t SERVER_ADMIN_Get_Pass(uint8_t * StrName , uint8_t * Password)
{
	uint8_t AdminFlag  = 0 ;
	EEPROM_ReadByteS(SERVER_ADMIN_FLAG_START_ADD ,(uint8_t *)&AdminFlag ,1);
	if (AdminFlag == 'S')
	{
		EEPROM_ReadByteS(SERVER_ADMIN_NAME_START_ADD ,(uint8_t *)StrName , ADMIN_USERNAME_LEN  );
		EEPROM_ReadByteS(SERVER_ADMIN_PASS_START_ADD ,(uint8_t *)Password , ADMIN_PASSWARD_LEN );
	}
	

	return SERVER_OPER_OK ;

}




SERVER_OPER_Status_t SERVER_ADMIN_Set_Temp(uint8_t * MaxTemp)
{
	uint16_t AdminFlag  =0 ;

	EEPROM_WriteByteS(SERVER_ADMIN_FLAG_START_ADD ,(uint8_t *)&AdminFlag ,ATM_CARD_ADDRESS_SIZE);
	EEPROM_WriteByteS(SERVER_ADMIN_TEMP_START_ADD ,(uint8_t *)MaxTemp ,ADMIN_TEMP_LEN);
	return SERVER_OPER_OK ;
}


SERVER_OPER_Status_t SERVER_ADMIN_Get_Temp(uint8_t * MaxTemp)
{
//	uint16_t AdminFlag  =0 ;
//	EEPROM_ReadByteS(SERVER_ADMIN_FLAG_START_ADD ,(uint8_t *)&AdminFlag ,ATM_CARD_ADDRESS_SIZE);
//	if(AdminFlag == 0)
	EEPROM_ReadByteS(SERVER_ADMIN_TEMP_START_ADD ,(uint8_t *)MaxTemp ,ADMIN_PASSWARD_LEN);
	
//	*MaxTemp = atoi((char *)Temp_MAxTemp);
	return SERVER_OPER_OK ;
}



SERVER_OPER_Status_t SERVER_ADMIN_Error(Admin_ErrorAction_t Action )
{
	uint8_t  Error[ADMIN_ERROR_LEN] = "ERROR" ; 
	if (Action == ADMIN_ERROR_SET)
	{
		EEPROM_WriteByteS(SERVER_ADMIN_ERROR_START_ADD ,(uint8_t *)Error ,ADMIN_ERROR_LEN);
		
	}else if (Action == ADMIN_ERROR_CLEAR )
	{
		memset(Error , 0 , ADMIN_ERROR_LEN);
		EEPROM_WriteByteS(SERVER_ADMIN_ERROR_START_ADD ,(uint8_t *)Error ,ADMIN_ERROR_LEN);
	}
	return SERVER_OPER_OK ; 
}

uint8_t SERVER_ADMIN_Error_Get(void)
{
	
	uint8_t  Error[ADMIN_ERROR_LEN] = {0} ;
	EEPROM_ReadByteS(SERVER_ADMIN_ERROR_START_ADD ,(uint8_t *)Error , ADMIN_ERROR_LEN);
	if (strcmp((char *)Error , "ERROR") == 0)
	{
		return 1 ;
	}else{
		return 0 ; 
	}
	return SERVER_OPER_OK ;
}








SERVER_OPER_Status_t SERVER_ADMIN_Set_MAximum_DailyAmount(uint8_t * MaxDailyAmount)
{
	EEPROM_WriteByteS(SERVER_ADMIN_MAX_DAILY_AMOUNT , MaxDailyAmount , ADMIN_MAX_DAILY_LEN );
	return SERVER_OPER_OK ;
}

