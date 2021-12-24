
#ifndef __BALANCE_H__
#define __BALANCE_H__


/*************************************************************INCLUDEES********************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdint.h>
#include "Stack.h"
#include "LinkedList.h"






/*************************************************************CONSTANTS********************************************/


typedef enum  { LINE_BALANCED = 0 ,NOT_BALANCING , BALANCING_STACK_ERROR , BALANCING_PTR_ERROR }BalanceStatus_t;















/*
 * brief  : this function used to check if the parentheses are balanced for any giving line  
 * param. : ( input )Ptr_CheckLine  parameter point to the start line character  : 
 * return : (output )uint32_t enum that indicate the status of the checking line for balancing 
 */
 
 
BalanceStatus_t Check_ParenthesesBlancing(uint8_t * Ptr_CheckLine );









#endif   /* __BALANCE_H__ */