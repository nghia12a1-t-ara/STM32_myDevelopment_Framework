/**
 *	TaaRTOS v1.0
 *	tasks.h -> header file for manage tasks
 *	author	: NghiaTaarabt
 *	time	: 30/10/22
 */

/* Include guard for header file */
#ifndef __TASKS_H__
#define __TASKS_H__

#define OS_TASK_READY          (0U)
#define OS_TASK_BLOCKED        (1U)
#define OS_TASK_RUNNING        (2U)

typedef uint32_t stackType;

/* Define Task Control Block */
typedef struct
{
	volatile stackType 	    *pxTopOfStack;	        /*< Points to top of Task Stack >*/
	char 					*TaskName;              /*< Name of Tasks >*/
	uint8					Priority;		        /*< Priority of Tasks >*/
	uint8					Status;			        /*< Status of Task >*/
	uint32				    DelayTicks;		        /*< delay time of Task >*/
	void                    (*TaskFunc)(void *);        /*< function pointer that is implemented by task >*/
	struct task				*NextTask;		        /*< point to next Task in Linked List >*/
} TCB_Type;

TCB_Type* xTaskCreate(const char* TaskName,void(*TaskFunc)(void*),uint8_t priority, stackType* stack);

#endif /* __TASKS_H__ */
