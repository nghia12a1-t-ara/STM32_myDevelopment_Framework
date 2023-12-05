/* Priority s_Queue implementation in C */
#include "PriorityQueue.h"
#include <stdlib.h>

/* DESIGN: QUEUE will contain n task ID with Priority
 *  - When Push an TaskID to Queue, Queue is sorted again with new priority
 *  - When Queue is Full and Pushed TaskID has higher priority than lowest priority task, new TaskID will be pushed, overwrite the lowest priority TaskID
 */
/*******************************************************************************
* Typedef (Struct, Union, Enum)
******************************************************************************/
#define QUEUE_BACK_INDEX(idx)			((idx==0U)?(s_Queue.Capacity-1):(idx-1))
#define QUEUE_NEXT_INDEX(idx)			((idx+1)%s_Queue.Capacity)

typedef enum
{
	QUEUE_NOT_PUSH  	= 0U,
	QUEUE_SHIFT_REAR	= 1U,
	QUEUE_SHIFT_FRONT	= 2U,
	QUEUE_ADD_FRONT 	= 3U,
	QUEUE_ADD_HIGHEST	= 4U,
	QUEUE_ADD_REAR		= 5U
} CheckShift_t;

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

static PriorityQueue_Types s_Queue = {
    .QueueArr   =   NULL_PTR,
    .Capacity   =   0,
    .Front      =   -1,
    .Rear       =   -1,
    .Size       =   0
};
/*******************************************************************************
                    *********** PRIVATE API ***********
******************************************************************************/
/* Check shift right or left all the elements from an index */
static void Queue_Shift2Rear(uint8 inputIdx, Bool_Type bShiftRear);
static void Queue_Shift2Front(uint8 inputIdx, Bool_Type bShiftFront);
/* Find the Exactly Position, Start by Rear Position, idx = 0 */
static CheckShift_t Queue_FindPosition(uint8 *pPosition, uint8 Priority, Bool_Type bNotFull);

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
        s_Queue.QueueArr = (Task_t *)malloc(sizeof(Task_t)*Capacity);
    }

    if ( NULL_PTR != s_Queue.QueueArr )
    {
        /* Reset all data in Queue and Reset Queue State */
        for (count = 0; count < Capacity; count++)
        {
            s_Queue.QueueArr[count].TaskID   = 0U;
            s_Queue.QueueArr[count].Priority = 0U;
        }
        s_Queue.Capacity    =   Capacity;
        s_Queue.Front       =   -1;
        s_Queue.Rear        =   -1;
        s_Queue.Size        =   0;
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
    Bool_Type   RetVal = FALSE, Key = FALSE;
    Bool_Type   bShift          = TRUE;
	uint8       checkPosition   = s_Queue.Rear;
    uint8       Position;
    CheckShift_t status;
    
	if ( PriorityQueue_IsEmpty() )
	{
		s_Queue.Front 	= 0;
		s_Queue.Rear	= 0;
		s_Queue.Size++;
		s_Queue.QueueArr[0].TaskID 	= TaskID;
		s_Queue.QueueArr[0].Priority = Priority;
		RetVal = TRUE;
	}
	else if ( FALSE == PriorityQueue_IsFull() )
	{
		if (s_Queue.Front == -1) 
		{
			s_Queue.Front = 0;
		}
        Key = TRUE;         	/* Need Re-Sorting */
		s_Queue.Size++;
	}
    else if ( Priority > s_Queue.QueueArr[s_Queue.Rear].Priority )    /* Queue is Full, check the Priority */
    {
        /* If the Input Priority > the lowest Priority -> Keep the Size */
        bShift 	= FALSE;
        Key 	= TRUE;         /* Need Re-Sorting */
    }
    else
    {
        /* Queue is Full and Priority <= Lowest Priority TaskID */
    }
    
    /* Re-Sorting the Task with new Priority if Task is Valid */
    if ( TRUE == Key )
    {	
		/* Find the Exactly Position, Start by Rear Position, idx = 0 */
        status = Queue_FindPosition(&Position, Priority, bShift);
        
    	/* Optimize the Speed -> shift to Left or Right when compare the Priority with Center Elements */
        switch ( status )
        {
        	case QUEUE_SHIFT_REAR:
	        	Queue_Shift2Rear(Position, bShift);
			case QUEUE_ADD_REAR:
	        	s_Queue.Rear 	= QUEUE_NEXT_INDEX(s_Queue.Rear);
	        	break;
			case QUEUE_SHIFT_FRONT:
	        	Queue_Shift2Front(Position, bShift);
	        case QUEUE_ADD_FRONT:
	        	s_Queue.Front 	= QUEUE_BACK_INDEX(s_Queue.Front);
	        	if( TRUE == bShift )
	        	break;
	        case QUEUE_ADD_HIGHEST:
				s_Queue.Front 	= Position;
				s_Queue.Rear 	= QUEUE_BACK_INDEX(Position);
				break;
	        case QUEUE_NOT_PUSH:
	        	break;
		}
		
		/* Assign to Position Data */
		if( QUEUE_NOT_PUSH != status )
		{
			s_Queue.QueueArr[Position].TaskID 	= TaskID;
			s_Queue.QueueArr[Position].Priority = Priority;
			RetVal = TRUE;
		}
	}
    return RetVal;
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
		*pTaskID = s_Queue.QueueArr[s_Queue.Front].TaskID;
		*pPrio   = s_Queue.QueueArr[s_Queue.Front].Priority;
		if ( s_Queue.Front == s_Queue.Rear )
		{
			s_Queue.Front = -1;
			s_Queue.Rear  = -1;
		}
		/* Q has only one PeekData, so we reset the s_Queue after dequeing it. ? */
		else
		{
            s_Queue.Front = QUEUE_NEXT_INDEX(s_Queue.Front);
		}
        s_Queue.Size--;
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
	if ( (s_Queue.Front == s_Queue.Rear + 1) || \
         ((s_Queue.Front == 0) && (s_Queue.Rear == s_Queue.Capacity - 1))
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
	if ( PRIORITY_QUEUE_EMPTY == s_Queue.Size )
	{
		Key = TRUE;
    #ifdef C_Priority_QUEUE_TEST
        printf("\nQueue is Empty\n");
    #endif
	}
	return Key;  
}

/* Check shift right or left all the elements from an index */
static void Queue_Shift2Rear(uint8 inputIdx, Bool_Type bShiftRear)
{
	uint8 idx = s_Queue.Rear;
	uint8 nextPosition;
	
	/* NOT Shift the Rear Element */
	if ( FALSE == bShiftRear )
	{
		s_Queue.Front = QUEUE_NEXT_INDEX(s_Queue.Front);
	}
	
	/* Shift all element from Rear or Back of Rear to inputIdx */
	do
	{
		nextPosition = QUEUE_NEXT_INDEX(idx);
		s_Queue.QueueArr[nextPosition] = s_Queue.QueueArr[idx];
		idx = QUEUE_BACK_INDEX(idx);		/* Update index */
	} while( nextPosition != inputIdx );
}
static void Queue_Shift2Front(uint8 inputIdx, Bool_Type bShiftFront)
{
	uint8 idx = s_Queue.Front;
	uint8 nextPosition;
	
	if( FALSE == bShiftFront )
	{
		s_Queue.Rear = QUEUE_BACK_INDEX(s_Queue.Rear);
	}
	
	/* Shift all element from Front or Next of Front to inputIdx */
	do
	{
		nextPosition = QUEUE_BACK_INDEX(idx);
		s_Queue.QueueArr[nextPosition] = s_Queue.QueueArr[idx];
		idx = QUEUE_NEXT_INDEX(idx);		/* Update index */
	} while( nextPosition != inputIdx );
}

/* Find the Exactly Position, Start by Rear Position, idx = 0 */
static CheckShift_t Queue_FindPosition(uint8 *pPosition, uint8 Priority, Bool_Type bNotFull)
{
	uint8 Position = s_Queue.Rear, Count2Rear = 0U;
	CheckShift_t status;
	
	if( Priority > s_Queue.QueueArr[s_Queue.Front].Priority )
	{
		/* Need push the highest Priority */
		if( FALSE == bNotFull )
		{
			/* Queue is Full - New Ele will replace the lowest Priority and Update Params */
			status 			= QUEUE_ADD_HIGHEST;
			Position 		= s_Queue.Rear;		/* Lowest Priority */
		}
		else
		{
			/* Queue is Not Full */
			status 	 = QUEUE_ADD_FRONT;
			Position = QUEUE_BACK_INDEX(s_Queue.Front);
		}
	}
	else if ( Priority <= s_Queue.QueueArr[s_Queue.Rear].Priority )
	{
		if( FALSE == bNotFull )
		{
			/* Queue is Full and Can not push */
			status = QUEUE_NOT_PUSH;
		}
		else
		{
			/* Queue is Not Full */
			status 	 = QUEUE_ADD_REAR;
			Position = QUEUE_NEXT_INDEX(s_Queue.Rear);
		}
	}
	else	/* Scanf Position from Rear to Position */
	{
	    while( TRUE )
	    {
			if( Priority <= s_Queue.QueueArr[QUEUE_BACK_INDEX(Position)].Priority )
	    	{
	    		break;
			}
			else
			{
				Position = QUEUE_BACK_INDEX(Position);
				Count2Rear++;
			}
	    }
	    
	    /* Check if Position is near by Rear or Front than other */
	    if ( Count2Rear < (s_Queue.Size >> 1) )
	    {
	    	status = QUEUE_SHIFT_REAR;
		}
		else
		{
			status = QUEUE_SHIFT_FRONT;
			Position = QUEUE_BACK_INDEX(Position);
		}
	}
	
	*pPosition = Position;
	
    return status;
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
    if ( s_Queue.Front <= s_Queue.Rear )
    {
        for (count = s_Queue.Front; count <= s_Queue.Rear; count++)
        {
            printf("%d ", s_Queue.QueueArr[count]);
        }
    }
    else
    {
        for (count = s_Queue.Front; count < s_Queue.Capacity; count++)
        {
            printf("%d ", s_Queue.QueueArr[count]);
        }
        for (count = 0; count <= s_Queue.Rear; count++)
        {
            printf("%d ", s_Queue.QueueArr[count]);
        }
    }
    printf("\n");
}
#endif