#include "Terminal.h"




/*
 * brief            : this fuction used to filter the input from client from any string 
 * param [input/output]    : pu8_Str1 pointer to pointer to string 
 * Return TernimalStatus_t : return the status of this function only TERMINAL_OK indicate true 
 */
TernimalStatus_t Terminal_GetNumsINString(uint8_t ** pu8_Str1 )
{
    uint32_t u8_Index_OldStr  = 0 , u8_Index_NewStr = 0   ;
    uint8_t * Pu8_NewStr = NULL , *pu8_OldStr1  = *pu8_Str1 ; 
    if(pu8_Str1 == NULL)
    {
        return TERMINAL_PARAM_ERROR ;
    }
    else
    {
        Pu8_NewStr = (uint8_t *)malloc(sizeof(uint8_t ) * CARD_NAME_HOLDER_LEN);
        if(Pu8_NewStr == NULL)
        {
            return TERMINAL_HEAP_ERROR ;
        }
        else
        {
                ;
        }
    }
    
    
    
    while(pu8_OldStr1[u8_Index_OldStr] != '\0')
    {
        if((pu8_OldStr1[u8_Index_OldStr] >= 0x30 ) && ( pu8_OldStr1[u8_Index_OldStr] <= 0x39))
        {
            Pu8_NewStr[u8_Index_NewStr++]  =  pu8_OldStr1[u8_Index_OldStr] ;
        }

        u8_Index_OldStr++ ;
        
    }
    Pu8_NewStr[u8_Index_NewStr++] = '\0' ;
    *pu8_Str1 =  Pu8_NewStr ;


    return TERMINAL_OK ;
}





/* brief            : this fuction used to search for a giving string (month) and return month in number  
 * param [input/output]    : Str pointer to  string that will be checked 
 * Return MonthOfYear_t : return the number of month of course return zero means error 
 */
MonthOfYear_t Terminal_SearchForMonth(uint8_t * Str)
{
    uint8_t  u8_Index =0 ;
    MonthOfYear_t Flag = 0 ;
    if(Str == NULL )
    {
        return TERMINAL_PARAM_ERROR ;
    }
    while (Str[u8_Index] != '\0')
    {
        switch(Str[u8_Index])
        {
            case 'J' :
                if((Str[u8_Index+1] == 'a') &&(Str[u8_Index+2] == 'n'))
                {
                    Flag = JANUARY ;
                }else   if((Str[u8_Index+1] == 'u') &&(Str[u8_Index+2] == 'l'))
                {
                    Flag = JULY ;
                }else if ((Str[u8_Index+1] == 'u') &&(Str[u8_Index+2] == 'n'))
                {
                    Flag = JUNE ;
                }else{
                }

            break ;

            case 'F' :
                if ((Str[u8_Index+1] == 'e') &&(Str[u8_Index+2] == 'b'))
                {
                    Flag = FEBRUARY ;
                }else{
                }               

            break ; 

            case 'M' :
                if((Str[u8_Index+1] == 'a') &&(Str[u8_Index+2] == 'c'))
                {
                    Flag = MARCH ;
                }else if ((Str[u8_Index+1] == 'a') &&(Str[u8_Index+2] == 'y'))
                {
                    Flag =  MAY ;
                }else{
                }               

            break ; 

            case 'A' :
                if ((Str[u8_Index+1] == 'p') &&(Str[u8_Index+2] == 'r'))
                {
                    Flag =  APRIL ;
                }else if((Str[u8_Index+1] == 'u') &&(Str[u8_Index+2] == 'g'))
                {
                    Flag =  AUGUST ;

                }else{
                }               

            break ; 

            case 'D' :
                if ((Str[u8_Index+1] == 'e') &&(Str[u8_Index+2] == 'c'))
                {
                    Flag =  DECEMBER ;
                }else{
                }               

            break ; 
 
            case 'S' :
                if ((Str[u8_Index+1] == 'e') &&(Str[u8_Index+2] == 'c'))
                {
                    Flag =  SEPTEMPER ;
                }else{
                }  
            break ; 

            case 'O' :
                if ((Str[u8_Index+1] == 'c') &&(Str[u8_Index+2] == 't'))
                {
                    Flag =  OCTOBER ;
                }else{
                } 
            break ; 

            case 'N' :
                if ((Str[u8_Index+1] == 'o') &&(Str[u8_Index+2] == 'v'))
                {
                    Flag =  NOVEMBER ;
                }else{
                        ;
                } 
            break ; 
            default :
                    Flag = 0 ;
            break  ;         

        }
        u8_Index++;
        if(Flag != 0)
        {
            break ;
        }
    }
    
        return Flag ;


}






