/**
 * Filename		: Systick.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Implement Systick Macros and Prototypes
 */

#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "SYSTICK_Base.h"
#include "Systick_Type.h"

/* Improved macro definitions with better naming */
#define SYSTICK_GET_COUNTER()                   ((SYSTICK->CVR) & SYSTICK_CVR_CURRENT_MASK)
#define SYSTICK_DELTA_OUTER(high, low, max)     ((max) - ((high) - (low)))
#define SYSTICK_DELTA_INNER(high, low)          ((high) - (low))
#define SYSTICK_OVERFLOWED(curr, ref)           ((curr) > (ref))

/* Added new API functions with error handling */
/**
 * @brief   Initialize SysTick Timer with configuration
 * @param   Config: Pointer to configuration structure
 * @return  SYSTICK_OK if successful, error code otherwise
 */
Systick_StatusType Systick_Init(const Systick_ConfigType* Config);

/**
 * @brief   Deinitialize SysTick Timer
 * @return  SYSTICK_OK if successful, error code otherwise
 */
Systick_StatusType Systick_DeInit(void);

/**
 * @brief   Start SysTick Timer
 * @return  SYSTICK_OK if successful, error code otherwise
 */
Systick_StatusType Systick_Start(void);

/**
 * @brief   Stop SysTick Timer
 * @return  SYSTICK_OK if successful, error code otherwise
 */
Systick_StatusType Systick_Stop(void);

/**
 * @brief   Get current counter value
 * @param   Counter: Pointer to store counter value
 * @return  SYSTICK_OK if successful, error code otherwise
 */
Systick_StatusType Systick_GetCounter(uint32* Counter);

/**
 * @brief   Get elapsed ticks since last call
 * @param   CurrentRef: Pointer to reference value (updated)
 * @param   ElapsedTicks: Pointer to store elapsed ticks
 * @return  SYSTICK_OK if successful, error code otherwise
 */
Systick_StatusType Systick_GetElapsed(uint32* CurrentRef, uint32* ElapsedTicks);

/**
 * @brief   Convert microseconds to ticks
 * @param   Micros: Time in microseconds
 * @param   Ticks: Pointer to store converted ticks
 * @return  SYSTICK_OK if successful, error code otherwise
 */
Systick_StatusType Systick_MicrosToTicks(uint32 Micros, uint32* Ticks);

/**
 * @brief   Get current system tick (milliseconds)
 * @param   Tick: Pointer to store tick value
 * @return  SYSTICK_OK if successful, error code otherwise
 */
Systick_StatusType Systick_GetTick(uint32* Tick);

/**
 * @brief   Blocking delay function
 * @param   DelayMs: Delay time in milliseconds
 * @return  SYSTICK_OK if successful, error code otherwise
 */
Systick_StatusType Systick_Delay(uint32 DelayMs);

/**
 * @brief   Set tick frequency
 * @param   Freq: New tick frequency
 * @return  SYSTICK_OK if successful, error code otherwise
 */
Systick_StatusType Systick_SetFrequency(Systick_FreqType Freq);

/**
 * @brief   Register callback for tick interrupt
 * @param   Callback: Callback function pointer
 * @return  SYSTICK_OK if successful, error code otherwise
 */
Systick_StatusType Systick_RegisterCallback(Systick_CallbackType Callback);

/* Improved timeout functions with error handling */
/**
 * @brief   Prepare for timeout checking
 * @param   StartTimeOut: Pointer to store start time
 * @param   TimeoutTicksOut: Pointer to store timeout ticks
 * @param   TimeoutUs: Timeout in microseconds
 * @return  SYSTICK_OK if successful, error code otherwise
 */
__STATIC_INLINE Systick_StatusType Systick_StartTimeout(uint32* StartTimeOut, 
                                                       uint32* TimeoutTicksOut, 
                                                       uint32 TimeoutUs)
{
    uint32 ticks;
    
    if (!SYSTICK_IS_VALID_POINTER(StartTimeOut) || 
        !SYSTICK_IS_VALID_POINTER(TimeoutTicksOut))
    {
        return SYSTICK_ERROR_NULL_POINTER;
    }
    
    if (Systick_MicrosToTicks(TimeoutUs, &ticks) != SYSTICK_OK)
    {
        return SYSTICK_ERROR_INVALID_PARAM;
    }
    
    *StartTimeOut = SYSTICK_GET_COUNTER();
    *TimeoutTicksOut = ticks;
    SYSTICK->CSR |= SYSTICK_CSR_ENABLE(ENABLE);
    
    return SYSTICK_OK;
}

/**
 * @brief   Check for timeout condition
 * @param   StartTime: Pointer to start time (updated)
 * @param   ElapsedTicks: Pointer to elapsed ticks (updated)
 * @param   TimeoutTicks: Timeout threshold in ticks
 * @param   IsTimeout: Pointer to store timeout status
 * @return  SYSTICK_OK if successful, error code otherwise
 */
__STATIC_INLINE Systick_StatusType Systick_CheckTimeout(uint32* StartTime, 
                                                       uint32* ElapsedTicks, 
                                                       uint32 TimeoutTicks,
                                                       Bool_Type* IsTimeout)
{
    uint32 currentElapsed;
    
    if (!SYSTICK_IS_VALID_POINTER(StartTime) || 
        !SYSTICK_IS_VALID_POINTER(ElapsedTicks) ||
        !SYSTICK_IS_VALID_POINTER(IsTimeout))
    {
        return SYSTICK_ERROR_NULL_POINTER;
    }
    
    if (Systick_GetElapsed(StartTime, &currentElapsed) != SYSTICK_OK)
    {
        return SYSTICK_ERROR_INVALID_PARAM;
    }
    
    *ElapsedTicks += currentElapsed;
    *IsTimeout = (*ElapsedTicks >= TimeoutTicks) ? TRUE : FALSE;
    
    return SYSTICK_OK;
}

#endif /* __SYSTICK_H__ */
