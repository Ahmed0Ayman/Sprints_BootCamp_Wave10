
#include "Terminal.h"




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
        Pu8_NewStr = (uint8_t *)malloc(sizeof(uint8_t ) * 14);
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
                    Flag == JANUARY ;
                }else   if((Str[u8_Index+1] == 'u') &&(Str[u8_Index+2] == 'l'))
                {
                    Flag == JULY ;
                }else if ((Str[u8_Index+1] == 'u') &&(Str[u8_Index+2] == 'n'))
                {
                    Flag = JUNE ;
                }else{
                        ;
                }

            break ;

            case 'F' :
                if ((Str[u8_Index+1] == 'e') &&(Str[u8_Index+2] == 'b'))
                {
                    Flag = FEBRUARY ;
                }else{
                        ;
                }               

            break ; 

            case 'M' :
                if((Str[u8_Index+1] == 'a') &&(Str[u8_Index+2] == 'c'))
                {
                    Flag == MARCH ;
                }else if ((Str[u8_Index+1] == 'a') &&(Str[u8_Index+2] == 'y'))
                {
                    Flag =  MAY ;
                }else{
                        ;
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
                        ;
                }               

            break ; 

            case 'D' :
                if ((Str[u8_Index+1] == 'e') &&(Str[u8_Index+2] == 'c'))
                {
                    Flag =  DECEMBER ;
                }else{
                        ;
                }               

            break ; 
 
            case 'S' :
                if ((Str[u8_Index+1] == 'e') &&(Str[u8_Index+2] == 'c'))
                {
                    Flag =  SEPTEMPER ;
                }else{
                        ;
                }  
            break ; 

            case 'O' :
                if ((Str[u8_Index+1] == 'c') &&(Str[u8_Index+2] == 't'))
                {
                    Flag =  OCTOBER ;
                }else{
                        ;
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





TernimalStatus_t Terminal_CollectCardData(struct ST_cardData_t * pstr_CardData)
{
    TernimalStatus_t TerminalStatus = 0 ; 
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
    
    printf("Please your card Holder Name : \n");
    fgets(pstr_CardData->pu8_cardHolderName,CARD_NAME_HOLDER_LEN , stdin);    
    do
    {
        printf("Please your card account Numder : \n");
        fflush(stdin);fgets(pstr_CardData->pu8_primaryAccountNumber,CARD_NUM_LEN , stdin);
        TerminalStatus = Terminal_GetNumsINString(&pstr_CardData->pu8_primaryAccountNumber);
        
    }while((TerminalStatus != 0 )||(strlen(pstr_CardData->pu8_primaryAccountNumber) != 14)) ;    
    system("cls");
  

    // now we'll collect Card Date expire 
    do
    {
        printf("Please your card Expire Date  in format YY/MM : \n");
        fflush(stdin);fgets(pstr_CardData->pu8_cardExpirationDate , CARD_NUM_LEN , stdin);
        TerminalStatus = Terminal_GetNumsINString(&pstr_CardData->pu8_cardExpirationDate);
        
    }while((TerminalStatus != 0 )||(strlen(pstr_CardData->pu8_cardExpirationDate) != 4)) ;      
    system("cls");
   
    
    // New Collect CVV Number 
    do
    {
        printf("Please your card CVV in format NNN : \n");
        fflush(stdin);fgets(pstr_CardData->pu8_CardCVV , CARD_CVV_LEN , stdin);
        TerminalStatus = Terminal_GetNumsINString(&pstr_CardData->pu8_CardCVV);
        
    }while((TerminalStatus != 0 )||(strlen(pstr_CardData->pu8_CardCVV) != 3)) ;      
    system("cls");
    
        
    // Now we reach to collecting all user card data 
    #if( __DEDUG__ == 1)
    printf("%s\n" , pstr_CardData->pu8_primaryAccountNumber);
    #endif
}


TernimalStatus_t Terminal_CheckCardDate(struct ST_cardData_t * pstr_CardData)
{


    if(strcat == NULL)
    {
        return TERMINAL_PARAM_ERROR ;
    }
    else
    {
        ;
    }
    uint8_t ArrYear[3] = { *(pstr_CardData->pu8_cardExpirationDate+0), *(pstr_CardData->pu8_cardExpirationDate+1) ,0}, \
                            ArrMonth[3] = {*(pstr_CardData->pu8_cardExpirationDate+2) , *(pstr_CardData->pu8_cardExpirationDate+3),0} ; 
                  uint8_t   StrCurrentYear[8] = {0}; 
    uint8_t u8_EnteredMonth = 0 ,  u8_CurrentMonth = 0 ;
    uint16_t u16_CurrentYear = 0 , u16_EnteredYear = 0  ;
    uint8_t StrAllDataFormate[30] ={0} ;
    #if( __DEDUG__ == 1)
    printf("month %s \n" , ArrMonth ) ;
    printf("year %s  \n" , ArrYear ) ;
    #endif

    u8_EnteredMonth = atoi(ArrMonth);
    u16_EnteredYear  = atoi(ArrYear);   

    #if( __DEDUG__ == 1)
    printf("entered month %d \n" , u8_EnteredMonth ) ;
    printf("year %d  \n" , u16_EnteredYear ) ;
    #endif

    time_t Str_Time ;
    time(&Str_Time);
    strcpy(StrAllDataFormate ,ctime(&Str_Time));

    u8_CurrentMonth = Terminal_SearchForMonth(StrAllDataFormate);
    strcpy(StrCurrentYear , &StrAllDataFormate[strlen(StrAllDataFormate) - 3  ]) ;
    u16_CurrentYear =  atoi(StrCurrentYear);                     

    #if( __DEDUG__ == 1)
    printf("current month %d \n" , u8_CurrentMonth ) ;
    printf("current year %d  \n" , u16_CurrentYear ) ;
    #endif

    if(( u16_CurrentYear <= u16_EnteredYear )&&(u8_CurrentMonth <= u8_EnteredMonth))
    {
        return TERMINAL_OK ; 

    }
    else
    {
        return TERMINAL_CARD_ERROR ;
    }
}