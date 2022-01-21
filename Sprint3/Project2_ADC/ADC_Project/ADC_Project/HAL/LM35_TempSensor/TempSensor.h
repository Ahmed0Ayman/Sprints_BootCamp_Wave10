/*
 * TempSensor.h
 *
 * Created: 1/17/2022 10:23:52 AM
 *  Author: Ahmed_Ayman
 */ 


#ifndef TEMPSENSOR_H_
#define TEMPSENSOR_H_

#include "HAL_GPIO.h"


typedef enum {LM35_OK , LM35_PARAM_ERROR , LM35_ERROR }LM35_Status_t;


LM35_Status_t  LM35_Init(uint8_t Pin_Num , StrGPIO_t PORT);


float LM35_Read(void);



#endif /* TEMPSENSOR_H_ */