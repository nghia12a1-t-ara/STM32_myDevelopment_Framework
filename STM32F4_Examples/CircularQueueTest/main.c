#include <stdio.h>
#include "CircularQueue.h"

int main() {
    CircularQueue_Create(6);
	uint32_t data = 1;
	uint32_t data2 = 131;
	uint32_t data3 = 53;
	uint32_t data4 = 546;
	uint32_t data5 = 1234;
	uint32_t data6 = 542313;
	uint32_t data7 = 2344576;
	
	uint32_t DataPeek;
	
    printf(" ---- Test Peek when Queue is empty ---- \n");
	
	printf("DataPeek = %d\n", CircularQueue_PopData());
    CircularQueue_Print();
    
    printf(" ---- Test Push Data into Queue ---- \n");
	printf("%d ", CircularQueue_PushData(data));
	printf("%d ", CircularQueue_PushData(data2));
	printf("%d ", CircularQueue_PushData(data3));
	printf("%d ", CircularQueue_PushData(data4));
	printf("%d ", CircularQueue_PushData(data5));
	printf("%d ", CircularQueue_PushData(data6));
	printf("%d ", CircularQueue_PushData(data7));
	printf("\n");
    CircularQueue_Print();
    
    printf(" ---- Test Peek Data when Queue is Full ---- \n");
	printf("DataPeek = %d\n", CircularQueue_PopData());
	printf("DataPeek = %d\n", CircularQueue_PopData());
	printf("DataPeek = %d\n", CircularQueue_PopData());
    CircularQueue_Print();
    
    printf("%d ", CircularQueue_PushData(data));
	printf("%d ", CircularQueue_PushData(data2));
	printf("%d ", CircularQueue_PushData(data3));
	printf("%d ", CircularQueue_PushData(data4));
	printf("%d ", CircularQueue_PushData(data5));
    printf("\n");
    CircularQueue_Print();
    
	return 0;
}