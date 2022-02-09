/*
 * APP.h
 *
 * Created: 2/8/2022 3:05:56 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef APP_H_
#define APP_H_


#define F_CPU   16000000u
#include "KeyPad.h"
#include "TIMER_Interface.h"
#include "Lcd-Driver.h"
#include <util/delay.h>
#include "HAL_EXIT.h"
#include "LinkedList.h"
#include "Stack.h"

extern pstr_Stack_t Stack_Handler;

void APP_Init(void);



void APP_Update(void);









#endif /* APP_H_ */