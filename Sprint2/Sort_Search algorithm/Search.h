#ifndef __SEARCH_H__
#define __SEARCH_H__





#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Sorting.h"




/* enum return the current status of searching function */
typedef enum {SEARCH_OK = 0 , SEARCH_NUM_FOUNDED  , SEARCH_NUM_NOT_FOUND , SEARCH_SORT_ERROR  } SearchStauts_t ;



/*typedef  pointer to function */ 
typedef SortingStauts_t (*Search_Sort_Method_t) (SortDataType_t *  Data , uint32_t Size );





/*
 * brief : this function is used search for any element in array 
 * param : Arr (input) pointer to array that we want to search 
 * param : size (input) size of array 
 * param : NumToSearch (Input) this is the number to search 
 */

SearchStauts_t Search_Linear(SortDataType_t * Arr ,uint32_t size , SortDataType_t Num  );








/*
 * brief : this function is used search for any element in array time complexity O(n) = log(n) better than linear search , 
 * best case scenario of time  = log(n)   
 * param : Arr (input) pointer to array that we want to search 
 * param : size (input) size of array 
 * param : NumToSearch (Input) this is the number to search 
 */

SearchStauts_t Search_Binary(SortDataType_t * ArrData ,uint32_t left ,uint32_t right  , SortDataType_t Num  , Search_Sort_Method_t fptr_SortMethod);












#endif /* __SEARCH_H__ */