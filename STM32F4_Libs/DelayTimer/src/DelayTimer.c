#include "DelayTimer.h"

void TIM2_Config (void)
{
/************** STEPS TO FOLLOW *****************
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
************************************************/
	
	RCC->APB1ENR |= (1<<0); // enable clock for TIM2 
/*	
	TIM2->CR1 = 0;  				// reset all
	TIM2->CR1 |= (0<<1); 		// UDIS=0; UEV Enabled. The Update event will generate
	TIM2->CR1 |= (0<<4);  	// DIR=1; select UP COUNTER mode
	TIM2->CR1 |= (0<<5);  	// CMS=0;  Edge-aligned mode, up or down count depends on DIR
	TIM2->CR1 |= (0<<8);  	// CKD=0; No clock DIVISION
	TIM2->CR1 |= (0<<7);  	// ARPE=0; ARR Auto Reload Disabled
	TIM2->RCR |= 0;         // Repetition Counter 0
*/	
	TIM2->ARR = 0xffff-1;  	// ARR value
	TIM2->PSC = 72-1;      	// Prescalar value
	
	TIM2->CR1 |= (1<<0);  	// enable timer
	while (!(TIM2->SR & (1<<0)));  // UIF: Update interrupt flag..  This bit is set by hardware when the registers are updated
}

void Delay_us (uint16_t us)
{
	/************** STEPS TO FOLLOW *****************
	1. RESET the Counter
	2. Wait for the Counter to reach the entered value. As each count will take 1 us, 
		 the total waiting time will be the required us delay
	************************************************/
	TIM2->CNT = 0;
	while (TIM2->CNT < us);
}

void Delay_ms (uint16_t ms)
{
	for (uint16_t i=0; i<ms; i++)
	{
		Delay_us (1000); // delay of 1 ms
	}
}
