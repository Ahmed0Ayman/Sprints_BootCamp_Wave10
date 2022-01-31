/******************************************************************************
 *
 * [MODULE]: DIO
 *
 * [FILE NAME]: dio.h
 *
 * [DESCRIPTION]: Source file for the DIO AVR driver
 *
 * [AUTHOR]: Ahmed Hassan
 *
 ******************************************************************************/

#include "dio.h"

/******************************************************************************
 *                          Functions Definitions   	                      *
 ******************************************************************************/

/******************************************************************************
 * [Function Name]: DIO_setPortDirection
 *
 * [Description]: 	Function to set the direction of all pins in the port (INPUT, OUTPUT)
 *
 * [Args]:			port_ID, port_Direction
 *
 * [in]			  	port_ID: Enumerator to DIO ID
 * 					port_Direction: Enumerator to DIO direction
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       Error state
 ******************************************************************************/
enuDIO_E_STATE_t DIO_setPortDirection(enuDIO_PortId_t enu_portID, enuDIO_DirectionType_t enu_portDirection)
{
	enuDIO_E_STATE_t enu_ErrorState = E_NOT_OK;

	/* Check if the PORT is input or output */
    if(enu_portDirection == HIGH)
    {
    	switch (enu_portID)
		{
		case DIO_PORTA:
			DDRA_DIR_R = OUTPUT_PORT;
			enu_ErrorState = DIO_E_PARAM_VALID;
			break;
		case DIO_PORTB:
			DDRB_DIR_R = OUTPUT_PORT;
			enu_ErrorState = DIO_E_PARAM_VALID;
			break;
		case DIO_PORTC:
			DDRC_DIR_R = OUTPUT_PORT;
			enu_ErrorState = DIO_E_PARAM_VALID;
			break;
		case DIO_PORTD:
			DDRD_DIR_R = OUTPUT_PORT;
			enu_ErrorState = DIO_E_PARAM_VALID;
			break;
		default:
			enu_ErrorState = DIO_E_PARAM_INVALID_PORT_ID;
			break;
		}
    }
    else if(enu_portDirection == LOW)
    {
		switch (enu_portID)
		{
		case DIO_PORTA:
			DDRA_DIR_R = INPUT_PORT;
			enu_ErrorState = DIO_E_PARAM_VALID;
			break;
		case DIO_PORTB:
			DDRB_DIR_R = INPUT_PORT;
			enu_ErrorState = DIO_E_PARAM_VALID;
			break;
		case DIO_PORTC:
			DDRC_DIR_R = INPUT_PORT;
			enu_ErrorState = DIO_E_PARAM_VALID;
			break;
		case DIO_PORTD:
			DDRD_DIR_R = INPUT_PORT;
			enu_ErrorState = DIO_E_PARAM_VALID;
			break;
		default:
			enu_ErrorState = DIO_E_PARAM_INVALID_PORT_ID;
			break;
		}
    }
    else
    {
    	enu_ErrorState = DIO_E_PARAM_INVALID_PORT_DIR;	/* Invalid port direction */
    }
    return enu_ErrorState;
}

/******************************************************************************
 * [Function Name]: DIO_setPinDirection
 *
 * [Description]: 	Function to set the direction of a certain pin in certain port
 *
 * [Args]:			port_ID, pin_ID, pin_Direction
 *
 * [in]			  	port_ID: Enumerator to DIO port ID
 * 					pin_ID: Enumerator to DIO pin ID
 * 					port_Direction: Enumerator to DIO pin direction
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       Error State
 ******************************************************************************/
