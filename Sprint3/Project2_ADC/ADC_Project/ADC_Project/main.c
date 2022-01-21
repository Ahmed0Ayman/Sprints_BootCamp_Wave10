/*
 * ADC_Project.c
 *
 * Created: 1/17/2022 6:45:19 AM
 * Author : Ahmed_Ayman
 */ 
#define F_CPU 16000000u

#include <avr/io.h>
#include <util/delay.h>
#include "HAL_GPIO.h"
#include "HAL_ADC.h"
#include "TIMER_Interface.h"
#include "But_LED.h"
#include "HAL_EXIT.h"
#include "Utilites.h"
#include "KeyPad.h"
#include "Lcd-Driver.h"
#include "Motor.h"
#include "TempSensor.h"
#include "HAL_I2c.h"

extern KeyPad_Handler_t KeyPad_Pins ;


uint8_t key = ' ' ; 
uint16_t x = 0 ; 
float res =0 ;
int main(void)
{
	LCD_Initializaion();
	KeyPad_Initialization(&KeyPad) ;

	LM35_Init(GPIO_PIN_0 , GPIOB);
	LCD_Send_String_WithLoc(1,1,"welcome");
	_delay_ms(2000);
	LCD_Send_Command(0x01);
    /* Replace with your application code */
    while (1) 
    {
		key = KeyPad_GetPressedKey(&KeyPad);
		LCD_Send_String_WithLoc(1,1,"Key = ");
		LCD_Send_Character_WithLoc(1,7,key);
		LCD_Send_String_WithLoc(2,2,"Temp = ");
		LCD_Send_Float_Withloc(2,8,LM35_Read());
    }

}

