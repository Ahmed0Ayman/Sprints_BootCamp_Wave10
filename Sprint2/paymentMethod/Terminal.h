#ifndef __TERMINAL_H__
#define __TERMINAL_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "ServerConfig.h"
#include "Utilites.h"




#define CARD_NAME_HOLDER_LEN                60u
#define CARD_NUM_LEN                        20u
#define CARD_EXPIR_DATE_LEN                 8u
#define CARD_CVV_LEN                        5u

#define CAP_TO_SMALL_OFFSET                 0x20u 

#define MAX_WITHDRAW_DAILY               8000.0






typedef enum  { TERMINAL_OK , TERMINAL_CARD_ERROR , TERMINAL_HEAP_ERROR  , TERMINAL_PARAM_ERROR }TernimalStatus_t;
typedef enum  { JANUARY=1  , FEBRUARY , MARCH , APRIL , MAY , JUNE , JULY , AUGUST , SEPTEMPER , OCTOBER , NOVEMBER , DECEMBER }MonthOfYear_t;


typedef struct _strcardData
{
    uint8_t * pu8_cardHolderName;
    uint8_t * pu8_primaryAccountNumber;
    uint8_t * pu8_cardExpirationDate;
    uint8_t * pu8_CardCVV  ;
    
}str_cardData_t;



typedef struct _strterminalData
{
     int transAmount;
     int maxTransAmount;
    uint8_t transactionDate[20];
    
}str_terminalData_t;










/*
 * brief            : this fuction used to filter the input from client from any string 
 * param [input/output]    : pu8_Str1 pointer to pointer to string 
 * Return TernimalStatus_t : return the status of this function only TERMINAL_OK indicate true 
 */
TernimalStatus_t Terminal_GetNumsINString(uint8_t ** pu8_Str1 );




/* 
 * brief            : this fuction used to search for a giving string (month) and return month in number  
 * param [input/output]    : Str pointer to  string that will be checked 
 * Return MonthOfYear_t : return the number of month of course return zero means error 
 */
MonthOfYear_t Terminal_SearchForMonth(uint8_t * Str);




/* 
 * brief            : this fuction used to format the entered name from client to server stile   
 * param [input]    : EnteredName pointer to  string that hold entered name  
 * param [input]    : pstr_CardData pointer to the entered card data from the user 
 * Return TernimalStatus_t : return the TERMINAL_OK if every thing is ok 
 */
TernimalStatus_t Terminal_SetNameForServer(uint8_t * EnteredName ,  str_cardData_t * pstr_CardData);




/*
 * brief            : this fuction used to format the entered name from client to server stile   
 * param [input]    : EnteredName pointer to  string that hold entered name  
 * param [input]    : pstr_CardData pointer to the entered card data from the user 
 * Return TernimalStatus_t : return the TERMINAL_OK if every thing is ok 
 */
TernimalStatus_t Terminal_CollectCardData(str_cardData_t * pstr_CardData);



/* 
 * brief            : this fuction used to get the transaction amount from the user   
 * param [input]    : ST_terminalData pointer struct the hold all transaction information   
 * Return TernimalStatus_t : return the TERMINAL_OK if every thing is ok 
 */
TernimalStatus_t Terminal_GetTransactionAmount(str_terminalData_t *ST_terminalData);





/* 
 * brief            : this fuction used to check the expired data of client card    
 * param [input]    : pstr_CardData pointer struct the hold all card information   
 * Return TernimalStatus_t : return the TERMINAL_OK if every thing is ok 
 */
TernimalStatus_t Terminal_CheckCardDate(str_cardData_t * pstr_CardData);




/* 
 * brief            : this fuction used to check the expired data of client card    
 * param [input]    : pstr_CardData pointer struct the hold all card information
 * param [input]    : pstr_CardData pointer struct the hold all transaction information     
 * Return TernimalStatus_t : return the TERMINAL_OK if every thing is ok 
 */
TernimalStatus_t Terminal_Processing(str_cardData_t * pstr_CardData ,str_terminalData_t * TerminalData);
#endif