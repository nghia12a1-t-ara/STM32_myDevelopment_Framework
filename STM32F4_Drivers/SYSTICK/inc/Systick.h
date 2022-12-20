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
#include "Std_Types.h"

/**
 * @fn		Systick_Init
 * @brief	Initialize Systick Timer
 */
void Systick_Init(uint32 SystemCounterFreq);

/**
 * @fn		Systick_GetCounter
 * @brief	Get counter value
 */
uint32 Systick_GetCounter(void);

/**
 * @fn		Systick_GetElapsed
 * @brief	Get remainning time
 */
uint32 Systick_GetElapsed(uint32 * const CurrentRef);

/**
 * @fn		Systick_MicrosToTicks
 * @brief	Convert time (micro second) to tick value
 */
uint32 Systick_MicrosToTicks(uint32 Micros);

#endif  /* #if !defined(__SYSTICK_BASE_H__) */
