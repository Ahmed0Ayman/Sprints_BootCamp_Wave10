/*
 * Queue.c
 *
 * Created: 2/10/2022 9:32:49 AM
 *  Author: Ahmed_Ayman
 */ 
#include "Queue.h"



struct Queue * QueueInitialize(uint32_t Size)
{
	struct Queue * Q = (struct Queue *)malloc(sizeof(struct Queue ));
	if(Q == NULL )
	return false ;
	
	Q->ArrData = (uint8_t *)malloc(Size * sizeof(uint8_t));
	if(Q->ArrData == NULL )
	return false ;
	
	
	Q->capacity = Size;
	Q->front = Q->rear = -1;
	return Q ;
	
}

bool EnQueue(struct Queue * Q ,uint8_t * data)
{
	uint32_t Size =Q->capacity ;
	if(Q == NULL )
	return false ;
	
	if(Q->rear == -1)
	{
		Q->rear = Q->front = 0;
		Q->ArrData[Q->rear] = *data ;
		return true ;
	}
	Q->rear =(Q->rear +1)%Q->capacity;

	if(((Q->rear)%(Size))==(Q->front))
	{
		Q->capacity = Q->capacity * 2 ;
		Q->ArrData = realloc(Q->ArrData,Q->capacity * sizeof(uint8_t));
		if(Q->ArrData == NULL)
		return false ;

		for(uint32_t i=Q->front;i<Size+Q->front;i++)
		{
			Q->ArrData[i+Size]=Q->ArrData[i];
		}
		Q->front = Q->front+Size;
		Q->ArrData[Q->rear] = *data ;
	}
	
	else
	{

		Q->ArrData[Q->rear] = *data ;
	}

	

	return true ;
	
}


bool DeQueue(struct Queue * Q,uint8_t * data)
{
	if(Q==NULL)
	return false ;
	
	if(Q->front == -1)
	return false ;
	
	*data =  Q->ArrData[Q->front];
	if(Q->front != Q->rear)
	Q->front = (Q->front +1) % (Q->capacity);
	else
	{
		Q->front = Q->rear = -1;
		return false ;
	}
	return true ;
}

