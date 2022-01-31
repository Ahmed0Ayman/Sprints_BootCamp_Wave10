
/*
 * HAL_UART.h
 *
 * Created: 5/10/2021 9:39:10 AM
 *  Author: Ahmed_Ayman
 */ 



#ifndef __HAL_UART__
#define __HAL_UART__


#define  F_CPU 16000000   /* used by this library to calculate the baud rate */ 
 
 
 
 
#include <stdint.h>
#include <avr/io.h>


#define  NULL ((void * )0)

#define  UART_SYNC  0




#define UART_Parity_No                  0x00u
#define UART_Parity_Even                0x20u
#define UART_Parity_Odd                 0x30u




#define UART_WordLen_5                  0x00u
#define UART_WordLen_6                  0x02u
#define UART_WordLen_7                  0x04u
#define UART_WordLen_8                  0x06u
#define UART_WordLen_9                  0x16u 





#define UART_MODE_TX                     0x08u
#define UART_MODE_RX                     0x10u
#define UART_MODE_TX_RX                  0x18u



#define UART_Stop_1                      0x00u
#define UART_Stop_2                      0x08u




typedef struct 
{
	uint32_t BaudRate ;		/* set to desired baud rate */
	uint8_t wordLen ;		/* size of transmitted word must be one of UART_WordLen_  */
	uint8_t StopBits ;		/* number of stop bits must be one of UART_Stop_ */
	uint8_t Parity ;		/* parity must be one of UART_Parity_ */ 
	uint8_t Mode   ;        /* must be one of UART_MODE_ */
	
}UartInit_Typedef;





typedef enum 
{
	UART_OK ,
	UART_ERROR ,	
	UART_BUSY 
	
}UART_STATUS;




typedef struct  
{
	UartInit_Typedef Init ;    /* hold the main configurations for  UART */
	uint8_t * TxBuffer ;
	uint8_t * RxBuffer ;
	uint16_t TxSize ;
	uint16_t RxSize ; 	
	UART_STATUS Status ;
	
}UART_Handler_t;







/*
 * brief : this function used to initialization  UART peripheral 
 * param : Handler pointer to the struct hold UART configuration 
 * return : void 
 */
void HAL_UART_Init(UART_Handler_t * Handler );






/*
 * brief : this function used to send data in blocking mode
 * param : Handler pointer to the struct hold UART configuration 
 * param : TxBuffer pointer to the transmitted buffer 
 * param : Size hold the size of transmitted data 
 * return : void 
 */
void HAL_UART_TRANSMIT(UART_Handler_t* Handler ,uint8_t * TxBuffer ,uint16_t Size );








/*
 * brief : this function used to receive data  in blocking mode
 * param : Handler pointer to the struct hold UART configuration 
 * param : RxBuffer pointer to the Received buffer 
 * param : Size hold the size of transmitted data 
 * return : void 
 */
void HAL_UART_RECEIVE(UART_Handler_t* Handler ,uint8_t * RxBuffer ,uint16_t Size );








/*
 * brief : this function used to send data to the slave node in multi processor mode 
 * param : Handler pointer to the struct hold UART configuration 
 * param : TxBuffer pointer to the transmitted buffer 
 * param : Size hold the size of transmitted data 
 * param : Addr hold the address of the slave node 
 * return : void 
 */
void HAL_UART_MltiProcessor_TX(UART_Handler_t * Handler ,uint8_t * TxBuffer ,uint16_t Size,uint16_t Addr );







/*
 * brief : this function used to receive data from  the master node in multi processor mode 
 * param : Handler pointer to the struct hold UART configuration 
 * param : RxBuffer pointer to the transmitted buffer 
 * param : Size hold the size of transmitted data 
 * param : Addr hold the address of the slave node 
 * return : void 
 */
void HAL_UART_MltiProcessor_RX(UART_Handler_t * Handler ,uint8_t * RxBuffer ,uint16_t Size,uint16_t Addr );
















#endif