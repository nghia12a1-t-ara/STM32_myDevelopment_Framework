/**
 * Filename		: Systick.c
 * Author		: Nghia-Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Implement Sys-tick Functions
 */

#include "Systick.h"

__IO uint32 uwTick;
Systick_FreqType uwTickFreq = SYSTICK_FREQ_DEFAULT;		/* 1KHz */
static uint32 u32InternalFrequencies = 8000000ul;

/**
 * @fn		Systick_Init
 * @brief	Initialize Sys-tick Timer
 */
void Systick_Init(uint32 SystemCounterFreq)
{
    (void)SystemCounterFreq;

    SYSTICK->CSR = SYSTICK_CSR_ENABLE(DISABLE);
    SYSTICK->RVR = SYSTICK_RVR_RELOAD(SYSTICK_MAX);
    SYSTICK->CVR = SYSTICK_CVR_CURRENT(0U);
    SYSTICK->CSR = SYSTICK_CSR_TICKINT(DISABLE) | SYSTICK_CSR_CLKSOURCE(SYSTICK_CLKSRC_PROCESSOR);
}

/**
 * @fn		Systick_GetCounter
 * @brief	Get counter value
 */
uint32 Systick_GetCounter(void)
{
    return ((SYSTICK->CVR) & SYSTICK_CVR_CURRENT_MASK);
}

/**
 * @fn		Systick_GetElapsed
 * @brief	Get remaining time
 */
uint32 Systick_GetElapsed(uint32 * const CurrentRef)
{
    uint32 CurrentVal = (SYSTICK->CVR) & SYSTICK_CVR_CURRENT_MASK;
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
 * @brief	Convert time (micro-second) to tick value
 */
uint32 Systick_MicrosToTicks(uint32 Micros)
{
    uint32 interim = 0;
    uint32 ticks = 0u;

    interim = u32InternalFrequencies/1000000u;
    interim *= Micros;
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

	/* Add a frequency to guarantee minimum wait */
	if (wait < SYSTICK_MAX_DELAY)
	{
		wait += (uint32)(uwTickFreq);
	}

	while((Sys_GetTick() - tickstart) < wait);
}

/**
 * @fn		SysTick_Handler
 * @brief	Handler SysTick Interrupt
 */
void SysTick_Handler(void)
{

}