enuDIO_E_STATE_t DIO_setPinDirection(enuDIO_PortId_t enu_portID , enuDIO_PinId_t enu_pinID,
								     enuDIO_DirectionType_t enu_pinDirection)
{
	enuDIO_E_STATE_t enu_ErrorState = E_NOT_OK;

	/* Check if the pin id is one of the existed pin or not */
	if ((enu_pinID >= PIN_0) && (enu_pinID <= PIN_7))
	{
		if (enu_pinDirection == OUTPUT)
		{
			switch (enu_portID)
			{
			case DIO_PORTA:
				SET_BIT(DDRA_DIR_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
			case DIO_PORTB:
				SET_BIT(DDRB_DIR_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
			case DIO_PORTC:
				SET_BIT(DDRC_DIR_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
			case DIO_PORTD:
				SET_BIT(DDRD_DIR_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
            default:
            	enu_ErrorState = DIO_E_PARAM_INVALID_PORT_ID;	/* Invalid port id */
                break;
			}
		}
		else if (enu_pinDirection == INPUT)
		{
			switch (enu_portID)
			{
			case DIO_PORTA:
				CLEAR_BIT(DDRA_DIR_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
			case DIO_PORTB:
				CLEAR_BIT(DDRB_DIR_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
			case DIO_PORTC:
				CLEAR_BIT(DDRC_DIR_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
			case DIO_PORTD:
				CLEAR_BIT(DDRD_DIR_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
            default:
            	enu_ErrorState = DIO_E_PARAM_INVALID_PORT_ID;	/* Invalid port id */
                break;
			}
		}
		else
		{
			enu_ErrorState = DIO_E_PARAM_INVALID_PORT_DIR;	/* Invalid port direction */
		}
	}
	else
	{
		enu_ErrorState = DIO_E_PARAM_INVALID_PIN_ID;	/* Invalid pin id */
	}
	return enu_ErrorState;
}

/******************************************************************************
 * [Function Name]: DIO_writePort
 *
 * [Description]: 	Function to write (HIGH, LOW) in a certain port
 *
 * [Args]:			port_ID, port_Value
 *
 * [in]			  	port_ID: Enumerator to DIO port ID
 *					port_Value: Unsigned character value to be written in the port
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       Error State
 ******************************************************************************/
enuDIO_E_STATE_t DIO_writePort(enuDIO_PortId_t enu_portID, uint8_t au8_portValue)
{
	enuDIO_E_STATE_t enu_ErrorState = E_NOT_OK;

    switch (enu_portID)
    {
    case DIO_PORTA:
        PORTA_DATA_R = au8_portValue;
        enu_ErrorState = DIO_E_PARAM_VALID;
        break;
    case DIO_PORTB:
        PORTB_DATA_R = au8_portValue;
        enu_ErrorState = DIO_E_PARAM_VALID;
        break;
    case DIO_PORTC:
        PORTC_DATA_R = au8_portValue;
        enu_ErrorState = DIO_E_PARAM_VALID;
        break;
    case DIO_PORTD:
        PORTD_DATA_R = au8_portValue;
        enu_ErrorState = DIO_E_PARAM_VALID;
        break;
    default:
    	enu_ErrorState = DIO_E_PARAM_INVALID_PORT_ID;	/* Invalid port id */
        break;
    }
    return enu_ErrorState;
}

/******************************************************************************
 * [Function Name]: DIO_writePin
 *
 * [Description]: 	Function to write (HIGH, LOW) in a certain pin in a certain port
 *
 * [Args]:			port_ID, pin_ID, pin_Value
 *
 * [in]			  	port_ID: Enumerator to DIO port ID
 *					pin_ID: Enumerator to DIO pin ID
 *					pin_Value: Unsigned character value to be written in the pin
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       Error State
 ******************************************************************************/
enuDIO_E_STATE_t DIO_writePin(enuDIO_PortId_t enu_portID, enuDIO_PinId_t enu_pinID, uint8_t au8_pinValue)
{
	enuDIO_E_STATE_t enu_ErrorState = E_NOT_OK;

	/* Check if the pin id is one of the existed pin or not */
	if ((enu_pinID >= PIN_0) && (enu_pinID <= PIN_7))
	{
		if (au8_pinValue == HIGH)
		{
			switch (enu_portID)
			{
			case DIO_PORTA:
				SET_BIT(PORTA_DATA_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
			case DIO_PORTB:
				SET_BIT(PORTB_DATA_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
			case DIO_PORTC:
				SET_BIT(PORTC_DATA_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
			case DIO_PORTD:
				SET_BIT(PORTD_DATA_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
            default:
            	enu_ErrorState = DIO_E_PARAM_INVALID_PORT_ID;	/* Invalid port id */
                break;
			}
		}
		else if (au8_pinValue == LOW)
		{
			switch (enu_portID)
			{
			case DIO_PORTA:
				CLEAR_BIT(PORTA_DATA_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
			case DIO_PORTB:
				CLEAR_BIT(PORTB_DATA_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
			case DIO_PORTC:
				CLEAR_BIT(PORTC_DATA_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
			case DIO_PORTD:
				CLEAR_BIT(PORTD_DATA_R, enu_pinID);
				enu_ErrorState = DIO_E_PARAM_VALID;
				break;
            default:
            	enu_ErrorState = DIO_E_PARAM_INVALID_PORT_ID;	/* Invalid port id */
                break;
			}
		}
		else
        {
			enu_ErrorState = DIO_E_PARAM_INVALID_PORT_DIR;	/* Invalid port direction */
		}
	}
	else
	{
		enu_ErrorState = DIO_E_PARAM_INVALID_PIN_ID;	/* Invalid pin id */
	}
	return enu_ErrorState;
}

/******************************************************************************
 * [Function Name]: DIO_readPort
 *
 * [Description]: 	Function to read the value in a certain port
 *
 * [Args]:			port_ID, port_State
 *
 * [in]			  	port_ID: Enumerator to DIO port ID
 *					port_State: Pointer to Unsigned character value to return the
 *								state of the port in it
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       Error State
 ******************************************************************************/
enuDIO_E_STATE_t DIO_readPort(enuDIO_PortId_t enu_portID, uint8_t * ptr_portState)
{
	enuDIO_E_STATE_t enu_ErrorState = E_NOT_OK;

	/* Check if the pointer is NULL pointer or not */
	if(ptr_portState == NULL_PTR)
    {
		enu_ErrorState = DIO_E_PARAM_POINTER;	/* Invalid pointer */
	}
	else
	{
		switch (enu_portID)
		{
		case DIO_PORTA:
			*ptr_portState = PINA_INPUT_R;
			enu_ErrorState = DIO_E_PARAM_VALID;
			break;
		case DIO_PORTB:
			*ptr_portState = PINB_INPUT_R;
			enu_ErrorState = DIO_E_PARAM_VALID;;
			break;
		case DIO_PORTC:
			*ptr_portState = PINC_INPUT_R;
			enu_ErrorState = DIO_E_PARAM_VALID;
			break;
		case DIO_PORTD:
			*ptr_portState = PIND_INPUT_R;
			enu_ErrorState = DIO_E_PARAM_VALID;
			break;
		default:
			enu_ErrorState = DIO_E_PARAM_INVALID_PORT_ID;	/* Invalid port id */
			break;
		}
	}
	return enu_ErrorState;
}

/******************************************************************************
 * [Function Name]: DIO_readPin
 *
 * [Description]: 	Function to read the value of the certain pin
 *
 * [Args]:			port_ID, pin_ID, pin_State
 *
 * [in]			  	port_ID: Enumerator to DIO port ID
 *					pin_ID: Enumerator to DIO pin ID
 *					pin_State: Pointer to Unsigned character value to return the
 *							   state of the pin in it
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       Error State
 ******************************************************************************/
enuDIO_E_STATE_t DIO_readPin(enuDIO_PortId_t enu_portID, enuDIO_PinId_t enu_pinID, uint8_t * ptr_pinState)
{
	enuDIO_E_STATE_t enu_ErrorState = E_NOT_OK;

	/* Check if the pointer is NULL pointer or not */
	if(ptr_pinState == NULL_PTR)
    {
		enu_ErrorState = DIO_E_PARAM_POINTER;
	}
	else
	{
        if((enu_pinID >= PIN_0) && (enu_pinID <= PIN_7))
        {
            switch (enu_portID)
            {
            case DIO_PORTA:
                *ptr_pinState = READ_BIT(PINA_INPUT_R, enu_pinID);
                enu_ErrorState = DIO_E_PARAM_VALID;
                break;
            case DIO_PORTB:
                *ptr_pinState = READ_BIT(PINB_INPUT_R, enu_pinID);
                enu_ErrorState = DIO_E_PARAM_VALID;
                break;
            case DIO_PORTC:
                *ptr_pinState = READ_BIT(PINC_INPUT_R, enu_pinID);
                enu_ErrorState = DIO_E_PARAM_VALID;
                break;
            case DIO_PORTD:
                *ptr_pinState = READ_BIT(PIND_INPUT_R, enu_pinID);
                enu_ErrorState = DIO_E_PARAM_VALID;
                break;
            default:
            	enu_ErrorState = DIO_E_PARAM_INVALID_PORT_ID;	/* Invalid port id */
                break;
            }
        }
        else
        {
        	enu_ErrorState = DIO_E_PARAM_INVALID_PIN_ID;	/* Invalid pin id */
        }
	}
    return enu_ErrorState;
}

/******************************************************************************
 * [Function Name]: DIO_TogglePin
 *
 * [Description]: 	Function to toggle a pin
 *
 * [Args]:			port_ID, pin_ID
 *
 * [in]			  	port_ID: Enumerator to DIO port ID
 *					pin_ID: Enumerator to DIO pin ID
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       Error State
 ******************************************************************************/
enuDIO_E_STATE_t DIO_TogglePin(enuDIO_PortId_t enu_portID, enuDIO_PinId_t enu_pinID)
{
	enuDIO_E_STATE_t enu_ErrorState = E_NOT_OK;

	/* Check if the pointer is NULL pointer or not */
    if ((enu_pinID >= PIN_0) && (enu_pinID <= PIN_7))
    {
        switch (enu_portID)
        {
        case DIO_PORTA:
            TOGGLE_BIT(PORTA_DATA_R, enu_pinID);
            enu_ErrorState = DIO_E_PARAM_VALID;
            break;
        case DIO_PORTB:
        	TOGGLE_BIT(PORTB_DATA_R, enu_pinID);
            enu_ErrorState = DIO_E_PARAM_VALID;
            break;
        case DIO_PORTC:
        	TOGGLE_BIT(PORTC_DATA_R, enu_pinID);
            enu_ErrorState = DIO_E_PARAM_VALID;
            break;
        case DIO_PORTD:
        	TOGGLE_BIT(PORTD_DATA_R, enu_pinID);
            enu_ErrorState = DIO_E_PARAM_VALID;
            break;
        default:
        	enu_ErrorState = E_NOT_OK;	/* Invalid port id */
            break;
        }
    }
    else
    {
    	enu_ErrorState = DIO_E_PARAM_INVALID_PIN_ID;	/* Invalid pin id */
    }
    return enu_ErrorState;
}