/* 
 * brief            : this fuction used to format the entered name from client to server stile   
 * param [input]    : EnteredName pointer to  string that hold entered name  
 * param [input]    : pstr_CardData pointer to the entered card data from the user 
 * Return TernimalStatus_t : return the TERMINAL_OK if every thing is ok 
 */
TernimalStatus_t Terminal_SetNameForServer(uint8_t * EnteredName ,  str_cardData_t * pstr_CardData){
    uint32_t EnteredNameIndex = 0 , CardNameIndex = 0 ; 
    if((EnteredName == NULL )||(pstr_CardData == NULL))
    {
        return TERMINAL_PARAM_ERROR ;
    }else
    {
        while(EnteredName[EnteredNameIndex] != '\0')
        {
            /* remove all Numbers and speces */
            if((EnteredName[EnteredNameIndex] == ' ') || ((EnteredName[EnteredNameIndex] < 0x3a ) && (EnteredName[EnteredNameIndex] > 0x2f ))) 
            {
                EnteredNameIndex++ ;
            }
            else
            {
                if((EnteredName[EnteredNameIndex]  >=  0x41  )&& (EnteredName[EnteredNameIndex]  <= 0x5a  ))
                {
                        pstr_CardData->pu8_cardHolderName[CardNameIndex++] = EnteredName[EnteredNameIndex++] + CAP_TO_SMALL_OFFSET ;
                }
                else
                {
                    pstr_CardData->pu8_cardHolderName[CardNameIndex++] = EnteredName[EnteredNameIndex++] ;
                }             
            }  

        }


     pstr_CardData->pu8_cardHolderName[CardNameIndex] =  '\0' ;


     #if ( __DEBUG__ == 1 )
     printf("this message from debugging mode Terminal_SetNameForServer name is  %s \n",pstr_CardData->pu8_cardHolderName );
     #endif

    }


    return TERMINAL_OK ;


}






/*
 * brief            : this fuction used to format the entered name from client to server stile   
 * param [input]    : EnteredName pointer to  string that hold entered name  
 * param [input]    : pstr_CardData pointer to the entered card data from the user 
 * Return TernimalStatus_t : return the TERMINAL_OK if every thing is ok 
 */
