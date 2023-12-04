#include <stdio.h>
#define PRIORITY_QUEUE_TEST
#include "PriorityQueue.h"

typedef struct
{
    uint32  TaskID;
    uint8   Priority;
} Task_t;

int main() {
	
	Task_t Datapeek;

    PriorityQueue_Create(6);
	Task_t data  = { 1          , 1};
	Task_t data2 = { 131        , 4};
	Task_t data3 = { 53         , 3};
	Task_t data4 = { 546        , 4};
	Task_t data5 = { 1234       , 3};
	Task_t data6 = { 542313     , 6};
	Task_t data7 = { 2344576    , 5};
	Task_t data8 = { 10000      , 0};
	
    // printf(" ---- Test Peek when Queue is empty ---- \n");
	
	// printf("DataPeek = %d\n", PriorityQueue_PopData());
    // PriorityQueue_Print();
    
    printf(" ---- Test Push Data into Queue ---- \n");
	printf("%d ", PriorityQueue_PushData(data.TaskID, data.Priority));
	printf("%d ", PriorityQueue_PushData(data2.TaskID, data2.Priority));
	printf("%d ", PriorityQueue_PushData(data3.TaskID, data3.Priority));
	printf("%d ", PriorityQueue_PushData(data4.TaskID, data4.Priority));
	printf("%d ", PriorityQueue_PushData(data5.TaskID, data5.Priority));
	 
	PriorityQueue_Print();
	 
	printf("%d ", PriorityQueue_PushData(data6.TaskID, data6.Priority));

	PriorityQueue_Print();
	printf("%d ", PriorityQueue_PushData(data7.TaskID, data7.Priority));
	PriorityQueue_Print();
	printf("%d ", PriorityQueue_PushData(data7.TaskID, data7.Priority));
	PriorityQueue_Print();
	printf("%d ", PriorityQueue_PushData(data7.TaskID, data7.Priority)); 
	PriorityQueue_Print();
	printf("%d ", PriorityQueue_PushData(data8.TaskID, data8.Priority)); 
	PriorityQueue_Print();
    
    
    printf(" ---- Test Peek Data when Queue is Full ---- \n");
	printf("status = %d\n", PriorityQueue_PopData(&Datapeek.TaskID, &Datapeek.Priority));
	printf("TaskID = %d, Priority = %d\n",Datapeek.TaskID, Datapeek.Priority);
	PriorityQueue_Print();
	printf("status = %d\n", PriorityQueue_PopData(&Datapeek.TaskID, &Datapeek.Priority));
	printf("TaskID = %d, Priority = %d\n",Datapeek.TaskID, Datapeek.Priority);
	PriorityQueue_Print();
	printf("status = %d\n", PriorityQueue_PopData(&Datapeek.TaskID, &Datapeek.Priority));
	printf("TaskID = %d, Priority = %d\n",Datapeek.TaskID, Datapeek.Priority);
	PriorityQueue_Print();
	printf("status = %d\n", PriorityQueue_PopData(&Datapeek.TaskID, &Datapeek.Priority));
	printf("TaskID = %d, Priority = %d\n",Datapeek.TaskID, Datapeek.Priority);
	PriorityQueue_Print();
	printf("status = %d\n", PriorityQueue_PopData(&Datapeek.TaskID, &Datapeek.Priority));
	printf("TaskID = %d, Priority = %d\n",Datapeek.TaskID, Datapeek.Priority);
	PriorityQueue_Print();
	printf("status = %d\n", PriorityQueue_PopData(&Datapeek.TaskID, &Datapeek.Priority));
	printf("TaskID = %d, Priority = %d\n",Datapeek.TaskID, Datapeek.Priority);
	PriorityQueue_Print();
	printf("status = %d\n", PriorityQueue_PopData(&Datapeek.TaskID, &Datapeek.Priority));
	
	printf("status = %d\n", PriorityQueue_PopData(&Datapeek.TaskID, &Datapeek.Priority));
    
	return 0;
}
