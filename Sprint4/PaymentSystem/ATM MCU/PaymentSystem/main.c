/*
 * ComminucationProtocols.c
 *
 * Created: 1/23/2022 5:44:40 PM
 * Author : Ahmed_Ayman
 */ 

#include "APP.h"

int main(void)
{
	
    /* Replace with your application code */
	APP_Init();
    Motor_Start();
	sei();

	while (1) 
    {
		APP_UPdate();

	
	
		
    }
}

