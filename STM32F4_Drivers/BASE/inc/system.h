/**
 * Filename		: system.h
 * Author		: Nghia-Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Header File System Configuration
 */

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "Std_Type.h"
#include "stm32f4xx.h"

void DisableAllInterrupt(void);
void EnableAllInterrupt(void);

/**
 * @brief   Set Interrupt Enable with priority
 * @details Enabel and Sets the priority of an interrupt.
 * @note    The priority cannot be set for every core interrupt.
 * @param   [in] IRQn       Interrupt number.
 * @param   [in] priority   Priority to set.
 */
void sys_EnableIRQ(uint8 IRQn, uint8 priority);

/**
 * @brief   Disable Interrupt Line
 * @details Disable an Interrupt
 * @note    
 * @param   [in] IRQn       Interrupt number.
 */
void sys_DisableIRQ(uint8 IRQn);

/**
 * @brief   System Initialize
 * @details Enable all Interrupt, Enable and Get Clock
 * @note    
 * @param   None
 */
void sysinit(void);

#endif  /* __SYSTEM_H__ */
