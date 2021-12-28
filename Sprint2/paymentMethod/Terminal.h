
#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#define __DEBUG__ 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "Terminal.h"


#define CARD_NAME_HOLDER_LEN             30u
#define CARD_NUM_LEN                     20u
#define CARD_EXPIR_DATE_LEN              8u
#define CARD_CVV_LEN                     5u

#define MAX_WITHDRAW_DAILY               8000.0

typedef enum  { TERMINAL_OK , TERMINAL_CARD_ERROR , TERMINAL_HEAP_ERROR  , TERMINAL_PARAM_ERROR }TernimalStatus_t;
typedef enum  { JANUARY=1  , FEBRUARY , MARCH , APRIL , MAY , JUNE , JULY , AUGUST , SEPTEMPER , OCTOBER , NOVEMBER , DECEMBER }MonthOfYear_t;
typedef enum EN_transStat_t
{
    DECLINED,
    APPROVED
    
}EN_transStat_t;

struct ST_cardData_t
{
    uint8_t * pu8_cardHolderName;
    uint8_t * pu8_primaryAccountNumber;
    uint8_t * pu8_cardExpirationDate;
    uint8_t * pu8_CardCVV  ;
    
}ST_cardData;

struct ST_terminalData_t
{
     int transAmount;
     int maxTransAmount;
    uint8_t transactionDate[20];
    
}ST_terminalData;

struct ST_transaction_t
{
    struct ST_cardData_t cardHolderData;
    struct ST_terminalData_t transData;
    EN_transStat_t transStat;
    
}ST_transaction;


TernimalStatus_t Terminal_CollectCardData(struct ST_cardData_t * pstr_CardData);

TernimalStatus_t Terminal_CheckCardDate(struct ST_cardData_t * pstr_CardData);


MonthOfYear_t Terminal_SearchForMonth(uint8_t * Str);


TernimalStatus_t Terminal_GetNumsINString(uint8_t ** pu8_Str1 );


//TernimalStatus_t CheckCardDate(struct ST_cardData_t * pstr_CardData);



#endif