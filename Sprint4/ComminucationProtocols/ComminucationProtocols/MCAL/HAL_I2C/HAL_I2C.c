



#include "HAL_I2c.h"



#define  WAIT_FLAG()  while(!(I2C->I2C_TWCR & I2C_IT_FLAG))  

/*
 * brief  : this function used to initialize I2C peripheral  
 * param. : Handler pointer to struct hold all I2C configuration and parameters 
 * return : void  
 */
void I2C_Init(I2C_Handler_t * Handler)
{
	// INIT. i2c peripheral
	I2C->I2C_TWBR = ((((uint64_t)F_CPU)/(uint64_t)(Handler->Init.I2C_Clk_Speed))-16)/2;
	I2C->I2C_TWAR = Handler->Init.I2C_SlaveADD ;
	I2C->I2C_TWCR = 0x00 ;
	I2C->I2C_TWSR = 0x00 ;
	
	if(Handler->Init.I2C_IT_MODE == I2C_IT_EN)
	{
	sei();
	I2C->I2C_TWCR |=   I2C_IT_EN ;
	}else{
	I2C->I2C_TWCR &= ~ I2C_IT_EN ;	
	}
	
	
}/* END_FUN I2C_INIT_FUN() */





 
/*
 * brief  : this function used to send a block of buffer with determined size 
 * param. : Handler pointer to struct hold all I2C configuration and parameters
 * param. : DevAdd  hold  I2C slave address that you will start communication with
 * param. : PTxData pointer to buffer that hold all data bytes that you need to send
 * param. : DataSize used to determine the buffer size  
 * return : void  
 */
I2C_STATUS HAL_I2C_Master_Transmit(I2C_Handler_t * Handler,uint8_t DevAdd ,uint8_t * PTxData,uint8_t DataSize)
{

	Handler->buffer = PTxData ;
	Handler->BufferSize   = DataSize;
	
	I2C_EN_START();
	while((I2C->I2C_TWCR & I2C_IT_FLAG)==0);
	I2C->I2C_TWDR = DevAdd ;
	I2C_EN();WAIT_FLAG();
	while(Handler->BufferSize-- > 0)
	{
		I2C->I2C_TWDR = *(Handler->buffer) ;
		I2C_EN();WAIT_FLAG();
		Handler->buffer++;
	}
	I2C_EN_STOP();

	
	return I2C_NORMAL ;
}/* END_FUN I2C_MASTER_TRANSMIT() */






/*
 * brief   : this function used to transmit data in master receive mode
 * param.  : handler this handler of I2c peripheral 
 * param.  : DevAdd this is the address of the slave device that you want to communicate with
 * param.  : pTxData this is pointer to the buffer that will hold the transmitted data 
 * param.  : DataSize number of bytes that you need to read 
*/
 
I2C_STATUS HAL_I2C_Master_Receive(I2C_Handler_t * Handler ,uint8_t DevAdd  ,uint8_t * pTxData ,uint8_t DataSize )
{
	
	Handler->buffer = pTxData ;
	Handler->BufferSize   = DataSize;
	
	I2C_EN();WAIT_FLAG();
	I2C->I2C_TWDR =(( DevAdd )| 1);
	I2C_EN();WAIT_FLAG();
	while(Handler->BufferSize-- > 0)
	{
		I2C->I2C_TWDR = *(Handler->buffer) ;
		I2C_EN();WAIT_FLAG();
		Handler->buffer++;
		
	}
	I2C_EN_STOP();


	return I2C_NORMAL ;

}/* END_FUN I2C_MASTER_RECIEVE() */


/*
 * brief   : this function used to receive data in slave mode
 * param.  : handler this handler of I2c peripheral 
 * param.  : DevAdd this is the address of the slave device that you want to communicate with
 * param.  : pRxData this is pointer to the buffer that will hold the received data 
 * param.  : DataSize number of bytes that you need to receive 
*/ 
I2C_STATUS HAL_I2C_Slave_Receive(I2C_Handler_t * Handler  ,uint8_t * pRxData ,uint8_t DataSize )
{
	Handler->buffer = pRxData ;
	Handler->BufferSize   = DataSize;
	
	I2C_EN_ACK();WAIT_FLAG();
	while(Handler->BufferSize-- >0)       
	{
		I2C_EN_ACK();WAIT_FLAG()
		*(Handler->buffer) = I2C->I2C_TWDR ;
		if(Handler->BufferSize == 0)
		{
			break ;
		}		 Handler->buffer++;
	}
	I2C_EN_NACK() ;
	
	
		return I2C_NORMAL ;
}/* END_FUN I2C_SLAVE_RECEIVE() */




