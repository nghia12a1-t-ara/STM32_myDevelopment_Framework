/**
 * Filename		: Systick.c
 * Author		: Nghia-Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Implement Sys-tick Functions
 */

#include "Systick.h"

/* Added static variables for driver state management */
static __IO uint32 s_uwTick = 0U;
static Systick_FreqType s_uwTickFreq = SYSTICK_FREQ_DEFAULT;
static uint32 s_u32SystemFreq = 8000000UL; /* Default 8MHz */
static Systick_CallbackType s_TickCallback = NULL_PTR;
static Bool_Type s_bInitialized = FALSE;

/* Added input validation and proper error handling */
Systick_StatusType Systick_Init(const Systick_ConfigType* Config)
{
    if (!SYSTICK_IS_VALID_POINTER(Config))
    {
        return SYSTICK_ERROR_NULL_POINTER;
    }
    
    if (!SYSTICK_IS_VALID_FREQ(Config->TickFreq) ||
        !SYSTICK_IS_VALID_CLKSRC(Config->ClkSource) ||
        (Config->SystemFreq < SYSTICK_MIN_FREQ_HZ) ||
        (Config->SystemFreq > SYSTICK_MAX_FREQ_HZ))
    {
        return SYSTICK_ERROR_INVALID_PARAM;
    }
    
    /* Disable SysTick during configuration */
    SYSTICK->CSR = SYSTICK_CSR_ENABLE(DISABLE);
    
    /* Configure reload value and current value */
    SYSTICK->RVR = SYSTICK_RVR_RELOAD(SYSTICK_MAX_COUNTER_VALUE);
    SYSTICK->CVR = SYSTICK_CVR_CURRENT(0U);
    
    /* Configure control register */
    SYSTICK->CSR = SYSTICK_CSR_TICKINT(ENABLE) | 
                   SYSTICK_CSR_CLKSOURCE(Config->ClkSource);
    
    /* Store configuration */
    s_u32SystemFreq = Config->SystemFreq;
    s_uwTickFreq = Config->TickFreq;
    s_TickCallback = Config->Callback;
    s_bInitialized = TRUE;
    
    return SYSTICK_OK;
}

/* Added deinitialization function */
Systick_StatusType Systick_DeInit(void)
{
    /* Disable SysTick */
    SYSTICK->CSR = SYSTICK_CSR_ENABLE(DISABLE);
    
    /* Reset registers */
    SYSTICK->RVR = SYSTICK_RVR_RELOAD(0U);
    SYSTICK->CVR = SYSTICK_CVR_CURRENT(0U);
    
    /* Reset static variables */
    s_uwTick = 0U;
    s_uwTickFreq = SYSTICK_FREQ_DEFAULT;
    s_u32SystemFreq = 8000000UL;
    s_TickCallback = NULL_PTR;
    s_bInitialized = FALSE;
    
    return SYSTICK_OK;
}

/* Added start/stop functions */
Systick_StatusType Systick_Start(void)
{
    if (!s_bInitialized)
    {
        return SYSTICK_ERROR_NOT_INITIALIZED;
    }
    
    SYSTICK->CSR |= SYSTICK_CSR_ENABLE(ENABLE);
    return SYSTICK_OK;
}

Systick_StatusType Systick_Stop(void)
{
    if (!s_bInitialized)
    {
        return SYSTICK_ERROR_NOT_INITIALIZED;
    }
    
    SYSTICK->CSR &= ~SYSTICK_CSR_ENABLE(ENABLE);
    return SYSTICK_OK;
}

/* Improved with input validation and error handling */
Systick_StatusType Systick_GetCounter(uint32* Counter)
{
    if (!SYSTICK_IS_VALID_POINTER(Counter))
    {
        return SYSTICK_ERROR_NULL_POINTER;
    }
    
    if (!s_bInitialized)
    {
        return SYSTICK_ERROR_NOT_INITIALIZED;
    }
    
    *Counter = (SYSTICK->CVR) & SYSTICK_CVR_CURRENT_MASK;
    return SYSTICK_OK;
}

