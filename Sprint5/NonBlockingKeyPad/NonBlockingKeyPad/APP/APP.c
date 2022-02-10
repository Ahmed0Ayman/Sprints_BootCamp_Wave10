/*
 * APP.c
 *
 * Created: 2/8/2022 3:05:47 PM
 *  Author: Ahmed_Ayman
 */ 



#include "APP.h"
uint32_t SystemTick = 0  ; 
static uint8_t KeyPadDelay , LCD_Delay ;
uint8_t  KeyPad_PendingStart , LCD_PendingStart ;


TIMInit_t TIM_Handler ={.Instance = TIM1 , .TIM_Interrupt = TIM_1_IT_OVER,.COMPConfig.TIM16Bit.CompNum = COMP_A_ , .COMPConfig.TIM16Bit.CompAction = TIM_COMP_PIN_OUT_Normal ,.COMPConfig.TIM16Bit.CompValue = 16000 , .TIMMode = TIM_MODE_COMP_PWM_FAST ,.TimPreScaler = TIM_1_Prescaler_1};
EXIT_Handler_t  EXIT_Handler = {.EXTI_EDGE_DETECTION = EXTI_EDGE_RISING_EDGE , .EXTI_NUM = EXTI_NUM_2 };
	
	
	
static void TIM_callbackfunction(void);



void APP_Init(void)
{

	KeyPad_Initialization(&KeyPad);
	TIM_NormalModeInit(&TIM_Handler);
	_TIM_IT_EN(TIM_1_IT_OVER);
	TIM_Start(&TIM_Handler);
	TIM_CallBack_FuctionSet( TIM_1_IT_OVER ,  TIM_callbackfunction);

	Queue_Handler = QueueInitialize(20);
	TIM_Start(&TIM_Handler);
	sei();
		LCD_Initializaion();
		LCD_Send_Integer_CurrLoc(1567) ;
		LCD_Send_String_CurrLoc("welcome") ;
		_delay_ms(1000);
		while( LCD_Send_Command(LCD_COMMANED_CLEAR_LCD) == LCD_BUSY ) ;

}



void APP_Update(void)
{
	uint8_t Key = KeyPad_NONBlock_GetPressedKey(&KeyPad);
	while(LCD_Send_Command(LCD_COMMANED_CLEAR_LCD)== LCD_BUSY );
	LCD_Send_Character_CurrLoc(Key);	
}



void TIM_callbackfunction(void)
{

static uint8_t QueueCondition = 0 ; 


	if (KeyPad_PendingStart == 1)
	{
		KeyPadDelay++ ;
		if (KeyPadDelay == 20)
		{
			KeyPad_PendingStart = 0 ;
			KeyPadDelay = 0 ;
			TimerEvent = 1 ;
		}
	}
	
	
	if (LCD_PendingStart == 1)
	{				
		LCD_Delay++ ;
		if (LCD_Delay == 1)
		{
			LCD_PendingStart = 0 ; 
			LCD_Delay = 0 ; 
			LCD_PendingStat  = 0 ; 
			if((QueueCondition == 0)&&DeQueue(Queue_Handler , &TempData))
			{
				QueueCondition = 1 ;					
			}
	
			
			
			if(LCD_Send_4BitData(TempData) == 0 )
			LCD_PendingStart = 1 ;
				
			else
			if (DeQueue(Queue_Handler , &TempData))
			LCD_PendingStart = 1 ;
			else
			QueueCondition = 0 ;
			}
	}
}


ISR(TIMER1_OVF_vect)
{
	TIM_callbackfunction();
	TCNT1 =65535 - TIM_Handler.COMPConfig.TIM16Bit.CompValue ;
}

