#include "Server.h"




/* brief            : this fuction used to check if the given card name is located in server data base 
 * param [input]    : pstr_CardData pointer to struct that hold all client data 
 * param [input]    : pointer to string that hold the read server name 
 * Return ServerStatus_t : enum if located will return SERVER_OK *
 */
ServerStatus_t Server_CheckCardName(str_cardData_t * pstr_CardData , uint8_t * pCardData)
{
    FILE * DateBaseFile = NULL; /* file pointer handler */
    uint32_t Index =0 ; /*used as index to char inside string */
    uint8_t Flag  = 0 ; /* flag hold the current status of comparsion */

            while(pCardData[Index] != '\0')
            {

                if(pCardData[Index] == pstr_CardData->pu8_cardHolderName[Index] )
                {

                    Flag = true ; 
                }
                else
                {
                    Flag = false ;
                    break ; /* break if there is any char that not found in server names */ 
                }
                Index++;
            }
 
    if(Flag == true)
    {
        return SERVER_OK ;
    } 
    else
    {
        return SERVER_CARD_ERROR ;
    }


}





/* brief            : this fuction used to check card data (name , account numder , CVV )
 * param [input]    : pstr_CardData pointer to struct that hold all client data 
 * param [input]    : TerminalData pointer to terminal struct that hold all required data to terminal 
 * param [input]    : pointer to string that hold the read server name 
 * Return ServerStatus_t : enum if located will return SERVER_OK *
 */

ServerStatus_t SERVER_CheckCardData(str_cardData_t * pstr_CardData ,str_terminalData_t * TerminalData)
{
    FILE * DateBaseFile ;
    uint8_t  Found =0  ;
    uint8_t  CardNumber[20] = {0}, CardCVV[20] = {0} , CardAmount[10] = {0} ;
    int   intCardAmmount = 0  ;
    uint8_t  NewCardAmount [5] = {0} , ClientMessage[20] = {0} ;
    uint8_t CardName[CARD_NAME_HOLDER_LEN+1] = {0};
    uint8_t * TransactionStatus[2] = {" not accepted Transaction " , "Accepted Transaction "  };

    if(pstr_CardData->pu8_primaryAccountNumber == NULL)
    {
        return SERVER_PARAM_ERROR ;
    }      

    DateBaseFile = fopen("DataBase.txt" , "r+") ;
    if(DateBaseFile == NULL)
    {
        #if( __DEBUG__ ==   1)
            printf("Error in File Opining \n");
        #endif 

        return SERVER_FILE_ERROR ;
    }


    while(fscanf(DateBaseFile , "%s %s %s" , CardName ,CardNumber , CardCVV ) > 1)  /* read the first three column */
    {
        if(Server_CheckCardName(pstr_CardData,CardName) != SERVER_OK)       /* check if the input card name */
        {
            printf("this Name is not found in data base , please try again \n");
        }
        else
        {
            if(strcmp(pstr_CardData->pu8_primaryAccountNumber  , CardNumber) == 0 )  /* check if the input card number  */
            {
                if(strcmp(pstr_CardData->pu8_CardCVV , CardCVV) == 0 )       /* check if the input card CVV number */
                {   
                    Found = 1 ;     /*now we found the card numder in data base so set Found flag then break */
                    break ;
                }else
                {
                    #if( __DEBUG__ == 0)
                    system("cls");
                    #endif 

                    sprintf(ClientMessage , "\nWrong CVV Try again \n");
                    SocketSend(ClientMessage, ClientHSocket_Id);
                    break ;
                }
            }
                fscanf(DateBaseFile , "%s " , CardAmount );
        }
    }
    if(Found == 1)
    {
        #if (__DEBUG__ == 0)
        sprintf(ClientMessage , "waiting *");       /* send waiting message to client */
        SocketSend(ClientMessage, ClientHSocket_Id);
        for(uint32_t counter =10 ; counter > 0 ; counter--)
        {
            sprintf(ClientMessage , "*");Delay(1);
            SocketSend(ClientMessage, ClientHSocket_Id);
        }
        #endif
        printf("\n");
        fscanf(DateBaseFile , "%s " , CardAmount );
        intCardAmmount = atoi(CardAmount) ;
        intCardAmmount -=  TerminalData->transAmount ;
        itoa(intCardAmmount , NewCardAmount, 10);      
        fseek(DateBaseFile , ftell(DateBaseFile)  - 6  , SEEK_SET) ;
        fprintf(DateBaseFile , " %d" ,intCardAmmount );
        sprintf(CardAmount , "\nyour current Amount is : %d \n",intCardAmmount);
        SocketSend(CardAmount, ClientHSocket_Id);   /* send current amount to client */
        fclose(DateBaseFile) ;
        SERVER_StoreTransactionDate(pstr_CardData ,TerminalData ,TransactionStatus[Found] );
        return SERVER_OK ;
    }
    else
    {
        
    }


    fclose(DateBaseFile) ;  /*always don't forget to close opened file */
    return SERVER_CARD_ERROR ;


}




/* brief            : this fuction used to save the accepted transaction data
 * param [input]    : pstr_CardData pointer to struct that hold all client data 
 * param [input]    : TerminalData pointer to terminal struct that hold all required data to terminal 
 * param [input]    :TransactionStatus  pointer to string that hold the transaction status  
 * Return ServerStatus_t : enum if located will return SERVER_OK *
 */
ServerStatus_t SERVER_StoreTransactionDate(str_cardData_t * pstr_CardData ,str_terminalData_t * TerminalData ,uint8_t * TransactionStatus )
{
        FILE * DataBaseFile  = NULL;
        DataBaseFile = fopen(pstr_CardData->pu8_primaryAccountNumber , "a+");   /* oppend file with card number name */
        if(DataBaseFile == NULL)
        {
            return SERVER_FILE_ERROR ;
        }
        else
        {
           fprintf(DataBaseFile , "%s  TransactionStatus is %s\n"  ,TerminalData->transactionDate,TransactionStatus);  
        }


    
    return SERVER_OK ; 
}


