/*
 * ATM.c
 *
 * Created: 1/24/2022 11:24:29 PM
 *  Author: Ahmed_Ayman
 */ 

#include "ATM.h"



#define 	LCD_Print_WELCOME_OPERATE				0
#define 	LCD_Print_MODE							1
#define 	LCD_Print_PLEASE_ENTER					2
#define 	LCD_Print_CARD							3
#define 	LCD_Print_ENTER_THE						4
#define 	LCD_Print_TRANSAC_AMOUNT				5
#define 	LCD_Print_TRANSACTION					6
#define 	LCD_Print_Wrong							7
#define 	LCD_Print_Transaction					8	
#define		LCD_Print_ERROR_Temp					9
#define 	LCD_Print_CALL_XXXXXX					10
#define     LCD_Print_Dragons						11
#define     LCD_Print_ATM_System					12
#define		LCD_Print_enter_Programing				13
#define		LCD_Print_Mode							14
#define		LCD_Print_Programing_Mode				15
#define     LCD_Print_CARD							16
#define     LCD_Print_NOT_READY						17
#define     LCD_Print_ENTER_THANK					18
#define     LCD_Print_YOU							19
#define     LCD_Print_Success						20


extern uint16_t Max_Temp ; 


static uint8_t ATM_Get_UserCommand(void);
 uint8_t ATM_Terminal_GetString(uint8_t * RxBuffer , uint8_t BufferSize );
static void ATM_Add_CardData(void);
static void ATM_Remove_Card(void);
static SERVER_OPER_Status_t ATM_Search_Card_WithPAN(void);


static void ATM_Collect_CardData(CardData_t * CardData);


uint8_t   const LCD_StrF[][20] PROGMEM = 
{
	"WELCOME OPERATE",
	"     MODE      ",
	"  PLEASE ENTER ",
	"     CARD      ",
	"  ENTER THE    ",
	"TRANSAC AMOUNT ",
	"TRANSACTION  : ",
	"     Wrong     ",
	"  Transaction  ",	
	"  ERROR_Temp   ",
	"  CALL_XXXXXX  ",	
	"	Dragons     ",
	"  ATM System   ",
	"enter Program  ",
	"     Mode      ",
	"Program ModE   ",
	"    CARD       ",
	"   NOT READY   ",
	"   THANK       ",
	"    YOU        ",
	"   Success     "
};
 


uint8_t * Print_F(uint8_t const * const Str_F)
{
	if (Str_F == NULL)
	{
		return NULL ;
	}
	static uint8_t Buffer_Ram[20] ;
	strcpy_P((char *)Buffer_Ram , (char*)Str_F);
	return Buffer_Ram ; 
}


uint8_t ATM_Terminal_GetString(uint8_t * RxBuffer , uint8_t BufferSize )
{
	if((RxBuffer == NULL)||(BufferSize == 0))	return -1 ;
	memset(RxBuffer , 0 , BufferSize);
	HAL_UART_RECEIVE(&UART_Handler , RxBuffer , BufferSize);
 
	
	return 0 ;
}




uint8_t ATM_Get_UserCommand(void)
{
	uint8_t command = 0; 	
	printf_P(PSTR("*******************************************************************************************\n"	));
	printf_P(PSTR("*********************** Please Choose one of the following Commands ***********************\n" ));
	printf_P(PSTR("*******************************************************************************************\n" ));
	printf_P(PSTR("************************ 1- Add Card	 *****************************************************\n" ));
	printf_P(PSTR("************************ 2- Remove Card   *************************************************\n" ));
	printf_P(PSTR("************************ 3- Search For Card With PAN **************************************\n" ));
	printf_P(PSTR("************************ 4- Search With Card Holder Name **********************************\n" ));
	printf_P(PSTR("************************ 5- Total NUM of Current CARDs ************************************\n" ));
	printf_P(PSTR("************************ 6- Reset Data Base ***********************************************\n" ));
	printf_P(PSTR("************************ 7- Admin Modify Data *********************************************\n" ));
	printf_P(PSTR("************************ 8- Exit Programming mode *****************************************\n" ));
	printf_P(PSTR("*******************************************************************************************\n" ));
	printf_P(PSTR("************************************** END OF SELECTION !!!********************************\n" ));
	printf_P(PSTR("*******************************************************************************************\n"	));
	printf_P(PSTR(" \n" ));	

	HAL_UART_RECEIVE(&UART_Handler , &command , 0x01) ;
	printf_P(PSTR("\n")) ;
	return command ; 
	
	

}