TernimalStatus_t Terminal_CollectCardData(str_cardData_t * pstr_CardData)
{
    TernimalStatus_t TerminalStatus = 0 ; 
    uint8_t CardEnteredName[CARD_NAME_HOLDER_LEN+1] = {0} ; 
    pstr_CardData->pu8_cardHolderName = (uint8_t *)malloc(sizeof(uint8_t )* CARD_NAME_HOLDER_LEN+1) ;
    if(pstr_CardData->pu8_cardHolderName == NULL)
    {
        return TERMINAL_HEAP_ERROR ;
    }
    else
    {
        pstr_CardData->pu8_primaryAccountNumber = (uint8_t *)malloc(sizeof(uint8_t )* CARD_NUM_LEN+1) ; 
        if(pstr_CardData->pu8_primaryAccountNumber == NULL)
        {
            return TERMINAL_HEAP_ERROR ;
        }
        else
        {
           pstr_CardData->pu8_cardExpirationDate = (uint8_t *)malloc(sizeof(uint8_t )* CARD_EXPIR_DATE_LEN+1) ;
           if(pstr_CardData->pu8_cardExpirationDate == NULL)
           {
                return TERMINAL_HEAP_ERROR ;
           }
           else
           {
               pstr_CardData->pu8_CardCVV = (uint8_t *)malloc(sizeof(uint8_t )* CARD_CVV_LEN+1) ;
               if(pstr_CardData->pu8_CardCVV == NULL)
               {
                    return TERMINAL_HEAP_ERROR ;
               }
               else
               {
                   ;
               }
           }
           
        }
    }

    
    memset(ClientMassage , 0x00 ,CARD_NAME_HOLDER_LEN+1 ); 
    sprintf(ClientMassage , "enter the cardHolder name \n"  );
    SocketSend(ClientMassage, ClientHSocket_Id);
    memset(CardEnteredName , 0x00 ,CARD_NAME_HOLDER_LEN+1 ); 
    SocketReceive(CardEnteredName, CARD_NAME_HOLDER_LEN ,ClientHSocket_Id); 


    if(Terminal_SetNameForServer(CardEnteredName ,pstr_CardData) != TERMINAL_OK)
    {
        return TERMINAL_CARD_ERROR ;
    }
    else
    {
        ;
    }





    do
    {

        memset(ClientMassage , 0 ,CARD_NAME_HOLDER_LEN+1 );
        sprintf(ClientMassage , "Please your card account Numder : \n"  );
        SocketSend(ClientMassage, ClientHSocket_Id);
        SocketReceive(pstr_CardData->pu8_primaryAccountNumber, CARD_NUM_LEN ,ClientHSocket_Id); 
        TerminalStatus = Terminal_GetNumsINString(&pstr_CardData->pu8_primaryAccountNumber);


    }while((TerminalStatus != 0 )||(strlen(pstr_CardData->pu8_primaryAccountNumber) != SERVER_CARD_NUM_LEN)) ;    
    #if( __DEBUG__ == 0)
    system("cls");
     #endif 
  

    // now we'll collect Card Date expire 
    do
    {

        memset(ClientMassage , 0 ,CARD_NAME_HOLDER_LEN+1 );       
        sprintf(ClientMassage , "Please your card Expire Date  in format YY/MM : \n"  );
        SocketSend(ClientMassage, ClientHSocket_Id);
        SocketReceive(pstr_CardData->pu8_cardExpirationDate , CARD_EXPIR_DATE_LEN ,ClientHSocket_Id);
        TerminalStatus = Terminal_GetNumsINString(&pstr_CardData->pu8_cardExpirationDate);
       
    }while((TerminalStatus != 0 )||(strlen(pstr_CardData->pu8_cardExpirationDate) != SERVER_CARD_DATE_LEN)) ;      
    #if( __DEBUG__ == 0)
    system("cls");
    #endif 
   
    
    // New Collect CVV Number 
    do
    {
        memset(ClientMassage , 0 ,CARD_NAME_HOLDER_LEN+1 );       
        sprintf(ClientMassage , "Please your card CVV in format NNN : \n"  );
        SocketSend(ClientMassage, ClientHSocket_Id);
        SocketReceive(pstr_CardData->pu8_CardCVV , CARD_CVV_LEN ,ClientHSocket_Id);   
        TerminalStatus = Terminal_GetNumsINString(&pstr_CardData->pu8_CardCVV); 


    }while((TerminalStatus != 0 )||(strlen(pstr_CardData->pu8_CardCVV) != SERVER_CARD_CVV_LEN)) ;      
    #if( __DEBUG__ == 0)
    system("cls");
     #endif   
        
    // Now we reach to collecting all user card data 

    #if( __DEBUG__ == 1)
    printf("%s\n" , pstr_CardData->pu8_primaryAccountNumber);
    #endif

    return TERMINAL_OK ; 
}




/* 
 * brief            : this fuction used to get the transaction amount from the user   
 * param [input]    : ST_terminalData pointer struct the hold all transaction information   
 * Return TernimalStatus_t : return the TERMINAL_OK if every thing is ok 
 */
TernimalStatus_t Terminal_GetTransactionAmount(str_terminalData_t *ST_terminalData)
{
    uint8_t  ClientMassage[100+1] ={0};
    if(ST_terminalData == NULL)
    {
        return TERMINAL_PARAM_ERROR ;
    }
    else
    {

        do{ 

        ST_terminalData->maxTransAmount = MAX_WITHDRAW_DAILY ;
        memset(ClientMassage , 0 ,100 + 1 );       
        sprintf(ClientMassage , "Please enter right Transaction amount from 1 to %f \n" , MAX_WITHDRAW_DAILY);
        SocketSend(ClientMassage, ClientHSocket_Id);
        memset(ClientMassage , 0 ,100+1 );  
        SocketReceive(ClientMassage , CARD_CVV_LEN ,ClientHSocket_Id);  
        ST_terminalData->transAmount = atoi(ClientMassage) ;


        }while((ST_terminalData->transAmount <= 0 )||(ST_terminalData->transAmount > MAX_WITHDRAW_DAILY));
    }
    return TERMINAL_OK ;

}







