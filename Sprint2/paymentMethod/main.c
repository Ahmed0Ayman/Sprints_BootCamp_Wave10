


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "Terminal.h"
#include "Server.h"

#define   MAIN_ERROR   -1 

CardServerData_t cardDateBaseData ; 
FILE *f ;

time_t Str_Time ;

int main()
{

  
    if(Terminal_CollectCardData(&ST_cardData) != TERMINAL_OK)
    {
        return MAIN_ERROR ; 
    }
    ST_terminalData.maxTransAmount = MAX_WITHDRAW_DAILY ;
    time(&Str_Time);
    strcpy(ST_terminalData.transactionDate , ctime(&Str_Time));
    #if (__DEBUG__ == 1)   
        printf("%s\n",ST_terminalData.transactionDate);
    #endif
    do{
    printf("Please enter Transaction amount \n");  
    scanf("%d",&ST_terminalData.transAmount );
    }while((ST_terminalData.transAmount <= 0 )||(ST_terminalData.transAmount > MAX_WITHDRAW_DAILY));

    if(Terminal_CheckCardDate(&ST_cardData) != TERMINAL_OK)
    {
        return MAIN_ERROR ;
    }
    else{
        // now turn of server side 

        if(GetCardData(&ST_cardData ,&ST_terminalData , &cardDateBaseData) == SERVER_OK)
        {
            printf(" Successed operation   \n");
            SERVER_StoreTransactionDate(&ST_cardData ,&ST_terminalData );
        }
        else
        {
            return MAIN_ERROR ;   
        }


    }

    




    return 0;

}