void ATM_Add_CardData(void)
{
		uint8_t  flag = 0 ;
		CardData_t TempCard = {0};		
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR("******* Please enter Card Holder Name ***********\n" ));
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR(" \n" ));					
		ATM_Terminal_GetString(TempCard.CardName , CARD_NAME_LEN +1);
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR("*********** Please enter Card PAN  : ************\n" ));
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR(" \n" ));
		ATM_Terminal_GetString(TempCard.CardPAN , CARD_PAN_LEN+1);
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR("************ Please enter Card PIN : ************\n" ));
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR(" \n" ));
		ATM_Terminal_GetString(TempCard.CardPIN , CARD_PIN_LEN+1);
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR("******* Please enter Card Total Balance**********\n" ));
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR("\n" ));
		ATM_Terminal_GetString(TempCard.CardBalance , CARD_BALANCE_LEN+1);	
		/********************************************************
		*					Add Card Data	to SERVER			*
		********************************************************/						
		flag = SERVER_OPER_Add_CARD(&TempCard);
				
		if (flag == SERVER_OPER_OK ) // if SERVER returned with Success operation 
		{
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR("****** Great a new Card added successfully ******\n" ));
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR(" \n" ));			
		}
		else if (flag == SERVER_OPER_FullSpace)
		{
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR("******** There is no enough space !!! ***********\n" ));
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR(" \n" ));
		}else{
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR("********* this card already exist !!! ***********\n" ));
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR(" \n" ));
		}
				
}

void ATM_Remove_Card(void)
{
		CardData_t TempCard = {0};	
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR("********* Please enter Card PAN  : **************\n" ));
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR(" \n" ));
		ATM_Terminal_GetString(TempCard.CardPAN , CARD_PAN_LEN+1);
				
		/********************************************************
		*				Search Card Data From DataBase			*
		********************************************************/ 
		if (SERVER_OPER_Remove_CARD(&TempCard)  == SERVER_OPER_OK ) // if Card data is exist 
		{
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR("******* Wait Until remove this Card Data : ******\n" ));
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR(" \n" ));				
		}else  // if  Card data dose not exist 
		{	
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR("************ Not exist Card Data : **************\n" ));
				printf_P(PSTR("*************************************************\n"	));
				printf_P(PSTR(" \n" ));
		}

}


SERVER_OPER_Status_t ATM_Search_Card_WithPAN(void)
{
	CardData_t TempCard = {0};
		printf_P(PSTR("*************************************************\n"	));
		printf_P(PSTR("************* Please enter Card PAN *************\n" ));
		printf_P(PSTR("*************************************************\n"	));
		printf_P(PSTR(" \n" ));
		ATM_Terminal_GetString(TempCard.CardPAN , CARD_PAN_LEN+1);
	// access SERVER here and return result
	if (SERVER_OPER_Search_CARD(&TempCard , ATM_SEARCH_BY_PAN)  != -1 ) // if data exist
	{
		printf_P(PSTR("**********************************************\n"	));	
		printf_P(PSTR("************ This card Is Exist **************\n" ));
		printf_P(PSTR("**********************************************\n"	));
		printf_P(PSTR(" \n" ));	
		return  SERVER_OPER_Exist ;
	}else  // if data dose not exist
	{
		printf_P(PSTR("************************************************\n"	));
		printf_P(PSTR("************* Not exist Card Data  *************\n" ));
		printf_P(PSTR("************************************************\n"	));
		printf_P(PSTR(" \n" ));
		return  SERVER_OPER_Not_Exist ;
	}
}

