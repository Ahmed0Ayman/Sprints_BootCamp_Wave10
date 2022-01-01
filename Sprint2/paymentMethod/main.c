
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "Terminal.h"
#include "Server.h"
#include "Utilites.h"



#define   MAIN_FUN_ERROR   -1 

FILE *f ;

str_terminalData_t  str_TerminalData;

int main()
{



    Socket_Init( );

    str_cardData_t  str_CardData ;

    if(Terminal_Processing(&str_CardData , &str_TerminalData) != TERMINAL_OK)
    {
        #if( __DEBUG__ == 1)
            printf("error in  Terminal_Processing() Function \n");
        #endif
        return MAIN_FUN_ERROR ;


    }
    else{
        // now turn of server side 
    
        if(SERVER_CheckCardData(&str_CardData ,&str_TerminalData) == SERVER_OK)
        {
            printf(" success operation   \n");
            SocketSend(" success operation    \n" ,ClientHSocket_Id);
        }
        else
        {
            #if( __DEBUG__ == 1)
                printf("error in  SERVER_CheckCardData() Function \n");
            #endif
            SocketSend("Not success operation  \n" ,ClientHSocket_Id);
            printf("Not Success Operation \n");
            return MAIN_FUN_ERROR ;   
        }


    }

    


    return 0;

}
