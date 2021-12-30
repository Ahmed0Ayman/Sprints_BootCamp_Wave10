
#ifndef __SERVER_H__
#define __SERVER_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "Terminal.h"
#include "Utilites.h"


typedef enum  {
                SERVER_OK , SERVER_CARD_ERROR , SERVER_HEAP_ERROR  , SERVER_PARAM_ERROR ,SERVER_FILE_ERROR
                } ServerStatus_t;   /* enum that return status of any function is server file */





/* brief            : this fuction used to check if the given card name is located in server data base 
 * param [input]    : pstr_CardData pointer to struct that hold all client data 
 * param [input]    : pointer to string that hold the read server name 
 * Return ServerStatus_t : enum if located will return SERVER_OK *
 */
ServerStatus_t Server_CheckCardName(str_cardData_t * pstr_CardData , uint8_t * pCardData);








/* brief            : this fuction used to check card data (name , account numder , CVV )
 * param [input]    : pstr_CardData pointer to struct that hold all client data 
 * param [input]    : TerminalData pointer to terminal struct that hold all required data to terminal 
 * param [input]    : pointer to string that hold the read server name 
 * Return ServerStatus_t : enum if located will return SERVER_OK *
 */

ServerStatus_t SERVER_CheckCardData(str_cardData_t * pstr_CardData ,str_terminalData_t * TerminalData);







/* brief            : this fuction used to save the accepted transaction data
 * param [input]    : pstr_CardData pointer to struct that hold all client data 
 * param [input]    : TerminalData pointer to terminal struct that hold all required data to terminal 
 * param [input]    :TransactionStatus  pointer to string that hold the transaction status  
 * Return ServerStatus_t : enum if located will return SERVER_OK *
 */
ServerStatus_t SERVER_StoreTransactionDate(str_cardData_t * pstr_CardData ,str_terminalData_t * TerminalData ,uint8_t * TransactionStatus );









#endif