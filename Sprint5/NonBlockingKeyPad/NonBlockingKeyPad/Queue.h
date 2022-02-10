/*
 * Queue.h
 *
 * Created: 2/10/2022 9:33:01 AM
 *  Author: Ahmed_Ayman
 */ 


#ifndef __QUEUE__H_
#define __QUEUE__H_



#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

struct Queue
{
	uint8_t *ArrData ;
	uint32_t front ,rear ,capacity ;
	
};


struct Queue * QueueInitialize(uint32_t Size);
bool EnQueue(struct Queue * Q ,uint8_t * data);
bool DeQueue(struct Queue * Q,uint8_t * data);




















#endif