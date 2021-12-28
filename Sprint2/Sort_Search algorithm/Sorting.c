

#include "Sorting.h"


SortingStauts_t Swap(SortDataType_t * Data1 , SortDataType_t * Data2)
{
    if((Data2 == NULL )||(Data1 == NULL ))
    {
        return SWAP_PARAM_ERROR ; 
    }
    
       SortDataType_t Temp = 0 ; 
       Temp = *Data1 ;
       *Data1= *Data2;
       *Data2 = Temp ;
       
    return SORT_OK ;
}




SortingStauts_t  Sort_Using_Bubble (SortDataType_t *  Data , uint32_t Size )
{
   bool BubbleFlag = false  ;
    
    if((Data == NULL)||(Size == 0 ))
    {
        return SORT_PARAAM_ERROR ;
    }
    else
    {
        for(uint32_t OuterIndex = 0 ; OuterIndex < Size; OuterIndex++)
        {
            BubbleFlag = false ;
            for(uint32_t InnerIndex = 0 ; InnerIndex < Size-1  ; InnerIndex++)
            {
                if(Data[InnerIndex] > Data[InnerIndex +1])
                {
                    if(Swap(&Data[InnerIndex] , &Data[InnerIndex+1])  != SORT_OK)
                    {
                        return SORT_SELECT_ERROR ;
                    }
                    
                    BubbleFlag = true ;
                }
 

            }
            if(!BubbleFlag)
            {
                break ;
            }
        }
    }
    return SORT_OK ;
    
}




SortingStauts_t  Sort_Using_Insertion(SortDataType_t *  Data , uint32_t Size )
{
    SortDataType_t TempData = 0 , tempdata2 = 0 ; 
    uint32_t TempIndex = 0  ;
    
    if((Data == NULL)||(Size == 0 ))
    {
        return SORT_PARAAM_ERROR ;
    }
    else
    {    
        for(uint32_t u32_Index = 1 ; u32_Index < Size ; u32_Index++)
        {
            TempData = Data[u32_Index] ;

            TempIndex = u32_Index ;
            while(Data[TempIndex] < Data[TempIndex-1] )
            {
                tempdata2 =  Data[TempIndex] ;              
                if(Swap(&Data[TempIndex] , &Data[TempIndex-1])  != SORT_OK)
                {
                    return SORT_SELECT_ERROR ;
                }   
                TempIndex-- ;
            }
        }   
    }
    
    return SORT_OK ;
        
}






SortingStauts_t   Sort_Using_Selection(SortDataType_t *  Data , uint32_t Size )
{

    if((Data == NULL)||(Size == 0 ))
    {
        return SORT_PARAAM_ERROR ;
    }
    else
    {
        for(uint32_t OuterIndex = 0 ; OuterIndex < Size -1; OuterIndex++)
        {

            for(uint32_t InnerIndex = OuterIndex ; InnerIndex < Size  ; InnerIndex++)
            {
                if(Data[OuterIndex] > Data[InnerIndex])
                {
                    if(Swap(&Data[OuterIndex] , &Data[InnerIndex])  != SORT_OK)
                    {
                        return SORT_SELECT_ERROR ;
                    }
                }
            }
        }
    }

        return SORT_OK ; 
   
}




SortingStauts_t   Sort_Using_Merge  (SortDataType_t *  Data , uint32_t Size )
{





        return SORT_OK ; 

}


SortingStauts_t   Sort_Using_Quack  (SortDataType_t *  Data , uint32_t Size )
{





        return SORT_OK ; 
}