/*
 * APP.c
 *
 * Created: 1/23/2022 6:21:30 PM
 *  Author: Ahmed_Ayman
 */ 


#include "APP.h"



#define		SELECT_OPERATION_MODE_BUTTON			0x01u 
#define     LCD_Print_Dragons						11
#define     LCD_Print_ATM_System					12

uint16_t Max_Temp = 0 ;
extern uint8_t   const LCD_StrF[11][20] ;



int usart_putchar_printf(char var, FILE *stream) ;
int _read(int fd, char* ptr, int len) ;
static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);

	



void Tim_1_CallBAck(void);
void INT0_CALLBACK(void);
void ATM_Check_Temp(void);
void ATM_Buttons_GPIO_Init(void);




EXIT_Handler_t	EXIT_Handler = {.EXTI_EDGE_DETECTION = EXTI_EDGE_LOW_LENEL , .EXTI_NUM = EXTI_NUM_0 };
	
	
	
	
	
	
I2C_Handler_t   I2C_Handler = {	.Init.I2C_Clk_Speed  =100000  ,.Init.I2C_IT_MODE = I2C_IT_DIS , .Init.I2C_SlaveADD = 0xaa, 
								.buffer = NULL   ,.BufferSize = I2C_Buffer_SIZE };





SPI_Handler_t SPI_Handler = {	.strSPI_Init.CLKPhase = SPI_CLK_SAMPLE_FIRST_EDGE ,.strSPI_Init.CLKPolarity = SPI_CLKPolarity_IDLE_LOW ,
								.strSPI_Init.CLKPrescaler = SPI_CLKPrescaler_128 , .strSPI_Init.FirstBit = SPI_FirstBit_MSB , 
								.strSPI_Init.IT_EN  = SPI_IT_MODE_DISABLE ,.strSPI_Init.Mode = SPI_MODE_SLAVE ,
								.RxBuffer = NULL ,.RxBufferSize =  SPI_RXBuffer_SIZE,.TxBuffer =NULL ,
								.TxBufferSize =  SPI_TXBuffer_SIZE}; 
								 
								 
								 
								 
								 
UART_Handler_t  UART_Handler = {.Init.BaudRate = 57600 ,.Init.Mode = UART_MODE_TX_RX , .Init.Parity = UART_Parity_No ,
								.Init.StopBits = UART_Stop_1 , .Init.wordLen = UART_WordLen_8 ,.RxBuffer = NULL ,
								.RxSize  = UART_RXBuffer_SIZE ,.TxBuffer = NULL ,.TxSize  = UART_TXBuffer_SIZE}; 
								
								
								
								
ButtonConfig_t ATM_Buttons[2] ={[0].PINNum = ATM_Card_Insert_Button_Pin ,[0].PORT = ATM_Card_Insert_Button_Port,
								[1].PINNum = ATM_FORCE_MODE_Button_Pin , [1].PORT = ATM_FORCE_MODE_Button_Port  };



TIMInit_t  Tim_1_Handler ={	.Instance = TIM1 , .TIM_Interrupt = TIM_1_IT_OVER ,.COMPConfig.TIM16Bit.CompAction = TIM_COMP_PIN_OUT_Normal   ,.TimPreScaler = TIM_1_Prescaler_256,.TIMMode = TIM_MODE_NORMAL  };
								 
								 
ADC_Handler_t ADC_Handler = {	.ADC_Intrrupet_Select = ADC_INIT_ENABLE ,.ADC_PreScaler = ADC_Presaler_2 ,
								.ADC_TRIG_SOURCE =ADC_TRIG_TIM1_OV ,.ADC_Vref_Select = ADC_Vref_AVCC,
								.ADC_Adjust_Select = ADC_Adjust_Right };
								 
	uint8_t strMax_Temp[ADMIN_TEMP_LEN] ; 								 
								 
void APP_Init(void)
{
	
	Motor_Init();				
	Motor_Start();
	KeyPad_Initialization(&KeyPad);
	LCD_Initializaion();	
	I2C_Init(&I2C_Handler);
	EEPROM_Init();
	HAL_SPI_Init(&SPI_Handler);
	HAL_UART_Init(&UART_Handler);
	ATM_Buttons_GPIO_Init();	
	TIM_NormalModeInit(&Tim_1_Handler);
	TIM_CallBack_FuctionSet(TIM_1_IT_OVER , Tim_1_CallBAck);
	ADC_Init(&ADC_Handler);
	cli();
	_TIM_IT_EN( TIM_1_IT_OVER);
	ADC_Get_Value_IT(&ADC_Handler,ADC_CH_0);
	SERVER_ADMIN_Get_Temp(strMax_Temp);
	Max_Temp = atoi((char *)strMax_Temp);
	if (Max_Temp == -1)
	{
		Max_Temp = 50 ;		// default value 
	}
	stdout = &mystdout; //Required for printf init

}



