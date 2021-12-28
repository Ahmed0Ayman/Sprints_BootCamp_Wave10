
#include "Search.h"




					
					
/*
 * brief : this function is used search for any element in array time complexity O(n) = n , 
 * best case scenario of time  = n  
 * param : Arr (input) pointer to array that we want to search 
 * param : size (input) size of array 
 * param : NumToSearch (Input) this is the number to search 
 */

SearchStauts_t
Search_Linear (SortDataType_t * Arr, uint32_t size,
	       SortDataType_t NumToSearch)
{

  /* search element by element */
  for (uint32_t u32_Index = 0; u32_Index < size; u32_Index++)
    {
      if (NumToSearch == Arr[u32_Index])
	{
	  return SEARCH_NUM_FOUNDED;
	}
      else
	{
	  ;
	}
    }


  return SEARCH_NUM_NOT_FOUND;	/* if reached here then Not found */

}



					
/*
 * brief : this function is used search for any element in array time complexity O(n) = log(n) better than linear search , 
 * best case scenario of time  = log(n)   
 * param : Arr (input) pointer to array that we want to search 
 * param : size (input) size of array 
 * param : NumToSearch (Input) this is the number to search 
 */

SearchStauts_t
Search_Binary (SortDataType_t * ArrData, uint32_t left, uint32_t right,
	      SortDataType_t NumToSearch,
	      Search_Sort_Method_t fptr_SortMethod)
{
  uint32_t size = right - left;


  SortDataType_t Left = left, Right = right, Mid = Left + (right - left) / 2;


  /* first check with Bubble sort U(1) if array is sorted */
  bool BubbleFlag = false;

  /* to avoid multiple check if sorted or not */
  static bool SortedFlag = false;


  if (SortedFlag == false)
    {
      for (uint32_t InnerIndex = 0; InnerIndex < size - 1; InnerIndex++)
	{
	  if (ArrData[InnerIndex] > ArrData[InnerIndex + 1])
	    {
	      if (Swap (&ArrData[InnerIndex], &ArrData[InnerIndex + 1]) !=
		  SORT_OK)
		{
		  SortedFlag = false;
		  return SORT_SELECT_ERROR;
		}

	      BubbleFlag = true;
	      SortedFlag == true;
	    }
	}
    }
  if (BubbleFlag == true)
    {
      if (fptr_SortMethod (ArrData, size) != SORT_OK)
	{
	  return SEARCH_SORT_ERROR;
	}
      else
	{
	  BubbleFlag = true;
	}
    }
  else
    {

      /* if number equal to mid number in array return found */
      if (NumToSearch == ArrData[Mid])
	{
	  SortedFlag = false;
	  return SEARCH_NUM_FOUNDED;
	}
      if ((Right - Left) == 1)
	{

	  /* search if number is equal to one of array bondries */
	  if ((ArrData[Right] == NumToSearch)
	      || (ArrData[Left] == NumToSearch))
	    {
	      SortedFlag = false;
	      return SEARCH_NUM_FOUNDED;
	    }
	  else
	    {
	      SortedFlag = false;
	      return SEARCH_NUM_NOT_FOUND;	/* if reached here then element is not found */
	    }
	}
      else
	{
	  /* if less than mid then search on left side array */
	  if (NumToSearch < ArrData[Mid])
	    {
	      Right = Mid;
	      return Search_Binary (ArrData, Left, Right, NumToSearch,fptr_SortMethod);
	    }
	  else
	    {
	      Left = Mid;
	      return Search_Binary (ArrData, Left, Right, NumToSearch,
			     fptr_SortMethod);
	    }


	}


    }



	return SEARCH_OK ;

}
