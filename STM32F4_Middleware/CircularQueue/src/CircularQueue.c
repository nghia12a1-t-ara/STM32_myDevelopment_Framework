/* Circular Queue implementation in C */
#include "CircularQueue.h"

Queue_Types testQueue = {
	0, -1, QUEUE_SIZE,
	0,
	&QUEUE_State_Arr[0]
};

/* Check full of Queue */
static uint8_t CircularQueue_IsFull(CircularQueue_Types *Queue)
{
	uint8_t Key = FALSE;
	if ((Queue->Front == Queue->Rear + 1) || (Queue->Front == 0 && Queue->Rear == Queue->Size - 1)) 
	{
		Key = TRUE;
	}
	return Key;
}

/* Check empty of Queue */
static uint8_t CircularQueue_IsEmpty(CircularQueue_Types *Queue)
{
	uint8_t Key = FALSE;
	if (Queue->Front == -1)
	{
		Key = TRUE;
	}
	return Key;  
}

/* Hadling push data in queue */
void CircularQueue_PushData(CircularQueue_Types *Queue, uint32_t InputData)
{
	if (!CircularQueue_IsFull(Queue))
	{
		if (Queue->Front == -1) 
		{
			Queue->Front = 0;
		}
		Queue->Rear = (Queue->Rear + 1) % Queue->Size;
		Queue->QueueArr[Queue->Rear] = InputData;
	}
}

/* Handling peek data in queue */
uint32_t CircularQueue_PopData(CircularQueue_Types *Queue)
{
	uint32_t DataOut;

	if (!CircularQueue_IsEmpty(Queue))
	{
		DataOut = Queue->QueueArr[Queue->Front];
		if (Queue->Front == Queue->Rear) 
		{
			Queue->Front = -1;
			Queue->Rear = -1;
		} 
		// Q has only one DataOut, so we reset the 
		// queue after dequeing it. ?
		else
		{
		  Queue->Front = (Queue->Front + 1) % Queue->Size;
		}
	}
	return (DataOut);
}
