#ifndef _CIRCULAR_QUEUE_H_
#define _CIRCULAR_QUEUE_H_

#include <stdint.h>
#include <stdlib.h>

/*******************************************************************************
* Definitions
******************************************************************************/
#define TRUE 						(1U)
#define FALSE 						(0U)
#define QUEUE_EMPTY 				(0U)
#define QUEUE_EMPTY_PEEK_VALUE		(0U)

/*** Define Queue Types ***/
typedef struct {
    int8_t Front, Rear, Size;
    uint32_t * QueueArr;
} CircularQueue_Types;


/*** Function Prototypes ***/
/* Check full of Queue */
uint8_t CircularQueue_IsFull(CircularQueue_Types *Queue);
/* Check empty of Queue */
uint8_t CircularQueue_IsEmpty(CircularQueue_Types *Queue);
/* Hadling push data in queue */
void CircularQueue_PushData(CircularQueue_Types *Queue, uint32_t InputData);
/* Handling peek data in queue */
uint32_t CircularQueue_PopData(CircularQueue_Types *Queue);

#endif	/* _CIRCULAR_QUEUE_H_ */
