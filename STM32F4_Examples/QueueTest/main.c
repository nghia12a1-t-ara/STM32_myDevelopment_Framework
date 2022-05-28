#include <stdio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#include "Queue.h"

#define NUMBER_STATE_QUEUE		5

uint32_t QUEUE_State_Arr[NUMBER_STATE_QUEUE] = {0, 0, 0, 0, 0};
Queue_Types testQueue = {
		0,-1,NUMBER_STATE_QUEUE,
		0,
		&QUEUE_State_Arr[0]
	};

int main(int argc, char *argv[]) 
{	
	uint32_t data = 1;
	uint32_t data2 = 131;
	uint32_t data3 = 53;
	uint32_t data4 = 546;	
	uint32_t data5 = 4373;	
	
	uint32_t DataPeek;
	
	for (int i = 0; i < NUMBER_STATE_QUEUE; i++)
	{
		printf("%d\t", QUEUE_State_Arr[i]);
	}
	printf("\n");
	
	Queue_PushData(&testQueue, data);
	Queue_PushData(&testQueue, data2);
	Queue_PushData(&testQueue, data3);
	Queue_PushData(&testQueue, data4);
	Queue_PushData(&testQueue, data5);
	
	for (int i = 0; i < NUMBER_STATE_QUEUE; i++)
	{
		printf("%d\t", QUEUE_State_Arr[i]);
	}
	printf("\n");
	
	DataPeek = Queue_PeekData(&testQueue);
	Queue_Pop(&testQueue);
	
	printf("DataPeek = %d\n", DataPeek);
	
	for (int i = 0; i < NUMBER_STATE_QUEUE; i++)
	{
		printf("%d\t", QUEUE_State_Arr[i]);
	}
	printf("\n");
	
	
	DataPeek = Queue_PeekData(&testQueue);
	Queue_Pop(&testQueue);
	
	printf("DataPeek = %d\n", DataPeek);
	
	for (int i = 0; i < NUMBER_STATE_QUEUE; i++)
	{
		printf("%d\t", QUEUE_State_Arr[i]);
	}
	printf("\n");
	
	return 0;
}
