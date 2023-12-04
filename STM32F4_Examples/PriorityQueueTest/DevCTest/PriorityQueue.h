#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#define PRIORITY_QUEUE_TEST

/*******************************************************************************
* Inclusions
******************************************************************************/
#include "Std_Type.h"

/*******************************************************************************
* Definitions
******************************************************************************/
#define PRIORITY_QUEUE_EMPTY 				(0U)
#define PRIORITY_QUEUE_EMPTY_PEEK_VALUE		(0xFFFFFFFFU)

/*** Queue State ***/
typedef enum
{
    PRIORITY_QUEUE_INIT      = 0u,
    PRIORITY_QUEUE_UNINIT    = 1u
} PriorityQueue_State;

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
Bool_Type PriorityQueue_Create(uint8 Capacity);

/**
 * @func    PriorityQueue_PushData
 * @brief   Push Data with Priority to Queue and increase size of Queue
 * @param   TaskID (Data)
 * @reval   TRUE        - Queue is not Full - Data pushed or Queue is Full but Pushed Data has Higher Priority than Current Elements
 *          FALSE       - Queue is Full - Data cannot be pushed
 */
Bool_Type PriorityQueue_PushData(uint32 TaskID, uint32 Priority);

/**
 * @func    PriorityQueue_PopData
 * @brief   Get Data with highest Priority From Queue if queue is not empty
 * @param   Reference of TaskID
 * @param   Reference of Priority
 * @reval   Boolean FALSE if queue is empty
 * @reval   Boolean TRUE if queue is not empty and data is got
 */
Bool_Type PriorityQueue_PopData(uint32 *pTaskID, uint8 *pPrio);

/**
 * @func    PriorityQueue_IsFull
 * @brief   Check if queue is full or not
 * @param   None
 * @reval   TRUE        - Queue is Full
 *          FALSE       - Queue is not Full
 */
Bool_Type PriorityQueue_IsFull(void);

/**
 * @func    PriorityQueue_IsEmpty
 * @brief   Check if queue is empty or not
 * @param   None
 * @reval   TRUE        - Queue is Empty
 *          FALSE       - Queue is not Empty
 */
Bool_Type PriorityQueue_IsEmpty(void);

#ifdef PRIORITY_QUEUE_TEST
#include <stdio.h>
void PriorityQueue_Print(void);
#endif

#endif	/* _PRIORITY_QUEUE_H_ */
