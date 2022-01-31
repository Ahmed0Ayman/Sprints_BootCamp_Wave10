/******************************************************************************
 *
 * [MODULE]: APPLICATION
 *
 * [FILE NAME]: App.c
 *
 * [DESCRIPTION]: Source file for the Application
 *
 * [AUTHOR]: Ahmed Hassan
 *
 *******************************************************************************/

#include "App.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

uint8_t gu8_UserChoice[10];
uint8_t gStr8_message[10];
uint8_t gbuffer8_Data_NotReady[DATA_SIZE] = "NOT READY";
uint8_t gu8_systemStatus;
uint8_t gu8_sendStatus = FALSE;
uint8_t count;
uint8_t buff_index;

STR_cardData_t cardData;		/* Primary card data that taken form user */
STR_cardData_t DataSent;		/*The card data that set to the control MCU */
EXIT_Handler_t	EXIT_Handler = {.EXTI_EDGE_DETECTION = EXTI_EDGE_RISING_EDGE , .EXTI_NUM = EXTI_NUM_0 };

/*******************************************************************************
 *                           Interrupt service routine                         *
 *******************************************************************************/


void INT0_CALLBACK(void)
{
	if(gu8_sendStatus == TRUE)
	{
		for(count = 0; count < DATA_SIZE; count++)
		{
			SPI_sendByte(*((uint8_t *)&cardData + count));
		}
	}
	else
	{
		for(buff_index = 0; buff_index < DATA_SIZE; buff_index++)
		{
			SPI_sendByte(gbuffer8_Data_NotReady[buff_index]);
		}
	}
}

/*******************************************************************************
 *                           Functions Definitions                             *
 *******************************************************************************/

/*******************************************************************************
 * [Function Name]: App_init
 *
 * [Description]: 	Function to Initialize the application to test eeprom driver
 *
 * [Args]:			None
 *
 * [in]			  	None
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       None
 *******************************************************************************/
void App_init(void)
{
	SREG |= (1<<7);		/* Enable interrupts by setting I-bit */

	UART_ConfigType uart_config = {BPS_9600, NORMAL_SPEED, EIGHT_BITS, DISABLED, ONE_BIT};
	UART_init(&uart_config);

	EXTI_Init(&EXIT_Handler);
	EXIT_INT0_CallBack(INT0_CALLBACK);

	EEPROM_init();	/* Initialize the external EEPROM */

	/* Store byte in eeprom to check that first time to login */
	EEPROM_readByte(ADDRESS_SYSTEM_STATUS ,&gu8_systemStatus);

	SPI_initMaster();

	UART_sendString("WELCOME TO ATM BANKING SYSTEM\r\r");	/* Receive string from terminal */
}

/*******************************************************************************
 * [Function Name]: App_Update
 *
 * [Description]: 	Function to update the state of the application
 *
 * [Args]:			None
 *
 * [in]			  	None
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       None
 *******************************************************************************/
void App_Update(void)
{
	uint8_t User_choice;

	UART_sendString("Choose between two modes:\r");			/* Receive string from terminal */
	UART_sendString("ADMIN\r");
	UART_sendString("NORMAL\r\r");

	UART_receiveString(gu8_UserChoice);

	if(strcmp(gu8_UserChoice, "ADMIN") == IDENTICAL)
	{
		/* handle admin mode*/
		/* take NAME, PAN, PIN from terminal */
		UART_sendString("Welcome to the ADMIN Mode\r\r");
		UART_sendString("Please enter your choice: \r");
		UART_sendString("1. ADD\r2. MODFIY\r3. REMOVE\r\r");
		User_choice = UART_recieveByte();
		UART_sendByte('\r');

		switch(User_choice)
		{
		case '1': /* Add card */
			APP_AddCard();
			UART_sendString("\rAdding Card succeeded !!!\r\r");
			break;
		case '2': /* MODIFY card */
			APP_ModifyCard();
			break;
		case '3': /* REMOVE */
			APP_RemoveCard();
			break;
		default: /* NOT a valid choice */
			UART_sendString("Please enter valid choice !!!");
			break;
		}
	}
	else if(strcmp(gu8_UserChoice, "NORMAL") == IDENTICAL)
	{
		/* handle normal mode*/
		/* Check for the first byte in eeprom */
		/* welcome message */
		/* ready to make transaction on the card with the control MCU */
		if(gu8_systemStatus != EMPTY_EEPROM)
		{
			APP_NormalMode();
			/* Be ready to communicate with the Control MCU */
			while(1);
		}
		else
		{
			UART_sendString("Please enter your data first !!!\r\r");
		}
	}
	else
	{
		/* Please enter a valid choice */
		UART_sendString("\rPlease enter a valid choice !!!\r\r");
	}
}

/*******************************************************************************
 *                           Functions Declaration                             *
 *******************************************************************************/
