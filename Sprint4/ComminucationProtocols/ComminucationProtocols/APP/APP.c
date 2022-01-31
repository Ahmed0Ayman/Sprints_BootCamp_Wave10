/*
 * APP.c
 *
 * Created: 1/23/2022 6:21:30 PM
 *  Author: Ahmed_Ayman
 */ 


#include "APP.h"



uint8_t KeypadKey[2] ;
uint8_t ControlFlag ;


#define I2C_Buffer_SIZE					0x0fu
#define SPI_RXBuffer_SIZE				0x0fu
#define SPI_TXBuffer_SIZE				0x0fu
#define UART_RXBuffer_SIZE				0x0fu
#define UART_TXBuffer_SIZE				0x0fu


uint8_t UART_TXBuffer[ UART_TXBuffer_SIZE]	= "welcomeMCU1\n";
uint8_t UART_RXBuffer[ UART_RXBuffer_SIZE]	;
uint8_t SPI_TXBuffer[SPI_TXBuffer_SIZE]		= "welcomeMCU1\n";
uint8_t SPI_RXBuffer[SPI_RXBuffer_SIZE]		;
uint8_t I2C_Buffer[I2C_Buffer_SIZE]			= "welcomeMCU1\n";



static void Uart_Transmit_Only(void);
static void SPI_Transmit_Only(void);
static void I2C_Transmit_Only(void);
static void ALL_Transmit_Only(void);
static void Uart_ECHO_Only(void);
static void EEPROM_Read_Only(void);
static void EEPROM_Write_Only(void);




EXIT_Handler_t	EXIT_Handler = {.EXTI_EDGE_DETECTION = EXTI_EDGE_LOW_LENEL , .EXTI_NUM = EXTI_NUM_0 };
	
	
	
I2C_Handler_t   I2C_Handler = {	.Init.I2C_Clk_Speed  =100000  ,.Init.I2C_IT_MODE = I2C_IT_DIS , .Init.I2C_SlaveADD = 0xaa, 
								.buffer = I2C_Buffer   ,.BufferSize = I2C_Buffer_SIZE };



SPI_Handler_t SPI_Handler = {	.strSPI_Init.CLKPhase = SPI_CLK_SAMPLE_FIRST_EDGE ,.strSPI_Init.CLKPolarity = SPI_CLKPolarity_IDLE_LOW ,
								.strSPI_Init.CLKPrescaler = SPI_CLKPrescaler_128 , .strSPI_Init.FirstBit = SPI_FirstBit_MSB , 
								.strSPI_Init.IT_EN  = SPI_IT_MODE_DISABLE ,.strSPI_Init.Mode = SPI_MODE_MASTER ,
								.RxBuffer = SPI_RXBuffer ,.RxBufferSize =  SPI_RXBuffer_SIZE,.TxBuffer =SPI_TXBuffer ,
								.TxBufferSize =  SPI_TXBuffer_SIZE}; 
								 
								 
								 
UART_Handler_t  UART_Handler = {.Init.BaudRate = 9600 ,.Init.Mode = UART_MODE_TX_RX , .Init.Parity = UART_Parity_No ,
								.Init.StopBits = UART_Stop_1 , .Init.wordLen = UART_WordLen_8 ,.RxBuffer = UART_RXBuffer ,
								.RxSize  = UART_RXBuffer_SIZE ,.TxBuffer = UART_TXBuffer ,.TxSize  = UART_TXBuffer_SIZE}; 
								
								

void APP_Init(void)
{
	KeyPad_Initialization(&KeyPad);
	LCD_Initializaion();
	EXTI_Init(&EXIT_Handler);
//	EXIT_INT0_CallBack()	
	//I2C_Init(&I2C_Handler);
	EEPROM_Init();
	HAL_SPI_Init(&SPI_Handler);
	HAL_UART_Init(&UART_Handler);
	sei();
}