uint8_t App_Get_Command(void)
{
	uint8_t Password[ADMIN_PASSWARD_LEN] = {0} , StrName[ADMIN_USERNAME_LEN] = {0} ;
	uint8_t Command[ADMIN_USERNAME_LEN] = {0};	
		
	#if (SELECT_OPERATION_MODE_BUTTON == 1)
	
	if(Button_Read(ATM_Buttons , ATM_SELECT_MODE_Button_INDEX) == State_LOW)
	{
		#else
				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR("******** Please Enter Command choice ***************\n" ));
				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR(" \n" ));
		do
		{
			ATM_Terminal_GetString(Command , 10);
			if  ((strcmp((char *)Command , (char *)"ADMIN") == 0)||(strcmp((char *)Command , (char *)"OPERATE") == 0))
			{
				break ;
			}else
			{
				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR("******** Wrong Command Please Try again ************\n" ));
				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR(" \n" ));
			}
		} while (1);
		
		if(strcmp((char *)Command , (char *)"ADMIN") == 0 )
		{
			#endif
			SERVER_ADMIN_Get_Pass(StrName ,Password);
			printf("Welcome ADMIN :,%s \n\n" , StrName);
			printf_P(PSTR("****************************************************\n"	));
			printf_P(PSTR("*********** Enter Your Password :  *****************\n" ));
			printf_P(PSTR("****************************************************\n"	));
			printf_P(PSTR(" \n" ));
			memset(Command , 0 , ADMIN_USERNAME_LEN);
			ATM_Terminal_GetString(Command , ADMIN_USERNAME_LEN);
			while(strcmp((char *)Password , (char *)Command) != 0 )
			{

				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR("***************** Wrong Password !!! ***************\n" ));
				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR(" \n" ));
				ATM_Terminal_GetString(Command , 10);
			}

				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR("******** Switching to programming mode  ***********\n" ));
				printf_P(PSTR("****************************************************\n"	));
				printf_P(PSTR(" \n" ));
			
			return 1 ;
			
		}else{

			// after exiting programming mode we will enter operation mode directly	

			printf_P(PSTR("****************************************************\n"	));
			printf_P(PSTR("********** Switching to OPERATION mode *************\n" ));
			printf_P(PSTR("****************************************************\n"	));
			printf_P(PSTR(" \n" ));
			return 0 ; 
		}
	
	
	
	
}




void APP_UPdate(void)
{
	uint8_t Flag = 0 ;
	LCD_Send_String_WithLoc(1,1,Print_F(LCD_StrF[LCD_Print_Dragons]));
	LCD_Send_String_WithLoc(2,1,Print_F(LCD_StrF[LCD_Print_ATM_System]));
	printf_P(PSTR("****************************************************\n"	));
	printf_P(PSTR("*****************  "));
	printf_P((char *)LCD_StrF[LCD_Print_Dragons]);
	printf_P(PSTR(" ******************\n" ));
	printf_P(PSTR("******************  "));
	printf_P((char *)LCD_StrF[LCD_Print_ATM_System]);
	printf_P(PSTR(" ****************\n" ));	
	printf_P(PSTR("****************************************************\n"	));
	printf_P(PSTR(" \n" ));


	
	_delay_ms(ATM_DLEAY_IN_S);
	LCD_Send_Command(LCD_COMMANED_CLEAR_LCD);
	LCD_Send_String_WithLoc(1,5,(uint8_t *)"welcome ");	
	printf_P(PSTR("****************************************************\n"	));
	printf_P(PSTR("************************ welcome *******************\n" ));
	printf_P(PSTR("****************************************************\n"	));
	printf_P(PSTR(" \n" ));

	_delay_ms(ATM_DLEAY_IN_S);
	LCD_Send_Command(LCD_COMMANED_CLEAR_LCD);	
	
	Flag = App_Get_Command();
	if (Flag == 1)
	{
		ATM_Programming_mode();
	}
	
		while(1)
		{
			

			sei();		
			TIM_Start(&Tim_1_Handler);			// Enable ADC To Periodically check Temp 
			if(SERVER_ADMIN_Error_Get() == 0)
			{
				ATM_Operation_mode();	// New We can Switch to user Mode 
			}else
			{
				ATM_Lock_Fun();
			}
		}
		
		

}



void ATM_Buttons_GPIO_Init(void)
{
	GPIO_InitTypeDef RequestData ={.mode = GPIO_MODE_OUTPUT , .pin = ATM_Request_Card_DATA_Pin ,.pull = GPIO_PULLUP  };
	HAL_GPIO_Pin_Init(ATM_Request_Card_DATA_Port , &RequestData);
	RequestData.pin = GPIO_PIN_3 ;
	HAL_GPIO_Pin_Init(GPIOD , &RequestData);
		
	
	Button_Init(ATM_Buttons);
		
}




void INT0_CALLBACK(void)
{
	
	
	
	
	
}





int usart_putchar_printf(char var, FILE *stream) {
	uint8_t TempVar = var , Tempr = '\r';
    if (var == '\n') HAL_UART_TRANSMIT(&UART_Handler , &Tempr ,1);
	HAL_UART_TRANSMIT(&UART_Handler , &TempVar ,1);

    return 0;
}





void Tim_1_CallBAck(void)
{
	
	
	
	
}

ISR(TIMER1_OVF_vect)
{
}