void ATM_Search_Card_ByName(void)
{
	CardData_t TempCard = {0};	
		printf_P(PSTR("************************************************\n"	));
		printf_P(PSTR("************* Please enter Card Name: **********\n" ));
		printf_P(PSTR("************************************************\n"	));
		printf_P(PSTR(" \n" ));
	ATM_Terminal_GetString(TempCard.CardName , CARD_NAME_LEN );
	// access SERVER here and return result
	if (SERVER_OPER_Search_CARD(&TempCard , ATM_SEARCH_BY_NAME)  != -1 ) // if card data is exist
	{
		printf_P(PSTR("************************************************\n"	));
		printf_P(PSTR("************* This card  Is Exist **************\n" ));
		printf_P(PSTR("************************************************\n"	));
		printf_P(PSTR(" \n" ));
	}else  // if data dose is not exist
	{
		printf_P(PSTR("************************************************\n"	));
		printf_P(PSTR("************* This card Is not Exist ***********\n" ));
		printf_P(PSTR("************************************************\n"	));
		printf_P(PSTR(" \n" ));
	}
}



void ATM_Admin_Modifying_Data(void)
{
	uint8_t ExitFlag = 0 , command =0  ;
	CardData_t TempCard = {0};
	uint8_t MaxDailyWithDraw[MaxDailyWithDraw_Size]  ;
	while(!ExitFlag)
	{

		printf_P(PSTR("*******************************************************************************************\n"));
		printf_P(PSTR("*********************** Please Choose one of the following Commands ***********************\n" ));
		printf_P(PSTR("*******************************************************************************************\n" ));
		printf_P(PSTR("************************ 1- Set Admin Password and Name ***********************************\n" ));
		printf_P(PSTR("************************ 2- Set Admin Maximum Temperature *********************************\n" ));
		printf_P(PSTR("************************ 3- Clear Error Flag **********************************************\n" ));
		printf_P(PSTR("************************ 4- Set Max Daily Amount ******************************************\n" ));
		printf_P(PSTR("************************ 5- Exit **********************************************************\n" ));
		printf_P(PSTR("*******************************************************************************************\n" ));
		printf_P(PSTR("************************************ END OF SELECTION !!!**********************************\n" ));				
		printf_P(PSTR("*******************************************************************************************\n"));
		printf_P(PSTR("\n" ));
		HAL_UART_RECEIVE(&UART_Handler , &command , 0x01) ;
		printf_P(PSTR(" \n" ));
		switch(command)
		{
			case ATM_ADMIN_COMMAN_SET_PASS :
				printf_P(PSTR("************************************************\n"	));
				printf_P(PSTR("******** Please enter a new admin name : *******\n" ));
				printf_P(PSTR("************************************************\n"	));
				printf_P(PSTR(" \n" ));
				ATM_Terminal_GetString(TempCard.CardName , CARD_NAME_LEN );
				printf_P(PSTR(" \n" ));
				printf_P(PSTR("************************************************\n"	));
				printf_P(PSTR("******** Please enter a new admin pass : *******\n" ));
				printf_P(PSTR("************************************************\n"	));
				printf_P(PSTR(" \n" ));
				ATM_Terminal_GetString(TempCard.CardPAN , CARD_NAME_LEN );
			
				printf_P(PSTR(" \n" ));
				printf_P(PSTR("************************************************\n"	));
				printf_P(PSTR("******************  wait !!! *******************\n" ));
				printf_P(PSTR("************************************************\n"	));
				printf_P(PSTR(" \n" ));
				_delay_ms(ATM_DLEAY_IN_S);
				if( SERVER_ADMIN_Set_Pass(TempCard.CardName , TempCard.CardPAN) == SERVER_OPER_OK )
				{
					printf_P(PSTR("************************************************\n"	));
					printf_P(PSTR("******** Admin Data Stored Successfully  *******\n" ));
					printf_P(PSTR("************************************************\n"	));
					printf_P(PSTR(" \n" ));
				}else
				{
					printf_P(PSTR("************************************************\n"	));
					printf_P(PSTR("*************  Please Try Again  ***************\n" ));
					printf_P(PSTR("************************************************\n"	));
					printf_P(PSTR(" \n" ));
				}
			
				break;
			case  ATM_ADMIN_COMMAN_SET_TEMP :

				printf_P(PSTR("************************************************\n"	));
				printf_P(PSTR("****** Enter a new admin MAX Temp value:********\n" ));
				printf_P(PSTR("************************************************\n"	));
				printf_P(PSTR(" \n" ));
				ATM_Terminal_GetString(TempCard.CardName , CARD_NAME_LEN );
				printf_P(PSTR("************************************************\n"	));
				printf_P(PSTR("******************  wait !!! *******************\n" ));
				printf_P(PSTR("************************************************\n"	));
				printf_P(PSTR(" \n" ));
				_delay_ms(ATM_DLEAY_IN_S);
				if( SERVER_ADMIN_Set_Temp(TempCard.CardName) == SERVER_OPER_OK )
				{
					printf_P(PSTR("************************************************\n"	));
					printf_P(PSTR("***** Admin Data Stored Successfully ***********\n" ));
					printf_P(PSTR("************************************************\n"	));
					printf_P(PSTR(" \n" ));
				}else
				{
					printf_P(PSTR("************************************************\n"	));
					printf_P(PSTR("*************  Please Try Again  ***************\n" ));
					printf_P(PSTR("************************************************\n"	));
					printf_P(PSTR(" \n" ));
				}
			
				break;
			case ATM_ADMIN_ERROR_CLEAR :
				if( SERVER_ADMIN_Error( ADMIN_ERROR_CLEAR ) == SERVER_OPER_OK )
				{
					printf_P(PSTR("************************************************\n"	));
					printf_P(PSTR("**********  Error Cleared Successfully *********\n" ));
					printf_P(PSTR("************************************************\n"	));
					printf_P(PSTR(" \n" ));
				}else
				{
					printf_P(PSTR("**********************************************************\n"	));
					printf_P(PSTR("******** Error Does Not Cleared Successfully !!!!  *******\n" ));
					printf_P(PSTR("**********************************************************\n"	));
					printf_P(PSTR(" \n" ));
				}
				break;
			case ATM_ADMIN_MAX_Daliy_Amount :
					printf_P(PSTR("************************************************\n"	));
					printf_P(PSTR("*****  Please Enter the MAx Daily Amount *******\n" ));
					printf_P(PSTR("************************************************\n"	));
					printf_P(PSTR(" \n" ));
					ATM_Terminal_GetString(MaxDailyWithDraw , MaxDailyWithDraw_Size);
					printf_P(PSTR(" \n" ));			 
				if(SERVER_ADMIN_Set_MAximum_DailyAmount(MaxDailyWithDraw) == SERVER_OPER_OK )
				{
					printf_P(PSTR("************************************************\n"	));
					printf_P(PSTR("*****  Maximum Daily Amount Successfully  ******\n" ));
					printf_P(PSTR("************************************************\n"	));
					printf_P(PSTR(" \n" ));
				}else
				{
					printf_P(PSTR(" \n"));
					printf_P(PSTR("*************************************************************************\n"	));
					printf_P(PSTR("********* Maximum Daily Amount Does Not Set Successfully !!!! ***********\n" ));
					printf_P(PSTR("*************************************************************************\n"	));
					printf_P(PSTR(" \n" ));
				}
				break;
			case ATM_ADMIN_Exit :
				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR("*****  EXIT Admin Modifying mode successfully ******\n" ));
				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR(" \n" ));
				ExitFlag = 1 ;
				break;
			default:
			
			
				break;
				}
		}
}





