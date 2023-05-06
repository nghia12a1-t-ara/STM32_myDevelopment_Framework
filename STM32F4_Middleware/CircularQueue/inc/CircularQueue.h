#ifndef _CIRCULAR_QUEUE_H_
#define _CIRCULAR_QUEUE_H_

/*******************************************************************************
* Inclusions
******************************************************************************/
#include "Std_Type.h"

/*******************************************************************************
* Definitions
******************************************************************************/
#define CIRCULAR_QUEUE_EMPTY 				(0U)
#define CIRCULAR_QUEUE_EMPTY_PEEK_VALUE		(0xFFFFFFFFU)

/*** Queue State ***/
typedef enum
{
    CIRCULAR_QUEUE_INIT      = 0u,
    CIRCULAR_QUEUE_UNINIT    = 1u
} CircularQueue_State;

/*** Define Queue Types ***/
typedef struct {
    int8    Front, Rear, Size;
    uint8	Capacity;
    uint32 *QueueArr;
} CircularQueue_Types;

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
Bool_Type CircularQueue_Create(uint8 Capacity);

/**
 * @func    CircularQueue_PushData
 * @brief   Push Data to Queue and increase size of Queue
 * @param   InputData
 * @reval   TRUE        - Queue is not Full - Data pushed
 *          FALSE       - Queue is Full - Data cannot be pushed
 */
Bool_Type CircularQueue_PushData(uint32 InputData);

/**
 * @func    CircularQueue_PopData
 * @brief   Get Data From Queue if queue is not empty
 * @param   None
 * @reval   PeekData                            Data get from queue
 *          CIRCULAR_QUEUE_EMPTY_PEEK_VALUE     Queue is empty
 */
uint32 CircularQueue_PopData(void);

/**
 * @func    CircularQueue_IsFull
 * @brief   Check if queue is full or not
 * @param   None
 * @reval   TRUE        - Queue is Full
 *          FALSE       - Queue is not Full
 */
Bool_Type CircularQueue_IsFull(void);

/**
 * @func    CircularQueue_IsEmpty
 * @brief   Check if queue is empty or not
 * @param   None
 * @reval   TRUE        - Queue is Empty
 *          FALSE       - Queue is not Empty
 */
Bool_Type CircularQueue_IsEmpty(void);

#ifdef C_CIRCULAR_QUEUE_TEST
#include <stdio.h>
void CircularQueue_Print(void);
#endif

#endif	/* _CIRCULAR_QUEUE_H_ */
