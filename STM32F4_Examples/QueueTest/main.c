#include <stdio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#include "Queue.h"

int main(int argc, char *argv[]) 
{
    Queue_Create(6);
	uint32_t data = 1;
	uint32_t data2 = 131;
	uint32_t data3 = 53;
	uint32_t data4 = 546;
	uint32_t data5 = 1234;
	uint32_t data6 = 542313;
	uint32_t data7 = 2344576;
	
	uint32_t DataPeek;
	
    printf(" ---- Test Peek when Queue is empty ---- \n");
	
	printf("DataPeek = %d\n", Queue_PopData());
    Queue_Print();
    
    printf(" ---- Test Push Data into Queue ---- \n");
	printf("%d ", Queue_PushData(data));
	printf("%d ", Queue_PushData(data2));
	printf("%d ", Queue_PushData(data3));
	printf("%d ", Queue_PushData(data4));
	printf("%d ", Queue_PushData(data5));
	printf("%d ", Queue_PushData(data6));
	printf("%d ", Queue_PushData(data7));
	printf("\n");
    Queue_Print();
    
    Queue_Create(3);
    
    printf(" ---- Test Peek Data when Queue is Full ---- \n");
	printf("DataPeek = %d\n", Queue_PopData());
	printf("DataPeek = %d\n", Queue_PopData());
	printf("DataPeek = %d\n", Queue_PopData());
    Queue_Print();
    
    printf("%d ", Queue_PushData(data));
	printf("%d ", Queue_PushData(data2));
	printf("%d ", Queue_PushData(data3));
	printf("%d ", Queue_PushData(data4));
	printf("%d ", Queue_PushData(data5));
    Queue_Print();
    
	return 0;
}