void ATM_Programming_mode(void)
{
 	uint8_t ExitFlag = 0 ;
	uint8_t command = 0; 
	
	
	LCD_Send_String_WithLoc(1,1,Print_F(LCD_StrF[LCD_Print_enter_Programing] ));	
	LCD_Send_String_WithLoc(2,1,Print_F(LCD_StrF[LCD_Print_Mode] ));
	printf_P(PSTR("****************************************************\n"	));
	printf_P(PSTR("*****************  "));
	printf_P((char *)LCD_StrF[LCD_Print_enter_Programing]);
	printf_P(PSTR(" ****************\n" ));
	printf_P(PSTR("**************** "));
	printf_P((char *)LCD_StrF[LCD_Print_Mode]);
	printf_P(PSTR(" ***************\n" ));
	printf_P(PSTR("****************************************************\n"	));
	printf_P(PSTR(" \n" ));
	_delay_ms(ATM_DLEAY_IN_S );
	LCD_Send_Command(LCD_COMMANED_CLEAR_LCD);
	printf_P(PSTR("****************************************************\n"	));
	printf_P(PSTR("*****************  "));
	printf_P((char *)LCD_StrF[LCD_Print_Programing_Mode]);
	printf_P(PSTR(" ****************\n" ));
	printf_P(PSTR("****************************************************\n"	));
	printf_P(PSTR(" \n" ));
	LCD_Send_String_WithLoc(1,1,Print_F(LCD_StrF[LCD_Print_Programing_Mode]));
	_delay_ms(ATM_DLEAY_IN_S);
	
	
	while(!ExitFlag)
	{
		
		command =  ATM_Get_UserCommand();
		switch(command)
		{
			case  ATM_ADD_Card :		// Add card
			
				/********************************************************
				*					Collect Card Data					*
				********************************************************/
			  	ATM_Add_CardData() ;
				break; 	
			case ATM_REMOVE_CARD :		// Remove Card 
				/********************************************************
				*			Remove Card Data From DataBase				*
				********************************************************/
				ATM_Remove_Card();
				break;	
			case  ATM_SEARCH_FOR_CARD_PAN :		// Search For Specific Card
			
					/********************************************************
					*				Search Card Data in DataBase			*
					********************************************************/ 		 
					ATM_Search_Card_WithPAN();
					break;				
					
			case  ATM_SEARCH_FOR_CARD_NAME :
					/********************************************************
					*		Search Card Data With Name In DataBASE			*
					********************************************************/ 		
					ATM_Search_Card_ByName();
					break;					
					
				break;					
				
			case   ATM_TOTAL_NUM_OF_CARDs :	
				/********************************************************
				*			Return Total Num Of Installed Card 			*
				********************************************************/ 
					printf_P(PSTR("****************************************************\n"));
					printf_P(PSTR("***** The Number of Installed Cards is :" ));
					printf("%i" , SERVER_OPER_GetTotal_CARDNum());
					printf_P(PSTR("*********** \n"));
					printf_P(PSTR("****************************************************\n"	));
					printf_P(PSTR(" \n" ));
				break;
			case   ATM_RESET_DATA_BASE :	
				/********************************************************
				*					Reset Database			 			*
				********************************************************/				
				if(SERVER_OPER_DataBase_Reset() == SERVER_OPER_OK)
				{
					printf_P(PSTR("****************************************************\n"));
					printf_P(PSTR("*************  Deleted successfully  ***************\n"));
					printf_P(PSTR("****************************************************\n"));
					printf_P(PSTR(" \n" ));
				}else{
					printf_P(PSTR("******************************************************\n"));
					printf_P(PSTR("***** problem With Data Base Call Service Support ****\n"));
					printf_P(PSTR("******************************************************\n"));
					printf_P(PSTR(" \n" ));
				}
				break;
			case  ATM_ADMIN_MODIFY :
				/********************************************************
				*					Modify Admin Data 					*
				********************************************************/		
				ATM_Admin_Modifying_Data();
				break;
			case    ATM_EXIT_PROGRAMMING_MODE :
				/********************************************************
				*			Switching to Operating Mode					*
				********************************************************/
				printf_P(PSTR("************************************************\n"	));
				printf_P(PSTR("******************  wait !!! *******************\n" ));
				printf_P(PSTR("************************************************\n"	));
				printf_P(PSTR(" \n" ));
				_delay_ms(ATM_DLEAY_IN_S);
				ExitFlag = 1 ;
			break;				
			default:
				/********************************************************
				*			Handling All Wrong Commands					*
				********************************************************/			
				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR("******** Wrong chose Please Try again **************\n" ));
				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR(" \n" ));
				break ;
			
			
		}	
	}
}
 
	uint8_t KeyPad_Key = 0  , CardDataExist = 0 ;
	uint8_t TempBlance[ADMIN_MAX_DAILY_LEN] = "1000";
	uint32_t UserTransAmount = 0 ; 
	uint32_t CardBalance =  2000 ; //atoi((char *)TempCard.CardBalance);
	uint32_t MaxDailyWithDraw = 2000 ;
	CardData_t  CardData , TempCardData  ;
		uint16_t  TempAdd ; 
		uint16_t CardAdd  =0;

		uint8_t ExitFlag =0 ; 
