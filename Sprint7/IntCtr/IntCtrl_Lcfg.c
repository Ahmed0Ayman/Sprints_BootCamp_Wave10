#include "IntCtrl_cfg.h"



uint8 IRQ_PRI[_End_Of_IRQ_NUM] = 
{
	
	[GPIOA_IRQ] = 6	,          
	[GPIOB_IRQ] = 7 ,         
	[GPIOC_IRQ] = 5 ,        
	[GPIOD_IRQ] = 4 ,       
	[GPIOE_IRQ] = 5 ,      
	[UART0_IRQ] = 7 ,     
	[UART1_IRQ] = 3   	
	

	
};
