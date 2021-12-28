#ifndef __SORTING_H__
#define __SORTING_H__



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* this determine the type of data that can be handle by this driver */
typedef uint32_t  SortDataType_t ;




typedef enum {SORT_OK = 0 , SWAP_PARAM_ERROR , SORT_PARAAM_ERROR , SORT_BUBBLE_ERROR ,SORT_SELECT_ERROR  } SortingStauts_t ;




typedef SortingStauts_t (*ptf_Sort_t)   (SortDataType_t * , uint32_t ) ; 




typedef struct str_Sorting
{
    
    ptf_Sort_t  ptf_BubbleSort   ; 
    ptf_Sort_t ptf_InsertionSort ;
    ptf_Sort_t ptf_SelectionSort  ; 
    
}str_Sort_t ;




/*this function used to swap two elements 
take pointers to these two elements */
SortingStauts_t Swap(SortDataType_t * Data1 , SortDataType_t * Data2);




/* here these are 3 sorting methods ( non recursion sorting algorithm) */

SortingStauts_t  Sort_Using_Bubble (SortDataType_t *  Data , uint32_t Size );





SortingStauts_t   Sort_Using_Selection (SortDataType_t *  Data , uint32_t Size );





SortingStauts_t   Sort_Using_Insertion (SortDataType_t *  Data , uint32_t Size );



/* here we implement another type of sorting (recursion sorting algorithm ) */



SortingStauts_t   Sort_Using_Merge  (SortDataType_t *  Data , uint32_t Size );


SortingStauts_t   Sort_Using_Quack  (SortDataType_t *  Data , uint32_t Size );


#endif /* __SORTING_H__*/