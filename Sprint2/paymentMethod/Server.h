
#ifndef __SERVER_H__
#define __SERVER_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "Terminal.h"



typedef enum  { SERVER_OK , SERVER_CARD_ERROR , SERVER_HEAP_ERROR  , SERVER_PARAM_ERROR ,SERVER_FILE_ERROR} ServerStatus_t;

typedef struct
{
    uint8_t * CardNumber ;
    uint8_t * cardCVV    ;
    uint8_t * CardMaxWithDraw;

}CardServerData_t;







ServerStatus_t GetCardData(struct ST_cardData_t * pstr_CardData  ,struct ST_terminalData_t * TerminalData, CardServerData_t * CardServerData);





ServerStatus_t UpdataAccount(struct ST_cardData_t * pstr_CardData ,struct ST_terminalData_t * TerminalData, CardServerData_t * CardServerData);




ServerStatus_t SERVER_StoreTransactionDate(struct ST_cardData_t * pstr_CardData ,struct ST_terminalData_t * TerminalData);







#endif