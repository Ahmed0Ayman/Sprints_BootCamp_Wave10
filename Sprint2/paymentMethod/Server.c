#include "Server.h"





void Delay(uint32_t NumOfSecond)
{
        int MilSecond  = 1000 * NumOfSecond ;

        clock_t StartTime = clock() ;
        while (clock() < StartTime+MilSecond)
        {
            ;
        }

}

ServerStatus_t GetCardData(struct ST_cardData_t * pstr_CardData ,struct ST_terminalData_t * TerminalData, CardServerData_t * CardServerData)
{
    FILE * DateBaseFile ;
    uint8_t  Founded =0  ;
    uint8_t  CardNumber[20] = {0}, CardCVV[20] = {0} , CardAmount[10] = {0} ;
    int   intCardAmmount = 0  ;
    char  NewCardAmount [5] = {0} ;


    if(pstr_CardData->pu8_primaryAccountNumber == NULL)
    {
        return SERVER_PARAM_ERROR ;
    }      
    DateBaseFile = fopen("DataBase.txt" , "r+") ;
    if(DateBaseFile == NULL)
    {
        return SERVER_FILE_ERROR ;
    }


    while(fscanf(DateBaseFile , "%s %s" ,CardNumber , CardCVV ) > 1)
    {
        if(strcmp(pstr_CardData->pu8_primaryAccountNumber  , CardNumber) == 0 )
        {
            if(strcmp(pstr_CardData->pu8_CardCVV , CardCVV) == 0 )
            {   
                Founded = 1 ;
                break ;
            }else
            {
                system("cls");
                printf("\nWrong CVV Try again \n");
            }
        }
            fscanf(DateBaseFile , "%s " , CardAmount );
    }
    if(Founded == 1)
    {
        #if (__DEBUG__ == 0)
        printf("waiting *");
        for(uint32_t counter =0 ; counter< 10 ; counter++)
        {
            printf("*");Delay(2);
        }
        #endif
        printf("\n");
        fscanf(DateBaseFile , "%s " , CardAmount );
        intCardAmmount = atoi(CardAmount) ;
        intCardAmmount -=  TerminalData->transAmount ;
        itoa(intCardAmmount , NewCardAmount, 10);      
        fseek(DateBaseFile , ftell(DateBaseFile)  - 6  , SEEK_SET) ;
        fprintf(DateBaseFile , " %d" ,intCardAmmount ); 
        printf("your current Amount is : %d \n",intCardAmmount);
        return SERVER_OK ;
    }


    fclose(DateBaseFile) ;
    return SERVER_CARD_ERROR ;


}

ServerStatus_t SERVER_StoreTransactionDate(struct ST_cardData_t * pstr_CardData ,struct ST_terminalData_t * TerminalData)
{
        FILE * DataBaseFile  = NULL;
        DataBaseFile = fopen(pstr_CardData->pu8_primaryAccountNumber , "a+");
        if(DataBaseFile == NULL)
        {
            return SERVER_FILE_ERROR ;
        }
        else
        {
           fprintf(DataBaseFile , "%s \n"  ,TerminalData->transactionDate);  
        }


    
    return SERVER_OK ; 
}