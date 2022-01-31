/*
 * HAL_UART.c
 *
 * Created: 5/10/2021 9:38:56 AM
 *  Author: Ahmed_Ayman
 */ 

#include "HAL_UART.h"



/*
 * brief : this function used to initialization  UART peripheral 
 * param : Handler pointer to the struct hold UART configuration 
 * return : void 
 */
void HAL_UART_Init(UART_Handler_t * Handler )
{
	uint16_t BaudRateCal =0 ;
	
	UCSRB = 0x00 ;
	UCSRC = (1 << URSEL) | 0x00 ;    /* clear UCSRC register to set a new configurations */
	UCSRB |= Handler->Init.Mode ;   /* enable uart in tx or rx or both */

	/* set the word size and parity and stop bits */
	UCSRC  |= (1 << URSEL) |((Handler->Init.wordLen) & (0x06)) | (Handler->Init.StopBits);

	

	/* now set the baud rate */
	BaudRateCal = (F_CPU/(16ul *Handler->Init.BaudRate))-1;
	UBRRL = BaudRateCal ;
	UBRRH =(BaudRateCal>>8)&(0x0f);

	
	DDRD  |= 0x02 ;
	DDRD  &= ~(1<<0);
	
	
	
}/* END_FUN HAL_UART_Init() */






/*
 * brief : this function used to send data in blocking mode
 * param : Handler pointer to the struct hold UART configuration 
 * param : TxBuffer pointer to the transmitted buffer 
 * param : Size hold the size of transmitted data 
 * return : void 
 */
void HAL_UART_TRANSMIT(UART_Handler_t * Handler ,uint8_t * TxBuffer ,uint16_t Size )
{
	Handler->RxBuffer = 0;
	Handler->RxSize =0 ;
	Handler->TxBuffer = TxBuffer ;
	Handler->TxSize = Size ;
	
	for (uint16_t iterator =0 ;iterator<Handler->TxSize;iterator++)
	{
	   while(!(UCSRA &(1<<UDRE)));
	   	if(Handler->Init.wordLen == UART_WordLen_9)
		   {
			  UCSRB |=((0x100)&(Handler->TxBuffer[iterator]))>>8|0x01; 
		   }
			UDR =(TxBuffer[iterator]);

	}
	
	
	
}/* END_FUN HAL_UART_TRANSMIT() */






/*
 * brief : this function used to receive data in blocking mode 
 * param : Handler pointer to the struct hold UART configuration 
 * param : RxBuffer pointer to the Received buffer 
 * param : Size hold the size of transmitted data 
 * return : void 
 */
void HAL_UART_RECEIVE(UART_Handler_t * Handler ,uint8_t * RxBuffer ,uint16_t Size )
{
	
	Handler->TxBuffer = NULL;
	Handler->TxSize =0 ;
	Handler->RxBuffer = RxBuffer ;
	Handler->RxSize = Size ;
	
	
	for (uint16_t iterator =0 ;iterator<Handler->RxSize;iterator++)
	{
		while(!(UCSRA & (1<<RXC)));
		if(Handler->Init.wordLen == UART_WordLen_9)
		{
					*(((uint16_t *)Handler->RxBuffer)+iterator)  = (((uint16_t)UCSRB & 0x02)<<7) ;     /* the ninth bit must be read first */
					*(((uint16_t *)Handler->RxBuffer)+iterator) |= UDR ;
		}else{
			
		Handler->RxBuffer[iterator] = UDR ;
		}
	
	}
	
	
}/* END_FUN HAL_UART_RECEIVE() */




/*
 * brief : this function used to send data to the slave node in multi processor mode 
 * param : Handler pointer to the struct hold UART configuration 
 * param : TxBuffer pointer to the transmitted buffer 
 * param : Size hold the size of transmitted data 
 * param : Addr hold the address of the slave node 
 * return : void 
 */
void HAL_UART_MltiProcessor_TX(UART_Handler_t * Handler ,uint8_t * TxBuffer ,uint16_t Size,uint16_t Addr )
{
	
	Handler->RxBuffer = 0;
	Handler->RxSize =0 ;
	Handler->TxBuffer = TxBuffer ;
	Handler->TxSize = Size ;
	
		/* first we send the slave Addr  */
		while(!(UCSRA &(1<<UDRE)));
		if(Handler->Init.wordLen == UART_WordLen_9)     /* if use 9 bit configuration */
		{
			UCSRB |=(0x01);			/* set as one to remark as address byte */
			UDR = 0x0f & Addr ;	  
			
		}else{       /* if use 8 bit configuration */
			
			UDR = 0x80 | (0x0f & Addr) ;	   
		}
		
		
	/* now we will send the slave data in blocking mode */ 
	for (uint16_t iterator =0 ;iterator<Handler->TxSize;iterator++)
	{
		while(!(UCSRA &(1<<UDRE)));
		if(Handler->Init.wordLen == UART_WordLen_9)
		{
			UCSRB |=((0x100)&(Handler->TxBuffer[iterator]))>>8|0x01;
		}
		UDR =(TxBuffer[iterator]);

	}
	
		
	
	
}/* END_FUN HAL_UART_MltiProcessor_TX() */







/*
 * brief : this function used to receive data from  the master node in multi processor mode 
 * param : Handler pointer to the struct hold UART configuration 
 * param : RxBuffer pointer to the transmitted buffer 
 * param : Size hold the size of transmitted data 
 * param : Addr hold the address of the slave node 
 * return : void 
 */
void HAL_UART_MltiProcessor_RX(UART_Handler_t * Handler ,uint8_t * RxBuffer ,uint16_t Size,uint16_t Addr )
{

	uint16_t ReceivedAddr = 0 ;

	Handler->TxBuffer = NULL;
	Handler->TxSize =0 ;
	Handler->RxBuffer = RxBuffer ;
	Handler->RxSize = Size ;

	UCSRA |= 0x01 ;		/* set multi processor  mode */


		while(!(UCSRA & (1<<RXC)));			/* wait until receive data */
		if(Handler->Init.wordLen == UART_WordLen_9)
		{
			ReceivedAddr  = (((uint16_t)UCSRB & 0x02)<<7) ;     /* the ninth bit must be read first */
			ReceivedAddr  |= UDR ;
			}else{
			
			ReceivedAddr = UDR ;
		}
		
		if((ReceivedAddr & 0x0f) == (Addr & 0x0f))
		{
			
			UCSRA &= ~(0x01);   /* clear the Multi processor mode and return to normal mode */
			for (uint16_t iterator =0 ;iterator<Handler->RxSize;iterator++)
			{
				while(!(UCSRA & (1<<RXC)));
				if(Handler->Init.wordLen == UART_WordLen_9)
				{
					*(((uint16_t *)Handler->RxBuffer)+iterator) = (((uint16_t)UCSRB & 0x02)<<7) ;     /* the ninth bit must be read first */
					*(((uint16_t *)Handler->RxBuffer)+iterator) |= UDR ;
	
				}else
				{
			
					Handler->RxBuffer[iterator] = UDR ;
				}
				
		
			}/* END_OF for (uint16_t iterator =0 ;iterator<Handler->RxSize;iterator++) */	
	
	
	
		}/* END_OF if((ReceivedAddr & 0x0f) == (Addr & 0x0f))  */
		
		
		
		
		
	
}/* END_FUN HAL_UART_MltiProcessor_RX() */