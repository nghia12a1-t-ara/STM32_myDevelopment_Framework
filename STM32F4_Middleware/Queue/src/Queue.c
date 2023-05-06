#include "Queue.h"
#include <stdlib.h>

/*******************************************************************************
* Variables
******************************************************************************/
static Queue_State s_QueueState = QUEUE_UNINIT;

static Queue_Types s_Queue = {
    .QueueArr = NULL_PTR,
    .Capacity = 0,
    .Front = -1,
    .Rear = -1,
    .Size = 0
};

/*******************************************************************************
                    *********** PUBLIC API ***********
******************************************************************************/
/**
 * @func    Queue_Create
 * @brief   Initialize a Queue with dynamic size
 * @param   Capacity    - maximum size of queue
 * @reval   TRUE        - If create successfull
 *          FALSE       - If Heap is not enough memory
 */
Bool_Type Queue_Create(uint8 Capacity)
{
    uint8 count = 0;
    Bool_Type retval = FALSE;
    if ( QUEUE_UNINIT == s_QueueState )
    {
        s_QueueState = QUEUE_INIT;
        s_Queue.QueueArr = (uint32 *)malloc(sizeof(uint32)*Capacity);
    }
    /* Reset all data in Queue and Reset Queue State */
    for (count = 0; count < Capacity; count++)
    {
        s_Queue.QueueArr[count] = 0;
    }
    if ( s_Queue.QueueArr != NULL_PTR )
    {
        s_Queue.Capacity    = Capacity;
        s_Queue.Front       = -1;
        s_Queue.Rear        = -1;
        s_Queue.Size        = 0;
    }
    return retval;
}

/**
 * @func    Queue_PushData
 * @brief   Push Data to Queue and increase size of Queue
 * @param   InputData
 * @reval   TRUE        - Queue is not Full - Data pushed
 *          FALSE       - Queue is Full - Data cannot be pushed
 */
Bool_Type Queue_PushData(uint32 InputData)
{
    Bool_Type Key = FALSE;
	if ( FALSE == Queue_IsFull() )
	{
        /* Push Data to Queue if queue is not full */
		s_Queue.QueueArr[++s_Queue.Rear] = InputData;
		s_Queue.Size++;
        Key = TRUE;
	}
    return Key;
}

/**
 * @func    Queue_PopData
 * @brief   Get Data From Queue if queue is not empty
 * @param   None
 * @reval   PeekData    Data get from queue
 *          QUEUE_EMPTY_PEEK_VALUE  -   Queue is empty
 */
uint32 Queue_PopData(void)
{
	uint32 PeekData = QUEUE_EMPTY_PEEK_VALUE;
	
	if ( FALSE == Queue_IsEmpty() )
	{
        /* Get Data From queue if queue is not empty */
		PeekData = s_Queue.QueueArr[++s_Queue.Front];
		s_Queue.Size--;
	}
	
	return PeekData;
}

/**
 * @func    Queue_IsEmpty
 * @brief   Check if queue is empty or not
 * @param   None
 * @reval   TRUE        - Queue is Empty
 *          FALSE       - Queue is not Empty
 */
Bool_Type Queue_IsEmpty(void)
{
	Bool_Type Key = FALSE;
	if ( s_Queue.Size == QUEUE_EMPTY )
	{
		Key = TRUE;
    #ifdef C_CIRCULAR_QUEUE_TEST
        printf("\nQueue is Empty\n");
    #endif
	}
	return Key;
}

/**
 * @func    Queue_IsFull
 * @brief   Check if queue is full or not
 * @param   None
 * @reval   TRUE        - Queue is Full
 *          FALSE       - Queue is not Full
 */
Bool_Type Queue_IsFull(void)
{
	Bool_Type Key = FALSE;
	if ( s_Queue.Size == s_Queue.Capacity )
	{
		Key = TRUE;
    #ifdef C_CIRCULAR_QUEUE_TEST
        printf("\nQueue is Full\n");
    #endif
	}
	return Key;
}

#ifdef C_QUEUE_TEST
void Queue_Print(void)
{
    int8 count = 0;
    if ( TRUE == Queue_IsEmpty() )
    {
        printf(">>> Queue is Empty!\n");
        return;
    }
    
    printf("> Current Queue: ");
    for (count = s_Queue.Front+1; count <= s_Queue.Rear; count++)
    {
        printf("%d ", s_Queue.QueueArr[count]);
    }
    printf("\n");
}
#endif
