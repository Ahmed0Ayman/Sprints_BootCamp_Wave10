
/*************************************************************INCLUDEES********************************************/


#include "Stack.h"



/************************************************************GLOBAL_STATIC_VAR**************************************/



static unsigned int StackCurrSize  ;




/************************************************************APIS_IMPLEMENTATION*************************************/





/*
 * brief  :  this function used to push data to stack   
 * param. : ( input )ppstr_DatasStack  ponter to pointer to the head of the  list 
 * param. : ( input )Data  ponter  to the verable that  hold data  
 * return : (output )StackStatus_t enum that indicate the status of the stack  
 */
StackStatus_t   Stack_Push(pstr_Stack_t *  ppstr_DatasStack, LinkedDataType_t * Data )
{
    
    
    uint32_t LinkedListStatus = 0 ;
    if((ppstr_DatasStack == NULL)||(Data == NULL))
    {
        return STACK_PTR_ERROR ;
    }
    
    
    LinkedListStatus = LinkedList_add_node_to_the_front( *Data, ppstr_DatasStack);
    if(LinkedListStatus != 0)
    {
        return STACK_PUSH_ERROR ;
    }
    else
    {
        ;
    }
    
    StackCurrSize++;
    return STACK_OK ;

}



/*
 * brief  :  this function used to pop data o from stack   
 * param. : ( input )ppstr_DatasStack  ponter to pointer to the head of the  list 
 * param. : ( output )Data  ponter  to the verable that will receive data  
 * return : (output )StackStatus_t enum that indicate the status of the stack  
 */
StackStatus_t  Stack_Pop(pstr_Stack_t * ppstr_DatasStack, LinkedDataType_t * Data )
{
    
    
    uint32_t LinkedListStatus = 0 ;
   
    if((ppstr_DatasStack == NULL)||(Data == NULL))
    {
        return STACK_PTR_ERROR ;
    }
    
    LinkedListStatus =LinkedList_Node_GetData( Data , *ppstr_DatasStack   , 1 ); 
    if(LinkedListStatus != 0)
    {
        return STACK_POP_ERROR ;
    }
    else
    {
        ;
    }
    
        
    LinkedListStatus = LinkedList_delete_specific_node(ppstr_DatasStack , 1 );
    if(LinkedListStatus != 0)
    {
        return STACK_POP_ERROR ;
    }
    else
    {
        ;
    }
    
    StackCurrSize-- ;
    return STACK_OK ;
}



/*
 * brief  :  this function used to pop data o from stack   
 * param. : ( input )ppstr_DatasStack  ponter to pointer to the head of the  list 
 * param. : ( output )Data  ponter  to the verable that will receive data  
 * return : (output )StackStatus_t enum that indicate the status of the stack  
 */
StackStatus_t  Stack_Top(pstr_Stack_t * ppstr_DatasStack , LinkedDataType_t * Data )
{
    
    if((*ppstr_DatasStack == NULL)||(Data == NULL))
    {
        return STACK_TOP_ERROR ;
    }
    else
    {
        return LinkedList_Node_GetData( Data , *ppstr_DatasStack   , 1 ); /* if return 0 then operation is performed okey */
    }
    
 }





/*
 * brief  :  this function used to check if stack is empty or not 
 * param. : ( input )ppstr_DatasStack  ponter to pointer to the head of the  list 
 * return : (output )StackStatus_t enum that indicate the status of the stack   
 */
 
StackStatus_t  Stack_IsEmpty(pstr_Stack_t * ppstr_DatasStack)
{

    if(*ppstr_DatasStack == NULL)
    {
        return STACK_IS_EMPTY ;
    }
    else
    {
        ;
    }
    
    
    return STACK_ISNOT_EMPTY ;    
    
    
}



uint32_t Stack_len(pstr_Stack_t ppstr_DatasStack)
{
    
    return StackCurrSize ;
    
}




