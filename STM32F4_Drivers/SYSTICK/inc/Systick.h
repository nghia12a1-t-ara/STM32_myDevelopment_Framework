/**
 * Filename		: Systick.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Implement Systick Macros and Prototypes
 */

/* Prevention from multiple including the same memory map */
#if !defined(__SYSTICK_H__)  /* Check if memory map has not been already included */
#define __SYSTICK_H__

#include "SYSTICK_Base.h"
#include "Std_Type.h"

#define SYSTICK_GET_COUNTER() 					((SYSTICK->CVR) & SYSTICK_CVR_CURRENT_MASK)
#define SYSTICK_DELTA_OUTER(high, low, max) 	((max) - ((high) - (low)))
#define SYSTICK_DELTA_INNER(high, low) 			((high) - (low))
#define SYSTICK_MAX 							(0xFFFFFFu)
#define SYSTICK_MAX_DELAY 						(0xFFFFFFFFu)

#define SYSTICK_OVERFLOWED(curr, ref) 			(curr > ref)

#define SYSTICK_CLKSRC_EXTERNAL                 0u
#define SYSTICK_CLKSRC_PROCESSOR                1u

typedef enum
{
	SYSTICK_FREQ_10HZ         = 100U,
	SYSTICK_FREQ_100HZ        = 10U,
	SYSTICK_FREQ_1KHZ         = 1U,
	SYSTICK_FREQ_DEFAULT      = SYSTICK_FREQ_1KHZ
} Systick_FreqType;

/**
 * @fn		Systick_Init
 * @brief	Initialize Sys-tick Timer
 */
void Systick_Init(uint32 SystemCounterFreq);

/**
 * @fn		Systick_GetCounter
 * @brief	Get counter value
 */
uint32 Systick_GetCounter(void);

/**
 * @fn		Systick_GetElapsed
 * @brief	Get remaining time
 */
uint32 Systick_GetElapsed(uint32 * const CurrentRef);

/**
 * @fn		Systick_MicrosToTicks
 * @brief	Convert time (micro-second) to tick value
 */
uint32 Systick_MicrosToTicks(uint32 Micros);

/**
 * @fn		Sys_Delay
 * @brief	Custom Delay for Application
 */
void Sys_Delay(uint32 utime);


/******************************************************************************/
/****************************** TIMEOUT FUNCTIONS *****************************/
/**
 * @brief   : Prepare for timeout checking
 * @
 * @return  : None
 */
__STATIC_INLINE void Systick_StartTimeout(uint32 * StartTimeOut, uint32 *TimeoutTicksOut, uint32 TimeoutUs)
{
	/* Get current Counter Value */
    *StartTimeOut    = ((SYSTICK->CVR) & SYSTICK_CVR_CURRENT_MASK);
    *TimeoutTicksOut = Systick_MicrosToTicks(TimeoutUs);
    SYSTICK->CSR 	|= SYSTICK_CSR_ENABLE(ENABLE);
}

/**
 * @brief   : Checks for timeout condition
 * @
 * @return  TRUE     Timeout occurs
 *          FALSE    Timeout does not occur
 */
__STATIC_INLINE Bool_Type Systick_CheckTimeout(uint32 * StartTime, uint32 * ElapsedTicks, uint32 TimeoutTicks)
{
    uint32 CurrentElapsedTicks = Systick_GetElapsed(StartTime);
    *ElapsedTicks += CurrentElapsedTicks;
    return ((*ElapsedTicks >= TimeoutTicks) ? TRUE : FALSE);
}

#endif  /* #if !defined(__SYSTICK_BASE_H__) */