void APP_UPdate(void)
{
			*KeypadKey = 0 ;
			while(!KeypadKey[0])
			KeypadKey[0] = KeyPad_GetPressedKey(&KeyPad);
			LCD_Send_Character_WithLoc(1,1,KeypadKey[0]);
			_delay_ms(100);

			ControlFlag  = atoi((char*)KeypadKey) ;
			LCD_Send_Integer_WithLoc(1,1,ControlFlag, 4);
			switch(ControlFlag)
			{

				case  1 :
						Uart_Transmit_Only();
					break;
				case  2 :
						SPI_Transmit_Only();
					break;
				case  3 :
						I2C_Transmit_Only();
					break;
				case 4 :
						ALL_Transmit_Only();			
					break;
				case 5 :
						Uart_ECHO_Only();
					break;
				case 6 :
						EEPROM_Read_Only();
					break; 
				case 7 :
						EEPROM_Write_Only();
					break;
				case 8 :
						EEPROM_Reset();
								ControlFlag  = 0  ;

								_delay_ms(100);
					break;
				case 9 :
				
				
					break;
				case 0 :
							/* wait action */
					break; 
				default:
				
				
				
					break;
				
				
				
				
			}
}








void Uart_Transmit_Only(void)
{
	uint8_t ExitKey = 0 ; 
	while(!ExitKey)
	{
		HAL_UART_TRANSMIT(&UART_Handler ,UART_TXBuffer ,  UART_RXBuffer_SIZE );
		ControlFlag  = 0  ;
		ExitKey = KeyPad_GetPressedKey(&KeyPad);
	}
	_delay_ms(100);
}

void SPI_Transmit_Only(void)
{

		HAL_UART_RECEIVE(&UART_Handler , SPI_RXBuffer , SPI_RXBuffer_SIZE);
		HAL_SPI_Transmit(&SPI_Handler , SPI_RXBuffer ,SPI_TXBuffer_SIZE );
		ControlFlag  = 0  ;

	_delay_ms(100);
}

void I2C_Transmit_Only(void)
{
	uint8_t ExitKey = 0 ;
	while(!ExitKey)
	{
		HAL_I2C_Mem_Write(&I2C_Handler , 0xaa ,5 ,1 ,I2C_Buffer ,I2C_Buffer_SIZE);
		ControlFlag  = 0  ;
		ExitKey = KeyPad_GetPressedKey(&KeyPad);
	}
	_delay_ms(100);
}

void ALL_Transmit_Only(void)
{
	uint8_t ExitKey = 0 ;
	while(!ExitKey)
	{
		HAL_UART_TRANSMIT(&UART_Handler ,UART_TXBuffer ,  UART_TXBuffer_SIZE );
		HAL_SPI_Transmit(&SPI_Handler , SPI_TXBuffer ,SPI_TXBuffer_SIZE );
		HAL_I2C_Mem_Write(&I2C_Handler , 0xaa ,5 , 1 ,I2C_Buffer ,I2C_Buffer_SIZE);
		ExitKey = KeyPad_GetPressedKey(&KeyPad);
	}
		ControlFlag  = 0  ;
		_delay_ms(100);
}

void Uart_ECHO_Only(void)
{
	uint8_t ExitKey = 0 ;
	while(!ExitKey)
	{
		HAL_UART_RECEIVE(&UART_Handler ,UART_RXBuffer ,  UART_RXBuffer_SIZE );
		HAL_UART_TRANSMIT(&UART_Handler ,UART_RXBuffer ,  UART_RXBuffer_SIZE );
		ExitKey = KeyPad_GetPressedKey(&KeyPad);
	}
		ControlFlag  = 0  ;
		_delay_ms(100);
}




void EEPROM_Write_Only(void)
{
	uint8_t ExitKey = 0 ;
	uint8_t TXByte[3] = "AH" ;
	while(!ExitKey)
	{
		EEPROM_WriteByteS(10,10,TXByte , 2);
		ExitKey = KeyPad_GetPressedKey(&KeyPad);
	}
	ControlFlag  = 0  ;
	_delay_ms(100);
}



void EEPROM_Read_Only(void)
{
	uint8_t ExitKey = 0 ;
	uint8_t RXByte[2] = {0} ;
	while(!ExitKey)
	{
		EEPROM_ReadByteS(10,10,RXByte , 2);
		ExitKey = KeyPad_GetPressedKey(&KeyPad);
	}
	ControlFlag  = 0  ;
	_delay_ms(100);
}

