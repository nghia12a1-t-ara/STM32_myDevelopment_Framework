#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdint.h>
#include <stdlib.h>

/*******************************************************************************
* Definitions
******************************************************************************/
typedef enum Boolean {
	TRUE = 0x1U,
	FALSE = 0x0U
} Bool;
#define TRUE 						(1U)
#define FALSE 						(0U)
#define QUEUE_EMPTY 				(0U)
#define QUEUE_EMPTY_PEEK_VALUE		(0U)

/*** Define Queue Types ***/
typedef struct {
    int8_t Front, Rear, Size;
    uint8_t	Capacity;
    uint32_t * QueueArr;
} Queue_Types;

/*******************************************************************************
* API
******************************************************************************/
/* Initialize a Queue */
// Queue_Types* createQueue(uint8_t Capacity);
/* Pop data from queue */
void Queue_Pop(Queue_Types *Queue);
/* Hadling push data in queue */
void Queue_PushData(Queue_Types *Queue, uint32_t InputData);
/* Handling peek data in queue */
uint32_t Queue_PeekData(Queue_Types *Queue);
/* Check empty of Queue */
uint8_t Queue_IsEmpty(Queue_Types *Queue);
/* Check full of Queue */
uint8_t Queue_IsFull(Queue_Types *Queue);


#endif /* _QUEUE_H_ */