void ATM_Operation_mode(void)
{	
	uint8_t index =0 ;
	uint8_t	CommandFlag  =0 ;	
	LCD_Send_String_WithLoc(1,1,Print_F(LCD_StrF[LCD_Print_WELCOME_OPERATE]));
	LCD_Send_String_WithLoc(2,1,Print_F(LCD_StrF[LCD_Print_MODE]));
	printf_P(PSTR("****************************************************\n"	));
	printf_P(PSTR("*****************  "));
	printf_P((char *)LCD_StrF[LCD_Print_WELCOME_OPERATE]);
	printf_P(PSTR(" ****************\n" ));
	printf_P(PSTR("*****************  "));
	printf_P((char *)LCD_StrF[LCD_Print_MODE]);
	printf_P(PSTR(" ***************\n" ));
	printf_P(PSTR("****************************************************\n"	));
	printf_P(PSTR(" \n" ));
	_delay_ms(ATM_DLEAY_IN_S);


	while(!ExitFlag)
	{
		index = 0 , KeyPad_Key = 0;
		memset(TempBlance , 0 , ADMIN_MAX_DAILY_LEN);

		LCD_Send_Command(LCD_COMMANED_CLEAR_LCD) ;
		LCD_Send_String_WithLoc(1,1,Print_F(LCD_StrF[LCD_Print_PLEASE_ENTER]));
		LCD_Send_String_WithLoc(2,1,Print_F(LCD_StrF[LCD_Print_CARD]));
		printf_P(PSTR("****************************************************\n"	));
		printf_P(PSTR("*****************  "));
		printf_P((char *)LCD_StrF[LCD_Print_PLEASE_ENTER]);
		printf_P(PSTR(" ***************\n" ));
		printf_P(PSTR("*****************  "));
		printf_P((char *)LCD_StrF[LCD_Print_CARD]);
		printf_P(PSTR(" ****************\n" ));
		printf_P(PSTR("****************************************************\n"	));
		printf_P(PSTR(" \n" ));

		while(Button_Read(ATM_Buttons, ATM_Insert_Card_Button_INDEX) == State_HIGH);
		if(Button_Read(ATM_Buttons, ATM_Insert_Card_Button_INDEX) == State_LOW)
		{
			 ATM_Collect_CardData(&CardData);
			CardAdd = SERVER_OPER_Search_CARD(&CardData , ATM_SEARCH_BY_PAN) ;
		
		if ( CardAdd != -1 ) // if data exist
		{
			EEPROM_ReadByteS(CardAdd , (uint8_t *)&TempCardData , ATM_CARD_BLOCK_SIZE);	
			CardBalance = atoi((char *)TempCardData.CardBalance) ;
			printf_P(PSTR("**********************************************\n"	));
			printf_P(PSTR("************ This card Is Exist **************\n" ));
			printf_P(PSTR("**********************************************\n"	));
			printf_P(PSTR(" \n" ));
			CardDataExist = 1 ;
		}else  // if data dose not exist
		{
			printf_P(PSTR("************************************************\n"	));
			printf_P(PSTR("************* Not exist Card Data  *************\n" ));
			printf_P(PSTR("************************************************\n"	));
			printf_P(PSTR(" \n" ));
			CardDataExist = 0 ; 
		}			
		
			
		
			if (CardDataExist == 1)
			{
				LCD_Send_Command( LCD_COMMANED_CLEAR_LCD );
				LCD_Send_String_WithLoc(1,1,Print_F(LCD_StrF[LCD_Print_ENTER_THE]));
				LCD_Send_String_WithLoc(2,1,Print_F(LCD_StrF[LCD_Print_TRANSAC_AMOUNT]));
				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR("*****************  "));
				printf_P((char *)LCD_StrF[LCD_Print_ENTER_THE]);
				printf_P(PSTR(" ****************\n" ));
				printf_P(PSTR("*****************  "));
				printf_P((char *)LCD_StrF[LCD_Print_TRANSAC_AMOUNT]);
				printf_P(PSTR(" **************** \n" ));
				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR(" \n" ));
				_delay_ms(ATM_DLEAY_IN_S);
				LCD_Send_Command( LCD_COMMANED_CLEAR_LCD );
				LCD_Send_String_WithLoc(1,1,(uint8_t *) Print_F(LCD_StrF[LCD_Print_TRANSACTION]));
				LCD_Goto_Location(2,1);
				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR("*****************  "));
				printf_P((char *)LCD_StrF[LCD_Print_TRANSACTION]);
				printf_P(PSTR(" ****************\n" ));
				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR(" \n" ));			
			


				while(1)
				{
					while(KeyPad_Key == 0)
					{
						_delay_ms(200);
						KeyPad_Key = KeyPad_GetPressedKey(&KeyPad);
						if((KeyPad_Key == '*'))	KeyPad_Key= 0 ; 
					
					}
					if (KeyPad_Key == '#')
					{
						break; 
					}else
					{
					
						LCD_Send_Character_CurrLoc('*');
						TempBlance[index++] = KeyPad_Key ;
						KeyPad_Key = 0 ;
					}
				
				
				}
			
			
				// Get Card PAN and Balance from  CARD 
				UserTransAmount = atoi( (char *)TempBlance ) ;
				LCD_Send_Command(LCD_COMMANED_CLEAR_LCD);
				LCD_Send_Integer_CurrLoc(UserTransAmount , 7);
				_delay_ms(ATM_DLEAY_IN_S);
				if((UserTransAmount > MaxDailyWithDraw) || (UserTransAmount > CardBalance))
				{
					LCD_Send_Command(LCD_COMMANED_CLEAR_LCD);
					printf_P(PSTR("****************************************************\n"	));
					printf_P(PSTR("*****************  "));
					printf_P((char *)LCD_StrF[LCD_Print_Wrong]);
					printf_P(PSTR(" ***************\n" ));
					printf_P(PSTR("*****************  "));
					printf_P((char *)LCD_StrF[LCD_Print_Transaction]);
					printf_P(PSTR(" *************** \n" ));
					printf_P(PSTR("****************************************************\n"	));
					printf_P(PSTR(" \n" ));
					LCD_Send_String_WithLoc(1,1,Print_F(LCD_StrF[LCD_Print_Wrong]));
					LCD_Send_String_WithLoc(2,1,Print_F(LCD_StrF[LCD_Print_Transaction]));
					_delay_ms(ATM_DLEAY_IN_S); 
				}else{
					// right transaction
					CardBalance -= UserTransAmount ; 
					itoa(CardBalance , (char *)TempCardData.CardBalance , 10 ) ;
					LCD_Send_Command(LCD_COMMANED_CLEAR_LCD);
					LCD_Send_Integer_CurrLoc(CardBalance , 7);
					printf("Current  balance is : %i \n" , CardBalance);
					EEPROM_WriteByteS(CardAdd , (uint8_t *)&TempCardData , ATM_CARD_BLOCK_SIZE);
					LCD_Send_String_WithLoc(1,1,Print_F(LCD_StrF[LCD_Print_Success]));
					LCD_Send_String_WithLoc(2,1,Print_F(LCD_StrF[LCD_Print_Transaction]));
					Motor_Dir( DIR_LEFT , 70);
					_delay_ms(1000);
					Motor_Dir( DIR_LEFT , 0);
		
				}
			
			}
		}else
		{
			;
		}
		printf_P(PSTR("*******************************************************************************************\n"));
		printf_P(PSTR("*********************** Please Choose one of the following Commands ***********************\n" ));
		printf_P(PSTR("*******************************************************************************************\n" ));
		printf_P(PSTR("************************ 1- Try another Transaction  **************************************\n" ));
		printf_P(PSTR("************************ 2- Exit **********************************************************\n" ));
		printf_P(PSTR("*******************************************************************************************\n" ));
		printf_P(PSTR("************************************ END OF SELECTION !!!**********************************\n" ));
		printf_P(PSTR("*******************************************************************************************\n"));

		printf_P(PSTR("\n" ));
		LCD_Send_Command(LCD_COMMANED_CLEAR_LCD);
		LCD_Send_String_WithLoc(1,1,(uint8_t *)"Select Command");
		LCD_Send_String_WithLoc(2,1,(uint8_t *)"1.Try   2.Exit");
 
		CommandFlag  = 1;
		while(CommandFlag)
		{
			
			KeyPad_Key = 0 ;
			while(KeyPad_Key == 0)
			{
				_delay_ms(200);
				KeyPad_Key = KeyPad_GetPressedKey(&KeyPad);
				if((KeyPad_Key == '*'))	KeyPad_Key= 0 ;
			
			}
			LCD_Send_Command(LCD_COMMANED_CLEAR_LCD);
			LCD_Send_String_WithLoc(1,1,(uint8_t *)"You Pressed");
			LCD_Send_Character_WithLoc(2,6,KeyPad_Key);
			switch(KeyPad_Key)
			{
				case '1' :
							ExitFlag = 0 ; 
							CommandFlag = 0 ;
					break; 
					
				case '2' : 
							ExitFlag = 1 ;	
							CommandFlag = 0 ;	
					break;
			
				default: 
					printf_P(PSTR("*******************************************************************************************\n" ));
					printf_P(PSTR("************************************ Wrong Command    !!!**********************************\n" ));
					printf_P(PSTR("*******************************************************************************************\n"));	
					CommandFlag = 1 ;	
				break;
			
			
				}
		}
	
	}
		_delay_ms(2000);
		printf_P(PSTR("****************************************************\n"	));
		printf_P(PSTR("************************ Thank You *****************\n" ));
		printf_P(PSTR("****************************************************\n"	));
		printf_P(PSTR(" \n" ));
		LCD_Send_Command( LCD_COMMANED_CLEAR_LCD );
		LCD_Send_String_WithLoc(1,1,Print_F(LCD_StrF[LCD_Print_ENTER_THANK]));
		LCD_Send_String_WithLoc(2,1,Print_F(LCD_StrF[LCD_Print_YOU]));
		while(1);
}


