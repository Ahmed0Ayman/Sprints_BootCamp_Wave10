/*
 * NonBlockingKeyPad.c
 *
 * Created: 2/8/2022 2:59:15 PM
 * Author : Ahmed_Ayman
 */ 

#include <avr/io.h>
#include "APP.h"

int main(void)
{
	APP_Init();
    /* Replace with your application code */
    while (1) 
    {
		APP_Update();
    }
}

