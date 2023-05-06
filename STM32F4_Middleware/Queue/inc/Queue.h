#ifndef __QUEUE_H__
#define __QUEUE_H__

/*******************************************************************************
* Inclusions
******************************************************************************/
#include "Std_Type.h"

/*******************************************************************************
* Definitions
******************************************************************************/
#define QUEUE_EMPTY 				(0U)
#define QUEUE_EMPTY_PEEK_VALUE		(0xFFFFFFFFU)

/*** Queue State ***/
typedef enum
{
    QUEUE_INIT      = 0u,
    QUEUE_UNINIT    = 1u
} Queue_State;

/*** Define Queue Types ***/
typedef struct {
    int8    Front, Rear, Size;
    uint8	Capacity;
    uint32 *QueueArr;
} Queue_Types;

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
Bool_Type Queue_Create(uint8 Capacity);

/**
 * @func    Queue_PushData
 * @brief   Push Data to Queue and increase size of Queue
 * @param   InputData
 * @reval   TRUE        - Queue is not Full - Data pushed
 *          FALSE       - Queue is Full - Data cannot be pushed
 */
Bool_Type Queue_PushData(uint32 InputData);

/**
 * @func    Queue_PopData
 * @brief   Get Data From Queue if queue is not empty
 * @param   None
 * @reval   PeekData    Data get from queue
 *          QUEUE_EMPTY_PEEK_VALUE  -   Queue is empty
 */
uint32 Queue_PopData(void);

/**
 * @func    Queue_IsEmpty
 * @brief   Check if queue is empty or not
 * @param   None
 * @reval   TRUE        - Queue is Empty
 *          FALSE       - Queue is not Empty
 */
Bool_Type Queue_IsEmpty(void);

/**
 * @func    Queue_IsFull
 * @brief   Check if queue is full or not
 * @param   None
 * @reval   TRUE        - Queue is Full
 *          FALSE       - Queue is not Full
 */
Bool_Type Queue_IsFull(void);

#ifdef C_QUEUE_TEST
#include <stdio.h>
void Queue_Print(void);
#endif

#endif /* _QUEUE_H_ */


