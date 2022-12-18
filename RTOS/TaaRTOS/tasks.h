/**
 *	TaaRTOS v1.0
 *	tasks.h -> header file for manage tasks
 *	author	: NghiaTaarabt
 *	time	: 30/10/22
 */

/* Include guard for header file */
#ifndef __TASKS_H__
#define __TASKS_H__

/* Define Task Control Block */
typedef struct
{
	volatile StackType_t 	*pxTopOfStack;	/*< Points to top of Task Stack >*/
	char 					*name; 			/*< Name of Tasks >*/
	uint8_t					Priority;		/*< Priority of Tasks >*/
	uint8_t					Status;			/*< Status of Task >*/
	uint32_t				DelayTicks;		/*< delay time of Task >*/
	void(*func)(void *);					/*< function pointer that is implemented by task >*/
	struct task				*NextTask;		/*< point to next Task in Linked List >*/
} TCB_Type;

#endif /* __TASKS_H__ */