/* Fixed overflow logic and added proper error handling */
Systick_StatusType Systick_GetElapsed(uint32* CurrentRef, uint32* ElapsedTicks)
{
    uint32 currentVal;
    uint32 reloadVal;
    
    if (!SYSTICK_IS_VALID_POINTER(CurrentRef) || 
        !SYSTICK_IS_VALID_POINTER(ElapsedTicks))
    {
        return SYSTICK_ERROR_NULL_POINTER;
    }
    
    if (!s_bInitialized)
    {
        return SYSTICK_ERROR_NOT_INITIALIZED;
    }
    
    currentVal = (SYSTICK->CVR) & SYSTICK_CVR_CURRENT_MASK;
    reloadVal = (SYSTICK->RVR) & SYSTICK_RVR_RELOAD_MASK;
    
    /* SysTick counts down, so we need to handle wraparound */
    if (currentVal <= *CurrentRef)
    {
        /* Normal case - no wraparound */
        *ElapsedTicks = *CurrentRef - currentVal;
    }
    else
    {
        /* Wraparound occurred */
        *ElapsedTicks = (*CurrentRef + reloadVal + 1U) - currentVal;
    }
    
    *CurrentRef = currentVal;
    return SYSTICK_OK;
}

/* Added proper parameter validation and overflow protection */
Systick_StatusType Systick_MicrosToTicks(uint32 Micros, uint32* Ticks)
{
    uint64 interim;
    
    if (!SYSTICK_IS_VALID_POINTER(Ticks))
    {
        return SYSTICK_ERROR_NULL_POINTER;
    }
    
    if (!s_bInitialized)
    {
        return SYSTICK_ERROR_NOT_INITIALIZED;
    }
    
    if (Micros == 0U)
    {
        *Ticks = 0U;
        return SYSTICK_OK;
    }
    
    /* Use 64-bit arithmetic to prevent overflow */
    interim = ((uint64)s_u32SystemFreq * (uint64)Micros) / SYSTICK_MICROSEC_PER_SEC;
    
    if (interim > SYSTICK_MAX_COUNTER_VALUE)
    {
        return SYSTICK_ERROR_INVALID_PARAM;
    }
    
    *Ticks = (uint32)interim;
    return SYSTICK_OK;
}

/* Added proper error handling */
Systick_StatusType Systick_GetTick(uint32* Tick)
{
    if (!SYSTICK_IS_VALID_POINTER(Tick))
    {
        return SYSTICK_ERROR_NULL_POINTER;
    }
    
    if (!s_bInitialized)
    {
        return SYSTICK_ERROR_NOT_INITIALIZED;
    }
    
    *Tick = s_uwTick;
    return SYSTICK_OK;
}

/* Improved delay function with better overflow handling */
Systick_StatusType Systick_Delay(uint32 DelayMs)
{
    uint32 tickStart;
    uint32 wait;
    uint32 currentTick;
    
    if (!s_bInitialized)
    {
        return SYSTICK_ERROR_NOT_INITIALIZED;
    }
    
    if (DelayMs == 0U)
    {
        return SYSTICK_OK;
    }
    
    if (Systick_GetTick(&tickStart) != SYSTICK_OK)
    {
        return SYSTICK_ERROR_INVALID_PARAM;
    }
    
    wait = DelayMs;
    
    /* Add frequency to guarantee minimum wait */
    if (wait < (SYSTICK_MAX_DELAY_VALUE - (uint32)s_uwTickFreq))
    {
        wait += (uint32)s_uwTickFreq;
    }
    
    do
    {
        if (Systick_GetTick(&currentTick) != SYSTICK_OK)
        {
            return SYSTICK_ERROR_INVALID_PARAM;
        }
    } while ((currentTick - tickStart) < wait);
    
    return SYSTICK_OK;
}

/* Added frequency setting function */
Systick_StatusType Systick_SetFrequency(Systick_FreqType Freq)
{
    if (!SYSTICK_IS_VALID_FREQ(Freq))
    {
        return SYSTICK_ERROR_INVALID_FREQ;
    }
    
    if (!s_bInitialized)
    {
        return SYSTICK_ERROR_NOT_INITIALIZED;
    }
    
    s_uwTickFreq = Freq;
    return SYSTICK_OK;
}

/* Added callback registration function */
Systick_StatusType Systick_RegisterCallback(Systick_CallbackType Callback)
{
    if (!s_bInitialized)
    {
        return SYSTICK_ERROR_NOT_INITIALIZED;
    }
    
    s_TickCallback = Callback;
    return SYSTICK_OK;
}

/* Properly implemented SysTick interrupt handler */
void SysTick_Handler(void)
{
    /* Increment tick counter */
    s_uwTick++;
    
    /* Call user callback if registered */
    if (s_TickCallback != NULL_PTR)
    {
        s_TickCallback();
    }
}