/* 
 * brief            : this fuction used to check the expired data of client card    
 * param [input]    : pstr_CardData pointer struct the hold all card information   
 * Return TernimalStatus_t : return the TERMINAL_OK if every thing is ok 
 */
TernimalStatus_t Terminal_CheckCardDate(str_cardData_t * pstr_CardData)
{

    uint8_t   StrCurrentYear[8] = {0}; 
    uint8_t u8_EnteredMonth = 0 ,  u8_CurrentMonth = 0 ;
    uint16_t u16_CurrentYear = 0 , u16_EnteredYear = 0  ;
    uint8_t StrAllDataFormate[30] ={0} ;
    time_t Str_Time ;



    if(pstr_CardData == NULL)
    {
        return TERMINAL_PARAM_ERROR ;
    }
    else
    {
        ;
    }
    uint8_t ArrYear[3] = { *(pstr_CardData->pu8_cardExpirationDate+0), *(pstr_CardData->pu8_cardExpirationDate+1) ,0}, \
                            ArrMonth[3] = {*(pstr_CardData->pu8_cardExpirationDate+2) , *(pstr_CardData->pu8_cardExpirationDate+3),0} ; 



    u8_EnteredMonth = atoi(ArrMonth);
    u16_EnteredYear  = atoi(ArrYear);   

    #if( __DEBUG__ == 1)
    printf("Entered month %d \n" , u8_EnteredMonth ) ;
    printf("Entered year %d  \n" , u16_EnteredYear ) ;
    #endif

    time(&Str_Time);
    strcpy(StrAllDataFormate ,ctime(&Str_Time));

    u8_CurrentMonth = Terminal_SearchForMonth(StrAllDataFormate);
    strcpy(StrCurrentYear , &StrAllDataFormate[strlen(StrAllDataFormate) - 3  ]) ;
    u16_CurrentYear =  atoi(StrCurrentYear);                     

    #if( __DEBUG__ == 1)
    printf("current month %d \n" , u8_CurrentMonth ) ;
    printf("current year %d  \n" , u16_CurrentYear ) ;
    #endif

    if(( u16_CurrentYear <= u16_EnteredYear ))
    {
        if((u8_CurrentMonth < u8_EnteredMonth)&&( u16_CurrentYear == u16_EnteredYear ))
        {
            return TERMINAL_CARD_ERROR ;
        }
        else
        {
            return TERMINAL_OK ; 
        }
    }
    else
    {
        return TERMINAL_OK ; 
    }

 

}






/* 
 * brief            : this fuction used to check the expired data of client card    
 * param [input]    : pstr_CardData pointer struct the hold all card information
 * param [input]    : pstr_CardData pointer struct the hold all transaction information     
 * Return TernimalStatus_t : return the TERMINAL_OK if every thing is ok 
 */
TernimalStatus_t Terminal_Processing(str_cardData_t * pstr_CardData ,str_terminalData_t * TerminalData)
{
    time_t Str_Time ;

    if(Terminal_CollectCardData(pstr_CardData) != TERMINAL_OK)
    {
        #if( __DEBUG__ == 1)
        printf("error in  Terminal_CollectCardData() Function \n");
        #endif
        return TERMINAL_CARD_ERROR ; 
    }



    time(&Str_Time);
    strcpy(TerminalData->transactionDate , ctime(&Str_Time));
    #if (__DEBUG__ == 1)   
        printf("%s\n",TerminalData->transactionDate);
    #endif



    if(Terminal_CheckCardDate(pstr_CardData) != TERMINAL_OK)
    {
        #if( __DEBUG__ == 1)
        printf("error in  Terminal_CheckCardDate() Function \n");
        #endif
        return TERMINAL_CARD_ERROR ;
    }

    if(Terminal_GetTransactionAmount(TerminalData) != TERMINAL_OK)
    {
        #if( __DEBUG__ == 1)
        printf("error in  Terminal_GetTransactionAmount() Function \n");
        #endif
        return TERMINAL_CARD_ERROR ; 
    }



}

