/*
 * SERVER_oper.h
 *
 * Created: 1/25/2022 9:47:02 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef SERVER_OPER_H_
#define SERVER_OPER_H_

#include "EEPROM.h"
#include "APP_Library.h"
#include <avr/pgmspace.h>
#include "APP.h"

SERVER_OPER_Status_t SERVER_OPER_Add_CARD(CardData_t * CardData);





SERVER_OPER_Status_t SERVER_OPER_DataBase_Reset(void);






SERVER_OPER_Status_t SERVER_OPER_Remove_CARD(CardData_t * CardData);







uint16_t SERVER_OPER_Search_CARD(CardData_t * CardData , uint8_t SearchBase );







uint16_t SERVER_OPER_GetTotal_CARDNum(void);







SERVER_OPER_Status_t SERVER_ADMIN_Set_Pass(uint8_t * StrName , uint8_t * Password);







SERVER_OPER_Status_t SERVER_ADMIN_Set_Temp(uint8_t * MaxTemp);




SERVER_OPER_Status_t SERVER_ADMIN_Get_Pass(uint8_t * StrName , uint8_t * Password);



SERVER_OPER_Status_t SERVER_ADMIN_Error(Admin_ErrorAction_t Action );



SERVER_OPER_Status_t SERVER_ADMIN_Get_Temp(uint8_t * MaxTemp);



uint8_t SERVER_ADMIN_Error_Get(void);




SERVER_OPER_Status_t SERVER_ADMIN_Set_MAximum_DailyAmount(uint8_t * MaxDailyAmount);


#endif /* SERVER_OPER_H_ */