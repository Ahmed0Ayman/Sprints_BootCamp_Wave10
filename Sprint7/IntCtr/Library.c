
#include "Library.h"




/****************************************************
*										Cpu_Driver											*
****************************************************/
static uint32 NestedNum ;




void  CpuDriver_StartCriticalSection(void)
{
	CpuDriver_DisableglobalInterrupt();
	NestedNum++;
	
}



void CpuDriver_StopCriticalSection(void)
{
	uint8 TempState ; 
	CpuDriver_DisableglobalInterrupt();	
	switch(NestedNum)
	{
		case 0 :
			TempState = 1 ;
			break ;
		case 1 :
			TempState = 1 ;
			NestedNum-- ;
			break ;
		default :
			--NestedNum ;
			TempState = 0 ;
			break ;
	}
	
	if(TempState == 1 )
	{
		CpuDriver_EnableglobalInterrupt();
	}else
	{
		
	}
	
}
