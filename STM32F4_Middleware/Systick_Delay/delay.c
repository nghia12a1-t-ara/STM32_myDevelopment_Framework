#include "SystickDelay.h"

// For store tick counts in us
static __IO uint32_t usTicks;

// SysTick_Handler function will be called every 1 us
void SysTick_Handler()
{
	if (usTicks != 0)
	{
		usTicks--;
	}
}

void Clock_Init(void)
{
	// HSI ON, Default f = 16MHz
	RCC->CR |= (1 << 0);
	// Choose HSI as Clock Source
	RCC->CFGR &= &= ~(0x3 << 21);
}

void DelayInit()
{
	// Clock Init with f=16Mhz
	Clock_Init();
	// Configure the SysTick timer to overflow every 1 us
	SYST->RVR = 2;				/* Reload Value = 2 */
	SYST->CSR &= ~(1 << 2);		/* Clock Source = External */
	SYST->CSR |= (1 << 1);		/* Enable Systick Interrupt */
}

void DelayUs(uint32_t us)
{
	// Enable Systick
	SYST->CSR |= (1 << 0);
	
	// Reload us value
	usTicks = us;
	// Wait until usTick reach zero
	while (usTicks);
	
	// Disable Systick
	SYST->CSR &= ~(1 << 0);
}

void DelayMs(uint32_t ms)
{
	// Wait until ms reach zero
	while (ms--)
	{
		// Delay 1ms
		DelayUs(1000);
	}
}

/********************************* END OF FILE ********************************/
/******************************************************************************/