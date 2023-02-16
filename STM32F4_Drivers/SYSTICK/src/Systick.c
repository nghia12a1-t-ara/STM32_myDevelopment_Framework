/**
 * Filename		: Systick.c
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Implement Systick Functions
 */

#include "Systick.h"

#define SYSTICK_GET_COUNTER() 					((SYSTICK->CVR) & SYSTICK_CVR_CURRENT_MASK)
#define SYSTICK_DELTA_OUTER(high, low, max) 	((max) - ((high) - (low)))
#define SYSTICK_DELTA_INNER(high, low) 			((high) - (low))
#define SYSTICK_MAX 							(0xFFFFFFu)
#define SYSTICK_MAX_DELAY 						(0xFFFFFFFFu)

#define SYSTICK_OVERFLOWED(curr, ref) 			(curr > ref)

__IO uint32 uwTick;
Systick_FreqType uwTickFreq = SYSTICK_FREQ_DEFAULT;		/* 1KHz */
static uint32 OsIf_au32InternalFrequencies;

/**
 * @fn		Systick_Init
 * @brief	Initialize Systick Timer
 */
void Systick_Init(uint32 SystemCounterFreq)
{
    (void)SystemCounterFreq;

    SYSTICK->CSRr = SYSTICK_CSR_ENABLE(0u);
    SYSTICK->RVR = SYSTICK_RVR_RELOAD(SYSTICK_MAX);
    SYSTICK->CVR = SYSTICK_CVR_CURRENT(0U);
    SYSTICK->CSRr = SYSTICK_CSR_ENABLE(1u) | SYSTICK_CSR_TICKINT(0u) | SYSTICK_CSR_CLKSOURCE(1u);
}

/**
 * @fn		Systick_GetCounter
 * @brief	Get counter value
 */
uint32 Systick_GetCounter(void)
{
    return SYSTICK_GET_COUNTER();
}

/**
 * @fn		Systick_GetElapsed
 * @brief	Get remainning time
 */
uint32 Systick_GetElapsed(uint32 * const CurrentRef)
{
    uint32 CurrentVal = SYSTICK_GET_COUNTER();
    uint32 dif = 0u;
    if (SYSTICK_OVERFLOWED((CurrentVal), (*CurrentRef)))
    {
        /* Overflow occurred */
        dif = SYSTICK_DELTA_OUTER(CurrentVal, *CurrentRef, SYSTICK->RVR);
    }
    else
    {
        /* Overflow did not occur */
        dif = SYSTICK_DELTA_INNER(*CurrentRef, CurrentVal);
    }
    *CurrentRef = CurrentVal;
    return dif;
}

/**
 * @fn		Systick_MicrosToTicks
 * @brief	Convert time (micro second) to tick value
 */
uint32 Systick_MicrosToTicks(uint32 Micros)
{
    uint32 interim = 0;
    uint32 ticks = 0u;

    interim = Micros * (uint64)OsIf_au32InternalFrequencies;
    interim /= 1000u;
    interim /= 1000u;       /* divide for 1.000.000u */
    ticks = (uint32)(interim & 0xFFFFFFFFu);

    return ticks;
}

/**
  * @brief Provides a tick value in millisecond.
  * @retval tick value
  */
static uint32 Sys_GetTick(void)
{
	return uwTick;
}

/**
 * @fn		Sys_Delay
 * @brief	Custom Delay for Application
 */
void Sys_Delay(uint32 utime)
{
	uint32 tickstart = Sys_GetTick();
	uint32 wait = utime;

	/* Add a freq to guarantee minimum wait */
	if (wait < SYSTICK_MAX_DELAY)
	{
		wait += (uint32)(uwTickFreq);
	}

	while((Sys_GetTick() - tickstart) < wait);
}