void ATM_Collect_CardData(CardData_t * CardData)
{
	uint8_t Flag = 0 ; 
	if (CardData == NULL)
	{
		return ;
	}
	while(!Flag)
	{
		
		HAL_GPIO_WRITEPIN(GPIOD , GPIO_PIN_3, GPIO_PIN_SET);
		HAL_SPI_Recieve(&SPI_Handler ,(uint8_t*) CardData , 29) ;
		if(strcmp((char * )CardData , "NOT READY" ) == 0 )
		{
			printf_P(PSTR("************************************************\n"	));
			printf_P(PSTR("******************    CARD    ******************\n" ));
			printf_P(PSTR("******************  NOT READY ******************\n" ));
			printf_P(PSTR("************************************************\n"	));
			printf_P(PSTR(" \n" ));
			LCD_Send_Command(LCD_COMMANED_CLEAR_LCD);
			printf_P(PSTR("****************************************************\n"	));
			printf_P(PSTR("*****************  "));
			printf_P((char *)LCD_StrF[LCD_Print_CARD]);
			printf_P(PSTR(" ***************\n" ));
			printf_P(PSTR("*****************  "));
			printf_P((char *)LCD_StrF[LCD_Print_NOT_READY]);
			printf_P(PSTR(" *************** \n" ));
			printf_P(PSTR("****************************************************\n"	));		
		}
		else
		{
			Flag = 1;
		}
		HAL_GPIO_WRITEPIN(GPIOD , GPIO_PIN_3, GPIO_PIN_RESET);
		_delay_ms(2000);
	}
	
}


void ATM_Lock_Fun(void)
{
	  
	LCD_Send_String_WithLoc(1,1,Print_F(LCD_StrF[LCD_Print_ERROR_Temp]));
	LCD_Send_String_WithLoc(2,1,Print_F(LCD_StrF[LCD_Print_CALL_XXXXXX]));
	printf_P(PSTR("****************************************************\n"	));
	printf_P(PSTR("***************     LOCKED       *******************\n" ));
	printf_P(PSTR("*************** Please Call XXXX *******************\n" ));
	printf_P(PSTR("****************************************************\n"	));
	printf_P(PSTR(" \n" ));
	while(1);
}