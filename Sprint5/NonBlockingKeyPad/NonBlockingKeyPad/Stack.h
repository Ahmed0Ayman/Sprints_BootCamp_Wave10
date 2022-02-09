/*
 * Stack.h
 *
 * Created: 2/9/2022 7:19:06 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef STACK_H_
#define STACK_H_




/*************************************************************INCLUDEES********************************************/



#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"



/* pointer to top of the stack */
typedef pstr_Node_t pstr_Stack_t ;





/* all stack return status you need to chect the return data id isn't STACK_OK then debug your code  */
typedef enum  {     STACK_OK = 0 , STACK_PTR_ERROR,STACK_POP_ERROR ,STACK_TOP_ERROR ,
                    STACK_PUSH_ERROR , STACK_IS_EMPTY , STACK_ISNOT_EMPTY }StackStatus_t; 








/*
 * brief  :  this function used to push data to stack   
 * param. : ( input )ppstr_DatasStack  ponter to pointer to the head of the  list 
 * param. : ( input )Data  ponter  to the verable that  hold data  
 * return : (output )StackStatus_t enum that indicate the status of the stack  
 */
StackStatus_t   Stack_Push(pstr_Stack_t *  ppstr_DatasStack, LinkedDataType_t * Data );







/*
 * brief  :  this function used to pop data o from stack   
 * param. : ( input )ppstr_DatasStack  ponter to pointer to the head of the  list 
 * param. : ( output )Data  ponter  to the verable that will receive data  
 * return : (output )StackStatus_t enum that indicate the status of the stack  
 */
StackStatus_t  Stack_Pop(pstr_Stack_t * ppstr_DatasStack, LinkedDataType_t * Data );







/*
 * brief  :  this function used to return data only and  without delete node from stack   
 * param. : ( input )ppstr_DatasStack  ponter to pointer to the head of the  list 
 * param. : ( output )Data  ponter  to the verable that will receive data  
 * return : (output )StackStatus_t enum that indicate the status of the stack  
 */
 
StackStatus_t  Stack_Top(pstr_Stack_t * ppstr_DatasStack , LinkedDataType_t * Data );






/*
 * brief  :  this function used to check if stack is empty or not 
 * param. : ( input )ppstr_DatasStack  ponter to pointer to the head of the  list 
 * return : (output )StackStatus_t enum that indicate the status of the stack   
 */
 
StackStatus_t  Stack_IsEmpty(pstr_Stack_t * ppstr_DatasStack);















#endif /* STACK_H_ */