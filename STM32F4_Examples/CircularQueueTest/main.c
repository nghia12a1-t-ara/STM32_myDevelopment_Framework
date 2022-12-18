#include <stdio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#include "CircularQueue.h"

#define QUEUE_SIZE				5

uint32_t QUEUE_State_Arr[QUEUE_SIZE] = {0};

CircularQueue_Types TestQueue = {
	-1, -1, QUEUE_SIZE,
	&QUEUE_State_Arr[0]
};

// Display the queue
void display(CircularQueue_Types *Queue) 
{
	uint8_t i;
	if (CircularQueue_IsEmpty(Queue))
	{
		printf(" \n Empty Queue\n");
	}
	else 
	{
		printf("\n Queue->Front -> %d ", Queue->Front);
		printf("\n Queue->QueueArr -> ");
		for (i = Queue->Front; i != Queue->Rear; i = (i + 1) % Queue->Size) 
		{
			printf("%d ", Queue->QueueArr[i]);
		}
		printf("%d ", Queue->QueueArr[i]);
		printf("\n Queue->Rear -> %d \n", Queue->Rear);
	}
}

int main() {
	/* Fails because Queue->Front = -1 */
	uint32_t Data;
	display(&TestQueue);
	
	Data = CircularQueue_PopData(&TestQueue);
	printf("\nPopData = %d\n", Data);
	
	CircularQueue_PushData(&TestQueue, 1);
	CircularQueue_PushData(&TestQueue, 2);
	CircularQueue_PushData(&TestQueue, 3);
	CircularQueue_PushData(&TestQueue, 4);
	CircularQueue_PushData(&TestQueue, 5);

	/* Fails to enqueue because Queue->Front == 0 && Queue->Rear == Queue->Size - 1 */
	CircularQueue_PushData(&TestQueue, 6);

	display(&TestQueue);
	
	Data = CircularQueue_PopData(&TestQueue);
	printf("\nPopData = %d\n", Data);

	display(&TestQueue);

	CircularQueue_PushData(&TestQueue, 7);
	display(&TestQueue);

	/* Fails to enqueue because Queue->Front == Queue->Rear + 1 */
	CircularQueue_PushData(&TestQueue, 8);
	display(&TestQueue);

	return 0;
}