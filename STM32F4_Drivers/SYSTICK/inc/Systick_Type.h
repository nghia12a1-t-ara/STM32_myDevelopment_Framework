/**
 * Filename		: Systick_Type.h
 * Author		: Nghia-Taarabt (Improved by v0)
 * Create Date 	: 18/12/22
 * Brief		: SysTick Type Definitions and Constants
 */

#ifndef __SYSTICK_TYPE_H__
#define __SYSTICK_TYPE_H__

#include "Std_Type.h"

/* Added comprehensive error codes for better error handling */
typedef enum
{
    SYSTICK_OK = 0U,
    SYSTICK_ERROR_NULL_POINTER,
    SYSTICK_ERROR_INVALID_FREQ,
    SYSTICK_ERROR_INVALID_PARAM,
    SYSTICK_ERROR_TIMEOUT,
    SYSTICK_ERROR_NOT_INITIALIZED
} Systick_StatusType;

/* Added callback type for tick interrupt */
typedef void (*Systick_CallbackType)(void);

/* Improved frequency enum with validation */
typedef enum
{
    SYSTICK_FREQ_10HZ         = 100U,
    SYSTICK_FREQ_100HZ        = 10U,
    SYSTICK_FREQ_1KHZ         = 1U,
    SYSTICK_FREQ_DEFAULT      = SYSTICK_FREQ_1KHZ,
    SYSTICK_FREQ_MAX          = SYSTICK_FREQ_10HZ
} Systick_FreqType;

/* Added clock source enum for better type safety */
typedef enum
{
    SYSTICK_CLKSRC_EXTERNAL = 0U,
    SYSTICK_CLKSRC_PROCESSOR = 1U,
    SYSTICK_CLKSRC_MAX
} Systick_ClkSrcType;

/* Added configuration structure */
typedef struct
{
    uint32 SystemFreq;
    Systick_FreqType TickFreq;
    Systick_ClkSrcType ClkSource;
    Systick_CallbackType Callback;
} Systick_ConfigType;

/* Defined constants to replace magic numbers */
#define SYSTICK_MAX_COUNTER_VALUE       (0xFFFFFFU)
#define SYSTICK_MAX_DELAY_VALUE         (0xFFFFFFFFU)
#define SYSTICK_MIN_FREQ_HZ             (1U)
#define SYSTICK_MAX_FREQ_HZ             (1000000U)
#define SYSTICK_MICROSEC_PER_SEC        (1000000U)
#define SYSTICK_MILLISEC_PER_SEC        (1000U)

/* Added validation macros */
#define SYSTICK_IS_VALID_FREQ(freq)     ((freq) <= SYSTICK_FREQ_MAX)
#define SYSTICK_IS_VALID_CLKSRC(src)    ((src) < SYSTICK_CLKSRC_MAX)
#define SYSTICK_IS_VALID_POINTER(ptr)   ((ptr) != NULL_PTR)

#endif /* __SYSTICK_TYPE_H__ */
