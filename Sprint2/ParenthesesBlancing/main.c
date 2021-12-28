
/*************************************************************INCLUDES********************************************/
#include <stdio.h>
#include "Stack.h"
#include "LinkedList.h"
#include "Balance.h"



/*************************************************************GLOBAL_VAR************************************************/

pstr_Node_t Head;


LinkedDataType_t  Data ;



/*******************************************************************APIS*************************************************/

int main (int argc , char * argv[])
{

    if(argc <= 1)
    {
        printf("Please enter any argument to check \n");
    }
    for(uint32_t u32_Index = 1 ; u32_Index < argc ; u32_Index++)
    {
        if(Check_ParenthesesBlancing(argv[u32_Index]) == LINE_BALANCED)
        {
            printf ("*********This line ***********\n%s is blanaced \n\n", argv[u32_Index] );
        }
		else
		{
            printf ("*********This line ***********\n%s is not blanaced \n\n", argv[u32_Index] );			
		}
    }



  return 0;
}
