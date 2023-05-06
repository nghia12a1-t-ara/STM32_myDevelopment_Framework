/**
 * Filename		: system.c
 * Author		: Nghia-Taarabt
 * Create Date 	: 18/12/22
 * Brief		: system function access
 */
#include "system.h"
#include "CLOCK.h"

void DisableAllInterrupt(void)
{
    __asm volatile ("cpsid i" : : : "memory");
}

void EnableAllInterrupt(void)
{
    __asm volatile ("cpsie i" : : : "memory");
}

/**
 * @brief   Set Interrupt Enable with priority
 * @details Enable and Sets the priority of an interrupt.
 * @note    The priority cannot be set for every core interrupt.
 * @param   [in] IRQn       Interrupt number.
 * @param   [in] priority   Priority to set.
 */
void sys_EnableIRQ(uint8 IRQn, uint8 priority)
{
    NVIC->ISER[(((uint32)(int32)IRQn) >> 5UL)] = (uint32)(1UL << (((uint32)(int32)IRQn) & 0x1FUL));
    
    if ((int32)(IRQn) < 0)
	{
		SCB->SHP[(((uint32)(int32)IRQn) & 0xFUL)-4UL] = (uint8)((priority << 4u) & (uint32)0xFFUL);
	}
	else
	{
		NVIC->IP[((uint32)(int32)IRQn)] = (uint8)((priority << 4u) & (uint32)0xFFUL);
	}
}

/**
 * @brief   Disable Interrupt Line
 * @details Disable an Interrupt
 * @note    
 * @param   [in] IRQn       Interrupt number.
 */
void sys_DisableIRQ(uint8 IRQn)
{
    NVIC->ICER[(((uint32)(int32)IRQn) >> 5UL)] = (uint32)(1UL << (((uint32)(int32)IRQn) & 0x1FUL));
}

/**
 * @brief   Install IRQ Function
 * @details Install new IRQ function to Vector Table
 * @note    
 * @param   [in] IRQn           Interrupt number
 * @param   [in] ISR_Address    New ISR Function Address
 */
//void sys_InstallIRQ(uint8 IRQn, t_isr_func ISR_Address)
//{
//    /* Disable Interrupt before Install new Handler */
//    NVIC->ICER[(((uint32)(int32)IRQn) >> 5UL)] = (uint32)(1UL << (((uint32)(int32)IRQn) & 0x1FUL));
//}

/**
 * @brief   System Initialize
 * @details Enable all Interrupt, Enable and Get Clock
 * @note    
 * @param   None
 */
void sysinit(void)
{
    EnableAllInterrupt();
    Clock_SetSYSCLKFreq(64000000UL);
}
