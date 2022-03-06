

#include "IntCtrl.h"




void IntCtr_PRI_init(void)
{
	for(uint8 iter = GPIOA_IRQ ; iter < _End_Of_IRQ_NUM ; iter++)
	{
			NVIC->IP[iter-16] = (uint8)(IRQ_PRI[iter] << 5u) ;
	}

		*(uint32 volatile *)(SCB->SHP) =  ((uint32)IRQ_PRI[MemManage_IRQ] << 5u) |
																			((uint32)IRQ_PRI[BusFault_IRQ] << 13u)  |
																			((uint32)IRQ_PRI[UsageFault_IRQ] << 18u);
		
		
		*(( uint32 volatile *)SCB->SHP +1) = ((uint32)IRQ_PRI[SVC_IRQ] << 29u) ;
		
		
		*((uint32 volatile *)SCB->SHP +2) = ((uint32)IRQ_PRI[DebugMon_IRQ] << 5u) | 
																				((uint32)IRQ_PRI[PendSV_IRQ]  << 21u) |
																				((uint32)IRQ_PRI[DebugMon_IRQ] << 29u);
}


