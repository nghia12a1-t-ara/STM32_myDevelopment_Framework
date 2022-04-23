#ifndef _DELAY_TIMER_H_
#define _DELAY_TIMER_H_

#include "stm32f4xx.h"                  // Device header

void TIM2_Config (void);
void Delay_us (uint16_t us);
void Delay_ms (uint16_t ms);

#endif	/** !(_DELAY_TIMER_H_) */
