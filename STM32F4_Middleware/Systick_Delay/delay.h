#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"

/* Define Systick Registers */
typedef struct {
	volatile uint32_t CSR;
	volatile uint32_t RVR;
	volatile uint32_t CVR;
	volatile uint32_t CALIB;
} Systick_Type;

#define SYSTICK_BASE	(0xE000E010u)
#define SYST 			((Systick_Type*)SYSTICK_BASE)	

/* Function Prototypes */
void Clock_Init(void);
void DelayInit(void);
void DelayUs(uint32_t us);
void DelayMs(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/