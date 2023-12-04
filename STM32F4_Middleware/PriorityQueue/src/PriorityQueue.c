/* Priority s_PriorityQueue implementation in C */
#include "PriorityQueue.h"
#include <stdlib.h>

/* DESIGN: QUEUE will contain n task ID with Priority
 *  - When Push an TaskID to Queue, Queue is sorted again with new priority
 *  - When Queue is Full and Pushed TaskID has higher priority than lowest priority task, new TaskID will be pushed, overwrite the lowest priority TaskID
 */
/*******************************************************************************
* Typedef (Struct, Union, Enum)
******************************************************************************/
typedef struct
{
    uint32  TaskID;
    uint8   Priority;
} Task_t;

/*** Define Queue Types ***/
typedef struct {
    int8    Front, Rear, Size;
    uint8	Capacity;
    Task_t  *QueueArr;
} PriorityQueue_Types;

/*******************************************************************************
* Variables
******************************************************************************/
static PriorityQueue_State s_QueueState = PRIORITY_QUEUE_UNINIT;

static PriorityQueue_Types s_PriorityQueue = {
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
 * @func    PriorityQueue_Create
 * @brief   Initialize a Queue with dynamic size
 * @param   Capacity    - maximum size of queue
 * @reval   TRUE        - If create successfull
 *          FALSE       - If Heap is not enough memory
 */
Bool_Type PriorityQueue_Create(uint8 Capacity)
{
    uint8 count = 0;
    Bool_Type retval = FALSE;
    if ( PRIORITY_QUEUE_UNINIT == s_QueueState )
    {
        s_PriorityQueue.QueueArr = (Task_t *)malloc(sizeof(Task_t)*Capacity);
    }

    if ( NULL_PTR != s_PriorityQueue.QueueArr )
    {
        /* Reset all data in Queue and Reset Queue State */
        for (count = 0; count < Capacity; count++)
        {
            s_PriorityQueue.QueueArr[count].TaskID   = 0U;
            s_PriorityQueue.QueueArr[count].Priority = 0U;
        }
        s_PriorityQueue.Capacity    =   Capacity;
        s_PriorityQueue.Front       =   -1;
        s_PriorityQueue.Rear        =   -1;
        s_PriorityQueue.Size        =   0;
        s_QueueState                =   PRIORITY_QUEUE_INIT;
        retval                      =   TRUE;
    }
    return retval;
}

/**
 * @func    PriorityQueue_PushData
 * @brief   Push Data with Priority to Queue and increase size of Queue
 * @param   TaskID (Data)
 * @reval   TRUE        - Queue is not Full - Data pushed or Queue is Full but Pushed Data has Higher Priority than Current Elements
 *          FALSE       - Queue is Full - Data cannot be pushed
 */
Bool_Type PriorityQueue_PushData(uint32 TaskID, uint32 Priority)
{
    Bool_Type   Key             = FALSE;
    uint8       checkPosition   = s_PriorityQueue.Rear;
    uint8       shift_idx, idx, shiftPosition, nextPosition, pos;
    
	if ( FALSE == PriorityQueue_IsFull() )
	{
		if (s_PriorityQueue.Front == -1) 
		{
			s_PriorityQueue.Front = 0;
		}
		s_PriorityQueue.Rear = (s_PriorityQueue.Rear + 1) % s_PriorityQueue.Capacity;
        s_PriorityQueue.Size++;
        Key = TRUE;         /* Need Re-Sorting */
	}
    else if ( Priority > s_PriorityQueue.QueueArr[s_PriorityQueue.Rear].Priority )    /* Queue is Full, check the Priority */
    {
        /* Keep the Size */
        Key = TRUE;         /* Need Re-Sorting */
    }
    else
    {
        /* Queue is Full and Priority <= Lowest Priority TaskID */
    }
    
    /* Re-Sorting the Task with new Priority if Task is Valid */
    if ( TRUE == Key )
    {
        checkPosition = s_PriorityQueue.Rear;
        
        /* Find the Exactly Position, Start by Rear Position, idx = 0 */
        for (idx = 1U; idx < s_PriorityQueue.Size && s_PriorityQueue.Size > 1U; idx++)
        {
            if ( Priority <= s_PriorityQueue.QueueArr[checkPosition-1].Priority || checkPosition == s_PriorityQueue.Front )
            {
                break;
            }
        	if ( 0U == checkPosition )
        	{
        		checkPosition = s_PriorityQueue.Capacity - 1;
			}
			else
			{
				checkPosition--;
			}
        }
        
        /* Shift all the Data with Lower Priority TaskID */
        for (shift_idx = 0U; shift_idx < idx-1 && s_PriorityQueue.Size > 1; shift_idx++)
        {
        	if ( 0U == s_PriorityQueue.Rear )
        	{
        		shiftPosition = s_PriorityQueue.Capacity - 1;
			}
			else
			{
				shiftPosition = s_PriorityQueue.Rear - shift_idx - 1;
			}
            nextPosition  = (shiftPosition + 1) % s_PriorityQueue.Capacity;
            
            /* Shift Data to next Position */
            s_PriorityQueue.QueueArr[nextPosition].TaskID   = s_PriorityQueue.QueueArr[shiftPosition].TaskID;
            s_PriorityQueue.QueueArr[nextPosition].Priority = s_PriorityQueue.QueueArr[shiftPosition].Priority;
        }
        
        /* Update the Pushed Data */
        s_PriorityQueue.QueueArr[checkPosition].TaskID   = TaskID;
        s_PriorityQueue.QueueArr[checkPosition].Priority = Priority;
    }
    
    return Key;
}

/**
 * @func    PriorityQueue_PopData
 * @brief   Get Data with highest Priority From Queue if queue is not empty
 * @param   Reference of TaskID
 * @param   Reference of Priority
 * @reval   Boolean FALSE if queue is empty
 * @reval   Boolean TRUE if queue is not empty and data is got
 */
Bool_Type PriorityQueue_PopData(uint32 *pTaskID, uint8 *pPrio)
{
	Bool_Type status = FALSE;

	if ( FALSE == PriorityQueue_IsEmpty() )
	{
		*pTaskID = s_PriorityQueue.QueueArr[s_PriorityQueue.Front].TaskID;
		*pPrio   = s_PriorityQueue.QueueArr[s_PriorityQueue.Front].Priority;
		if ( s_PriorityQueue.Front == s_PriorityQueue.Rear )
		{
			s_PriorityQueue.Front = -1;
			s_PriorityQueue.Rear  = -1;
		}
		/* Q has only one PeekData, so we reset the
		 * s_PriorityQueue after dequeing it. ? */
		else
		{
            s_PriorityQueue.Front = (s_PriorityQueue.Front + 1) % s_PriorityQueue.Capacity;
		}
        s_PriorityQueue.Size--;
        status = TRUE;
	}
    else
    {
        /* Queue is Empty */
        *pTaskID = 0U;
		*pPrio   = 0U;
    }
	return status;
}

/**
 * @func    PriorityQueue_IsFull
 * @brief   Check if queue is full or not
 * @param   None
 * @reval   TRUE        - Queue is Full
 *          FALSE       - Queue is not Full
 */
Bool_Type PriorityQueue_IsFull(void)
{
	Bool_Type Key = FALSE;
	if ( (s_PriorityQueue.Front == s_PriorityQueue.Rear + 1) || \
         ((s_PriorityQueue.Front == 0) && (s_PriorityQueue.Rear == s_PriorityQueue.Capacity - 1))
    ) 
	{
		Key = TRUE;
    #ifdef C_Priority_QUEUE_TEST
        printf("\nQueue is Full\n");
    #endif
	}
	return Key;
}

/**
 * @func    PriorityQueue_IsEmpty
 * @brief   Check if queue is empty or not
 * @param   None
 * @reval   TRUE        - Queue is Empty
 *          FALSE       - Queue is not Empty
 */
Bool_Type PriorityQueue_IsEmpty(void)
{
	Bool_Type Key = FALSE;
	if ( PRIORITY_QUEUE_EMPTY == s_PriorityQueue.Size )
	{
		Key = TRUE;
    #ifdef C_Priority_QUEUE_TEST
        printf("\nQueue is Empty\n");
    #endif
	}
	return Key;  
}

#ifdef PRIORITY_QUEUE_TEST
void PriorityQueue_Print(void)
{
    int8 count = 0;
    if ( TRUE == PriorityQueue_IsEmpty() )
    {
        printf(">>> Priority Queue is Empty!\n");
        return;
    }
    
    printf("> Current Priority Queue: ");
    if ( s_PriorityQueue.Front <= s_PriorityQueue.Rear )
    {
        for (count = s_PriorityQueue.Front; count <= s_PriorityQueue.Rear; count++)
        {
            printf("%d ", s_PriorityQueue.QueueArr[count]);
        }
    }
    else
    {
        for (count = s_PriorityQueue.Front; count < s_PriorityQueue.Capacity; count++)
        {
            printf("%d ", s_PriorityQueue.QueueArr[count]);
        }
        for (count = 0; count <= s_PriorityQueue.Rear; count++)
        {
            printf("%d ", s_PriorityQueue.QueueArr[count]);
        }
    }
    printf("\n");
}
#endif