/*
 * brief   : this function used to transmit data in slave mode
 * param.  : handler this handler of I2c peripheral 
 * param.  : DevAdd this is the address of the slave device that you want to communicate with
 * param.  : pTxData this is pointer to the buffer that will hold the transmitted data 
 * param.  : DataSize number of bytes that you need to transmit 
*/
I2C_STATUS HAL_I2C_Slave_Transmit(I2C_Handler_t * Handler  ,uint8_t * pTxData,uint8_t DataSize )
{
		Handler->buffer = pTxData ;
		Handler->BufferSize   = DataSize;
		
		I2C_EN_ACK();WAIT_FLAG();
		while(Handler->BufferSize-- >0)
		{
			I2C_EN_ACK();WAIT_FLAG();
			I2C->I2C_TWDR = *(Handler->buffer);
			Handler->buffer++;
			if(Handler->BufferSize == 0)
			{
				break ;
			}
		}
		I2C_EN_NACK() ;
	
	
		return I2C_NORMAL ;
	
}/* END_FUN I2C_SLAVE_TRANSMIT() */




/*
 * brief  : this function used to handle all operation of dealing with reading from dev. memory 
 * param.  : handler this handler of I2c peripheral 
 * param.  : DevAdd this is the address of the slave device that you want to communicate with 
 * param.  : memAdd this is the internal memory address that you need to write data to 
 * param.  : pRxData this is pointer to the buffer that hold the writing data 
 * param.  : DataSize number of bytes that you need to write 
*/ 
I2C_STATUS HAL_I2C_Mem_Write(I2C_Handler_t * Handler ,uint8_t DevAdd,uint16_t MemAdd ,uint8_t MemAddSize ,uint8_t * pTxData ,uint8_t DataSize )
{
	Handler->buffer = pTxData ;
	Handler->BufferSize   = DataSize;
	
	I2C_EN_START();WAIT_FLAG();
	I2C->I2C_TWDR = DevAdd ;
	I2C_EN();WAIT_FLAG();

	if (MemAddSize == 2)
	{
		I2C->I2C_TWDR =( MemAdd>>8 & 0xff );
		I2C_EN();WAIT_FLAG();
	}
	I2C->I2C_TWDR =( MemAdd & 0xff );
	I2C_EN();WAIT_FLAG();

	while(DataSize-- > 0)
	{
		I2C->I2C_TWDR = *(Handler->buffer++) ;
		I2C_EN();WAIT_FLAG();

	}
	I2C_EN_STOP();

	return I2C_NORMAL ;
	
}/* END_FUN I2C_MEM_WRITE() */







/* 
 * brief   : this function used to handle all operation of dealing with memory 
 * param.  : handler this handler of I2c peripheral 
 * param.  : DevAdd this is the address of the slave device that you want to communicate with 
 * param.  : memAdd this is the internal memory address that you need to read data from it 
 * param.  : pRxData this is pointer to the buffer that will hold the reading data 
 * param.  : DataSize number of bytes that you need to read 
*/ 
I2C_STATUS HAL_I2C_Mem_Read(I2C_Handler_t * Handler ,uint8_t DevAdd,uint16_t MemAdd ,uint8_t MemAddSize ,uint8_t * pRxData ,uint8_t DataSize )
{
	Handler->buffer = pRxData ;
	Handler->BufferSize = DataSize;
	
	I2C_EN_START();WAIT_FLAG();
	I2C->I2C_TWDR = DevAdd ;
	I2C_EN();WAIT_FLAG();
	if (MemAddSize == 2)
	{
		I2C->I2C_TWDR =( MemAdd>>8 & 0xff );
		I2C_EN();WAIT_FLAG();
	}
	I2C->I2C_TWDR =( MemAdd & 0xff );
	I2C_EN();WAIT_FLAG();
	I2C_EN_START();WAIT_FLAG();
	I2C->I2C_TWDR = DevAdd | 1 ;
	I2C_EN();WAIT_FLAG();
	while(DataSize-- > 1)	
	{
		I2C_EN_ACK();WAIT_FLAG();
		*(Handler->buffer++) = I2C->I2C_TWDR ;
	}
	
	
	/* Last Byte Will received with NACK */
	I2C_EN();WAIT_FLAG();
	*(Handler->buffer++) = I2C->I2C_TWDR ;

	
	/* Send Stop Bit allow another Master to acquire the bus */
	I2C_EN_STOP();
	
	
	return I2C_NORMAL ;
} /* END_FUN I2C_MEM_READ() */