void APP_receiveData(void)
{
	uint8_t count;

	for(count = 0; count < 10 ;count++)
	{
		EEPROM_readByte((ADDRESS_NAME_STORED | count), &cardData.au8_CardHolderName[count]);
		_delay_ms(50);
	}

	for(count = 0; count < 10  ;count++)
	{
		EEPROM_readByte((ADDRESS_PAN_STORED | count), &cardData.au8_PAN[count]);
		_delay_ms(50);
	}

	for(count = 0; count < 5  ;count++)
	{
		EEPROM_readByte((ADDRESS_PIN_STORED | count), &cardData.au8_PIN[count]);
		_delay_ms(50);
	}
}

/****************************************************************************************/
void APP_NormalMode(void)
{
	uint8_t count;

	APP_receiveData();

	UART_sendString("Welcome to the NORMAL Mode\r\r");

	for(count = 0; cardData.au8_CardHolderName[count] != '\0' ;count++)
	{
		EEPROM_readByte((ADDRESS_NAME_STORED | count), &DataSent.au8_CardHolderName[count]);
		_delay_ms(50);
	}
	EEPROM_readByte((ADDRESS_NAME_STORED | count), &DataSent.au8_CardHolderName[count]);
	_delay_ms(50);

	for(count = 0; cardData.au8_PAN[count] != '\0' ;count++)
	{
		EEPROM_readByte((ADDRESS_PAN_STORED | count), &DataSent.au8_PAN[count]);
		_delay_ms(50);
	}
	EEPROM_readByte((ADDRESS_PAN_STORED | count), &DataSent.au8_PAN[count]);
	_delay_ms(50);

	for(count = 0; cardData.au8_PIN[count] != '\0' ;count++)
	{
		EEPROM_readByte((ADDRESS_PIN_STORED | count), &DataSent.au8_PIN[count]);
		_delay_ms(50);
	}
	EEPROM_readByte((ADDRESS_PIN_STORED | count), &DataSent.au8_PIN[count]);
	_delay_ms(50);

	gu8_sendStatus = TRUE;
}

/****************************************************************************************/

void APP_AddCard(void)
{
	uint8_t count;

	/* FIRST CHOICE: ADD */
	UART_sendString("Please enter your NAME: ");
	UART_receiveString(cardData.au8_CardHolderName);

	for(count = 0; cardData.au8_CardHolderName[count] != '\0' ;count++)
	{
		EEPROM_writeByte((ADDRESS_NAME_STORED | count), cardData.au8_CardHolderName[count]);
		_delay_ms(50);
	}
	EEPROM_writeByte((ADDRESS_NAME_STORED | count), cardData.au8_CardHolderName[count]);
	_delay_ms(50);

	/* PAN */
	UART_sendString("Please enter your PAN: ");
	UART_receiveString(cardData.au8_PAN);

	for(count = 0; cardData.au8_PAN[count] != '\0' ;count++)
	{
		EEPROM_writeByte((ADDRESS_PAN_STORED | count), cardData.au8_PAN[count]);
		_delay_ms(50);
	}
	EEPROM_writeByte((ADDRESS_PAN_STORED | count), cardData.au8_PAN[count]);
	_delay_ms(50);

	/* PIN */
	UART_sendString("Please enter your PIN: ");
	UART_receiveString(cardData.au8_PIN);

	for(count = 0; cardData.au8_PIN[count] != '\0' ;count++)
	{
		EEPROM_writeByte((ADDRESS_PIN_STORED | count), cardData.au8_PIN[count]);
		_delay_ms(50);
	}
	EEPROM_writeByte((ADDRESS_PIN_STORED | count), cardData.au8_PIN[count]);
	_delay_ms(50);

	APP_CheckSystem_Status();
}
/****************************************************************************************/

void APP_CheckSystem_Status(void)
{
	/* modify the first byte in eeprom to indicate that this is the second time to login */
	if(gu8_systemStatus == EMPTY_EEPROM)
	{
		gu8_systemStatus = ANY_TIME_TO_LOG_IN;
		EEPROM_writeByte(ADDRESS_SYSTEM_STATUS, gu8_systemStatus);
		_delay_ms(50);
	}
}

/****************************************************************************************/
void APP_ModifyCard(void)
{
	if(gu8_systemStatus != EMPTY_EEPROM)
	{
		/* modify data */
		APP_AddCard();
		UART_sendString("\rModifying Card succeeded !!!\r\r");
	}
	else
	{
		/* you are a dummy user */
		UART_sendString("Please enter your data first !!!\r\r");
	}
}

/****************************************************************************************/
void APP_RemoveCard(void)
{
	uint16_t count;

	if(gu8_systemStatus != EMPTY_EEPROM)
	{
		UART_sendString("Wait until data is removing....\r\r");
		for(count = ADDRESS_SYSTEM_STATUS; count <= ADDRESS_PIN_STORED + 5 ;count++)
		{
			EEPROM_writeByte(count, EMPTY_EEPROM);
			_delay_ms(50);
		}
		UART_sendString("Removing Card succeeded !!!\r\r");
	}
	else
	{
		/* you are a dummy user */
		UART_sendString("Please enter your data first !!!\r\r");
	}
}

