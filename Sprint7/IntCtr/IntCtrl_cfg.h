#ifndef __INTCTRL_CFG_H__
#define __INTCTRL_CFG_H__
#include "Library.h"

extern uint8 IRQ_PRI[] ;


typedef enum { 
Reset_IRQ  = 1   	,
NMI_IRQ       		,       
HardFault_IRQ  		,   
MemManage_IRQ   	,    
BusFault_IRQ     	,  
UsageFault_IRQ    ,   
SVC_IRQ  = 11 		,
DebugMon_IRQ 			,
PendSV_IRQ = 14 	,		    
SysTick_IRQ				,  
GPIOA_IRQ   			,          
GPIOB_IRQ    			,         
GPIOC_IRQ     		,        
GPIOD_IRQ      		,       
GPIOE_IRQ    	   	,      
UART0_IRQ    	    ,     
UART1_IRQ         ,    
SSI0_IRQ          ,   
I2C0_IRQ          ,  
PMW0_FAULT_IRQ    , 
M0_0_IRQ 	        ,
PWM0_1_IRQ 	      ,
PWM0_2_IRQ        ,
QEI0_IRQ          ,
ADC0SS0_IRQ       ,
ADC0SS1_IRQ = 27	,          
ADC0SS2_IRQ 			,         
ADC0SS3_IRQ  			,        
WDT0_IRQ      		,        
TIMER0A_IRQ    		,      
TIMER0B_IRQ     	,     
TIMER1A_IRQ    	  ,    
TIMER1B_IRQ       ,   
TIMER2A_IRQ       ,  
TIMER2B_IRQ       , 
COMP0_IRQ         ,
COMP1_IRQ  =29		,           
COMP2_IRQ  				,          
SYSCTL_IRQ  			,         
FLASH_IRQ    			,        
GPIOF_IRQ     		,       
GPIOG_IRQ    		  ,      
GPIOH_IRQ     	  ,     
UART2_IRQ    	    ,    
SSI1_IRQ          ,    
TIMER3A_IRQ       ,   
TIMER3B_IRQ       ,  
I2C1_IRQ          , 
QEI1_IRQ          ,
CAN0_IRQ          ,
CAN1_IRQ  				,
CAN2_IRQ   				,           
HIB_IRQ      = 59	,          
USB0_IRQ     			,         
PWM0_3_IRQ    		,        
UDMA_IRQ       		,       
UDMAERR_IRQ     	,      
ADC1SS0_IRQ      	,     
ADC1SS1_IRQ       ,    
ADC1SS2_IRQ       ,   
ADC1SS3_IRQ       ,  
GPIOJ_IRQ  =  68 	,           
GPIOK_IRQ   			,          
GPIOL_IRQ    			,         
SSI2_IRQ  				,
SSI3_IRQ   				,           
UART3_IRQ   			,          
UART4_IRQ    			,         
UART5_IRQ     		,	        
UART6_IRQ      		,       
UART7_IRQ       	,      
I2C2_IRQ  = 78		,           
I2C3_IRQ					,           
TIMER4A_IRQ 			,    
TIMER4B_IRQ  			,   
TIMER5A_IRQ = 108	,     
TIMER5B_IRQ 			,    
WTIMER0A_IRQ 			,        
WTIMER0B_IRQ  		,    
WTIMER1A_IRQ   		,   
WTIMER1B_IRQ    	,  
WTIMER2A_IRQ     	, 
WTIMER2B_IRQ      ,
WTIMER3A_IRQ      ,
WTIMER3B_IRQ      ,
WTIMER4A_IRQ      ,
WTIMER4B_IRQ     	,
WTIMER5A_IRQ     	,
WTIMER5B_IRQ      ,
FPU_IRQ 					,  
I2C4_IRQ = 124		,        
I2C5_IRQ 					,       
GPIOM_Hand				,
GPION_Hand				,
QEI2_IRQ 					,      
GPIOP0_IRQ = 131	,            
GPIOP1_IRQ 				,    
GPIOP2_IRQ  			,    
GPIOP3_IRQ   			,  
GPIOP4_IRQ    		,  
GPIOP5_IRQ     		, 
GPIOP6_IRQ     		,
GPIOP7_IRQ      	,
GPIOQ0_IRQ    		,
GPIOQ1_IRQ     		, 
GPIOQ2_IRQ      	,
GPIOQ3_IRQ      	,
GPIOQ4_IRQ      	,
GPIOQ5_IRQ      	,
GPIOQ6_IRQ      	,
GPIOQ7_IRQ      	,
GPIOR_IRQ     	 	,
GPIOS_IRQ   	  	,
PMW1_0_IRQ	      ,     
PWM1_1_IRQ       	,    
PWM1_2_IRQ        ,   
PWM1_3_IRQ				,
PWM1_FAULT_IRQ		,  



_End_Of_IRQ_NUM 
}IRQ_Num_t ;



typedef struct
{
	uint32  	:5 ;
	uint32  INTA : 3 ;
	uint32  	:5 ;
	uint32  INTB : 3 ;
	uint32  	:5 ;
	uint32  INTC : 3 ;
	uint32  	:5 ;
	uint32  INTD : 3 ;
}IRQ_PRI_Bit_t;

typedef union
{
	IRQ_PRI_Bit_t IPQ_Bits ;
	uint32 IRQ_ALL ;
}IRQ_Reg_t ;






#endif  /* __INTCTRL_CFG_H__ */
