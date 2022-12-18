#include "Queue.h"

/*******************************************************************************
* Variables
******************************************************************************/

/*******************************************************************************
* Code
******************************************************************************/
/* Initialize a Queue */
// Queue_Types* createQueue(uint8_t Capacity)
// {
	// Queue_Types* queue = (Queue_Types*)malloc(sizeof(Queue_Types));
    // queue->Capacity = Capacity;
    // queue->Front = queue->Size = 0;
 
    // This is important, see the enqueue
    // queue->Rear = Capacity - 1;
    // queue->QueueArr = (uint32_t*)malloc(queue->Capacity * sizeof(uint32_t));
    // return queue;
// }


/* Pop data from queue */
void Queue_Pop(Queue_Types *Queue)
{
	uint8_t count;
	if(!Queue_IsEmpty(Queue))
	{
		/* Update Possitive Queue Values */
		for (count = Queue->Front; count <= Queue->Rear; count++)
		{
			Queue->QueueArr[(count - Queue->Front)] = Queue->QueueArr[count];
		}
		
		/* Update Front, Rear Values */
		Queue->Front = 0;
		Queue->Rear = Queue->Capacity - 1;
		
		/* OPTIONAL : Update Nagative Queue Values */
		for (count = Queue->Capacity; count < Queue->Size; count++)
		{
			Queue->QueueArr[count] = 0;
		}
	}
}

/* Hadling push data in queue */
void Queue_PushData(Queue_Types *Queue, uint32_t InputData)
{
	if(!Queue_IsFull(Queue))
	{
		Queue->QueueArr[Queue->Rear + 1] = InputData;
		Queue->Rear++;
		Queue->Capacity++;
	}
}

/* Handling peek data in queue */
uint32_t Queue_PeekData(Queue_Types *Queue)
{
	uint32_t PeekData = QUEUE_EMPTY_PEEK_VALUE;
	
	if(!Queue_IsEmpty(Queue))
	{
		PeekData = Queue->QueueArr[Queue->Front];
		Queue->Front++;
		Queue->Capacity--;
	}
	else
	{
		
	}
	
	return PeekData;
}

/* Check empty of Queue */
uint8_t Queue_IsEmpty(Queue_Types *Queue)
{
	uint8_t Key = FALSE;
	if(Queue->Capacity == QUEUE_EMPTY)
	{
		Key = TRUE;
	}
	return Key;
}

/* Check full of Queue */
uint8_t Queue_IsFull(Queue_Types *Queue)
{
	uint8_t Key = FALSE;
	if(Queue->Capacity == Queue->Size)
	{
		Key = TRUE;
	}
	return Key;
}
