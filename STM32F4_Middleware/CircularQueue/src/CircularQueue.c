/* Circular s_CircularQueue implementation in C */
#include "CircularQueue.h"
#include <stdlib.h>

/*******************************************************************************
* Typedef (Struct, Union, Enum)
******************************************************************************/
/*** Define Queue Types ***/
typedef struct {
    int8    Front, Rear, Size;
    uint8	Capacity;
    uint32 *QueueArr;
} CircularQueue_Types;

/*******************************************************************************
* Variables
******************************************************************************/
static CircularQueue_State s_QueueState = CIRCULAR_QUEUE_UNINIT;

static CircularQueue_Types s_CircularQueue = {
    .QueueArr   =   NULL_PTR,
    .Capacity   =   0,
    .Front      =   -1,
    .Rear       =   -1,
    .Size       =   0
};

/*******************************************************************************
                    *********** PUBLIC API ***********
******************************************************************************/
/**
 * @func    CircularQueue_Create
 * @brief   Initialize a Queue with dynamic size
 * @param   Capacity    - maximum size of queue
 * @reval   TRUE        - If create successfull
 *          FALSE       - If Heap is not enough memory
 */
Bool_Type CircularQueue_Create(uint8 Capacity)
{
    uint8 count = 0;
    Bool_Type retval = FALSE;
    if ( CIRCULAR_QUEUE_UNINIT == s_QueueState )
    {
        s_QueueState = CIRCULAR_QUEUE_INIT;
        s_CircularQueue.QueueArr = (uint32 *)malloc(sizeof(uint32)*Capacity);
    }
    
    if ( s_CircularQueue.QueueArr != NULL_PTR )
    {
        /* Reset all data in Queue and Reset Queue State */
        for (count = 0; count < Capacity; count++)
        {
            s_CircularQueue.QueueArr[count] = 0;
        }
        s_CircularQueue.Capacity    = Capacity;
        s_CircularQueue.Front       = -1;
        s_CircularQueue.Rear        = -1;
        s_CircularQueue.Size        = 0;
    }
    return retval;
}

/**
 * @func    CircularQueue_PushData
 * @brief   Push Data to Queue and increase size of Queue
 * @param   InputData
 * @reval   TRUE        - Queue is not Full - Data pushed
 *          FALSE       - Queue is Full - Data cannot be pushed
 */
Bool_Type CircularQueue_PushData(uint32 InputData)
{
    Bool_Type Key = FALSE;
	if ( FALSE == CircularQueue_IsFull() )
	{
		if (s_CircularQueue.Front == -1) 
		{
			s_CircularQueue.Front = 0;
		}
		s_CircularQueue.Rear = (s_CircularQueue.Rear + 1) % s_CircularQueue.Capacity;
		s_CircularQueue.QueueArr[s_CircularQueue.Rear] = InputData;
        s_CircularQueue.Size++;
        Key = TRUE;
	}
    return Key;
}

/**
 * @func    CircularQueue_PopData
 * @brief   Get Data From Queue if queue is not empty
 * @param   None
 * @reval   PeekData                            Data get from queue
 *          CIRCULAR_QUEUE_EMPTY_PEEK_VALUE     Queue is empty
 */
uint32 CircularQueue_PopData(void)
{
	uint32 PeekData = CIRCULAR_QUEUE_EMPTY_PEEK_VALUE;

	if ( FALSE == CircularQueue_IsEmpty() )
	{
		PeekData = s_CircularQueue.QueueArr[s_CircularQueue.Front];
		if ( s_CircularQueue.Front == s_CircularQueue.Rear )
		{
			s_CircularQueue.Front = -1;
			s_CircularQueue.Rear = -1;
		}
		/* Q has only one PeekData, so we reset the
		 * s_CircularQueue after dequeing it. ? */
		else
		{
            s_CircularQueue.Front = (s_CircularQueue.Front + 1) % s_CircularQueue.Capacity;
		}
        s_CircularQueue.Size--;
	}
	return PeekData;
}

/**
 * @func    CircularQueue_IsFull
 * @brief   Check if queue is full or not
 * @param   None
 * @reval   TRUE        - Queue is Full
 *          FALSE       - Queue is not Full
 */
Bool_Type CircularQueue_IsFull(void)
{
	Bool_Type Key = FALSE;
	if ( (s_CircularQueue.Front == s_CircularQueue.Rear + 1) || \
         ((s_CircularQueue.Front == 0) && (s_CircularQueue.Rear == s_CircularQueue.Capacity - 1))
    ) 
	{
		Key = TRUE;
    #ifdef C_CIRCULAR_QUEUE_TEST
        printf("\nQueue is Full\n");
    #endif
	}
	return Key;
}

/**
 * @func    CircularQueue_IsEmpty
 * @brief   Check if queue is empty or not
 * @param   None
 * @reval   TRUE        - Queue is Empty
 *          FALSE       - Queue is not Empty
 */
Bool_Type CircularQueue_IsEmpty(void)
{
	Bool_Type Key = FALSE;
	if ( CIRCULAR_QUEUE_EMPTY == s_CircularQueue.Size )
	{
		Key = TRUE;
    #ifdef C_CIRCULAR_QUEUE_TEST
        printf("\nQueue is Empty\n");
    #endif
	}
	return Key;  
}

#ifdef C_CIRCULAR_QUEUE_TEST
void CircularQueue_Print(void)
{
    int8 count = 0;
    if ( TRUE == CircularQueue_IsEmpty() )
    {
        printf(">>> Circular Queue is Empty!\n");
        return;
    }
    
    printf("> Current Circular Queue: ");
    if ( s_CircularQueue.Front <= s_CircularQueue.Rear )
    {
        for (count = s_CircularQueue.Front; count <= s_CircularQueue.Rear; count++)
        {
            printf("%d ", s_CircularQueue.QueueArr[count]);
        }
    }
    else
    {
        for (count = s_CircularQueue.Front; count < s_CircularQueue.Capacity; count++)
        {
            printf("%d ", s_CircularQueue.QueueArr[count]);
        }
        for (count = 0; count <= s_CircularQueue.Rear; count++)
        {
            printf("%d ", s_CircularQueue.QueueArr[count]);
        }
    }
    printf("\n");
}
#endif
