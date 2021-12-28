
#include <stdio.h>
#include "Sorting.h"
#include "Search.h"
#define __DEBUG__   1


/* here jest for test the input may be from any other file or from user command */
SortDataType_t  ga_Data[] = { 1,3,5,7,9,60,3,50,8,10 };


/* global struct used to grouping all sorting functions under one struct */
str_Sort_t gstr_Sort ; 




int main(void)
{
    SortDataType_t Num = 10 ; 
    gstr_Sort.ptf_BubbleSort     = Sort_Using_Bubble ; 
    gstr_Sort.ptf_InsertionSort  = Sort_Using_Selection ;
    gstr_Sort.ptf_SelectionSort   = Sort_Using_Insertion ; 
    

    #if (__DEBUG__  == 1)
    gstr_Sort.ptf_BubbleSort (ga_Data , sizeof(ga_Data)/sizeof(ga_Data[0]) );
    for(int i = 0 ; i <sizeof(ga_Data)/sizeof(ga_Data[0]) ; i++)
    {
        printf("%d ",ga_Data[i]);
    }
    printf("\n");
    #endif
 
        if(Search_Binary(ga_Data , 0 ,sizeof(ga_Data)/sizeof(ga_Data[0]) -1  ,Num, gstr_Sort.ptf_BubbleSort  ) == SEARCH_NUM_FOUNDED )
        {
            printf("this number%d is founded \n ",Num);
        }
        else
        {
            printf("this number%d is not founded \n ",Num);          
        }
 
	
	fflush(stdin);getchar(); 	/* keep terminal */
    return 0;
}
