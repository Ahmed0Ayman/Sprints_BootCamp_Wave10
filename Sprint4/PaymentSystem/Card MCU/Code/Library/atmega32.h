 /******************************************************************************
 *
 * [MODULE]: Registers of ATMEGA32 Micro-controller
 *
 * [FILE NAME]: atmega32.h
 *
 * [DESCRIPTION]: Registers for AVR
 *
 * [AUTHOR]: Ahmed Hassan
 *
 *******************************************************************************/
 
#ifndef ATMEGA32_H_
#define ATMEGA32_H_

/*****************************************************************************
 *							DIO registers (PORTA)
 *****************************************************************************/

#define PORTA_DATA_R     	*((volatile uint8_t*)0x3B)
#define DDRA_DIR_R        	*((volatile uint8_t*)0x3A)
#define PINA_INPUT_R      	*((volatile uint8_t*)0x39)

/*****************************************************************************
 * 							DIO registers (PORTB)
 *****************************************************************************/

#define PORTB_DATA_R       	*((volatile uint8_t*)0x38)
#define DDRB_DIR_R       	*((volatile uint8_t*)0x37)
#define PINB_INPUT_R      	*((volatile uint8_t*)0x36)

/*****************************************************************************
 *							DIO registers (PORTC)
 *****************************************************************************/

#define PORTC_DATA_R       	*((volatile uint8_t*)0x35)
#define DDRC_DIR_R        	*((volatile uint8_t*)0x34)
#define PINC_INPUT_R      	*((volatile uint8_t*)0x33)

/*****************************************************************************
 *							DIO registers (PORTD)
 *****************************************************************************/
 
#define PORTD_DATA_R       	*((volatile uint8_t*)0x32)
#define DDRD_DIR_R        	*((volatile uint8_t*)0x31)
#define PIND_INPUT_R		*((volatile uint8_t*)0x30)

/*
 *****************************************************************************
 *							TIMER registers (TIMER0)
 *****************************************************************************

#define TCCR0      	*((volatile uint8_t*)0x53)
#define TCNT0       *((volatile uint8_t*)0x52)
#define OCR0     	*((volatile uint8_t*)0x5C)

#define MCUCR       *((volatile uint8_t*)0x55)
#define MCUCSR      *((volatile uint8_t*)0x54)

#define TWCR      	*((volatile uint8_t*)0x56)

#define SPMCR      	*((volatile uint8_t*)0x57)

#define TIFR       	*((volatile uint8_t*)0x58)
#define TIMSK      	*((volatile uint8_t*)0x59)

#define GIFR      	*((volatile uint8_t*)0x5A)
#define GICR       	*((volatile uint8_t*)0x5B)

*****************************************************************************
 *							TIMER registers (TIMER1)
 *****************************************************************************
 
#define ICR1L      	*((volatile uint8_t*)0x46)
#define ICR1H      	*((volatile uint8_t*)0x47)
#define OCR1BL      *((volatile uint8_t*)0x48)
#define OCR1BH      *((volatile uint8_t*)0x49)
#define OCR1AL      *((volatile uint8_t*)0x4A)
#define OCR1AH      *((volatile uint8_t*)0x4B)
#define TCNT1L      *((volatile uint8_t*)0x4C)
#define TCNT1H      *((volatile uint8_t*)0x4D)
#define TCCR1B      *((volatile uint8_t*)0x4E)
#define TCCR1A      *((volatile uint8_t*)0x4F)

#define SFIOR      	*((volatile uint8_t*)0x50)

*****************************************************************************
 *							TIMER registers (TIMER2)
 *****************************************************************************

#define TCCR2       *((volatile uint8_t*)0x45)
#define TCNT2      	*((volatile uint8_t*)0x44)
#define OCR2      	*((volatile uint8_t*)0x43)

*****************************************************************************
 *								TWI registers 
 *****************************************************************************
 
#define TWDR      	*((volatile uint8_t*)0x23)
#define TWAR       	*((volatile uint8_t*)0x22)
#define TWSR      	*((volatile uint8_t*)0x21)
#define TWBR      	*((volatile uint8_t*)0x20)

*****************************************************************************
 *								ADC registers 
 *****************************************************************************

#define ADMUX      	*((volatile uint8_t*)0x27)
#define ADCSRA      *((volatile uint8_t*)0x26)
#define ADCH       	*((volatile uint8_t*)0x25)
#define ADCL      	*((volatile uint8_t*)0x24)

*****************************************************************************
 *							Analog Comparator registers 
 *****************************************************************************

#define ACSR       	*((volatile uint8_t*)0x28)

*****************************************************************************
 *								USART registers 
 *****************************************************************************
 
#define UDR      	*((volatile uint8_t*)0x2C)
#define UCSRA       *((volatile uint8_t*)0x2B)
#define UCSRB      	*((volatile uint8_t*)0x2A)
#define UBRRL      	*((volatile uint8_t*)0x29)

*****************************************************************************
 *								SPI registers 
 *****************************************************************************

#define SPDR    	*((volatile uint8_t*)0x2F)
#define SPSR       	*((volatile uint8_t*)0x2E)
#define SPCR      	*((volatile uint8_t*)0x2D)

*****************************************************************************
 *								EEPROM registers 
 *****************************************************************************

#define EEARH      	*((volatile uint8_t*)0x3F)
#define EEARL      	*((volatile uint8_t*)0x3E)
#define EEDR       	*((volatile uint8_t*)0x3D)
#define EECR      	*((volatile uint8_t*)0x3C)

#define UBRRH      	*((volatile uint8_t*)0x32)
#define UCSRC       *((volatile uint8_t*)0x31)

#define ASSR       	*((volatile uint8_t*)0x42)

#define WDTCR      	*((volatile uint8_t*)0x41)

*****************************************************************************
 *								Additional registers
 *****************************************************************************
 
#define SREG     	*((volatile uint8_t*)0x5F)
#define SPH      	*((volatile uint8_t*)0x5E)
#define SPL      	*((volatile uint8_t*)0x5D)
*/

#endif /* ATMEGA32_H_ */
