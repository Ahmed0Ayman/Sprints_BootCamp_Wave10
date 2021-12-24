
/*************************************************************INCLUDEES********************************************/


#include "Balance.h"





/*************************************************************GLOBAL_VAR************************************************/



/* stack top poiner (linked list header) */
pstr_Node_t pstr_Stack1Opened  ;







/*******************************************************************APIS*************************************************/



/*
 * brief  : this function used to check if the parentheses are balanced for any giving line  
 * param. : ( input )Ptr_CheckLine  parameter point to the start line character  : 
 * return : (output )uint32_t enum that indicate the status of the checking line for balancing 
 */
 
uint32_t Check_ParenthesesBlancing(uint8_t * Ptr_CheckLine )
{
    uint8_t u8_Index = 0 , u8_PopDataopen =0  , u8_PopDataClose = 0 ;
    
    if(Ptr_CheckLine == NULL)   /* ckeck that the line pointer is not null */
    {
        return BALANCING_PTR_ERROR ;
    }
    
    
    while(Ptr_CheckLine[u8_Index] != '\0')  /* check all characters on the giving line */
    {
        
        
        
        /* here we check 3 conditions 
        1- open parentheses         ---> push to stack 
        2- closed paarentheses      ---> pop the last element from stack and compare it with the current parentheses 
        3 - any other ordinary Charecter  --> escape that character  
        */
        
        
        if((Ptr_CheckLine[u8_Index] == '(')||(Ptr_CheckLine[u8_Index] == '{')||(Ptr_CheckLine[u8_Index] == '['))
        {
            Stack_Push( &pstr_Stack1Opened , &Ptr_CheckLine[u8_Index]);
        }
        else if((Ptr_CheckLine[u8_Index] == ')')||(Ptr_CheckLine[u8_Index] == '}')||(Ptr_CheckLine[u8_Index] == ']'))
        {
            if(Stack_Pop(&pstr_Stack1Opened , &u8_PopDataClose) != STACK_OK ) 
            {
                return NOT_BALANCING ;
            }
            
            
            /* according to ascii code the subtraction between 2 parentheses 1 or 2 */                 
            if((Ptr_CheckLine[u8_Index] -  u8_PopDataClose) & 0x03 )  
            {
                
            }
            else
            {
                return NOT_BALANCING ;   
            }
        }
        else
        {
            ;
        }
        
        u8_Index++ ;
    }
    
        
    if(Stack_IsEmpty(&pstr_Stack1Opened) == STACK_ISNOT_EMPTY)   
    {
        return NOT_BALANCING ;         /* here this mean stack still having an elements so that its unbalanced */ 
    }
    
    
    
    return LINE_BALANCED ;  /* if we reach  here this mean that that line is balanced */
    
}   /* END_OF_FUN   Check_ParenthesesBlancing() */
 