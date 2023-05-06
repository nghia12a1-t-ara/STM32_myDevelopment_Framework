/**
 * Filename		: NVIC.c
 * Author		: Nghia-Taarabt
 * Create Date 	: 18/5/22
 * Brief		: Implement API for NVIC Driver
 */

#include "NVIC.h"

/****************************************************************************/
/* ##########################   NVIC functions  #################################### */
/**
  \ingroup  CMSIS_Core_FunctionInterface
  \defgroup CMSIS_Core_NVICFunctions NVIC Functions
  \brief    Functions that manage interrupts and exceptions via the NVIC.
  @{
 */

/**
  \brief   Enable External Interrupt
  \details Enables a device-specific interrupt in the NVIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
void NVIC_EnableIRQ(IRQn_Type IRQn)
{
	NVIC->ISER[(((uint32)(int32)IRQn) >> 5UL)] = (uint32)(1UL << (((uint32)(int32)IRQn) & 0x1FUL));
}


/**
  \brief   Disable External Interrupt
  \details Disables a device-specific interrupt in the NVIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
void NVIC_DisableIRQ(IRQn_Type IRQn)
{
	NVIC->ICER[(((uint32)(int32)IRQn) >> 5UL)] = (uint32)(1UL << (((uint32)(int32)IRQn) & 0x1FUL));
}


/**
  \brief   Get Pending Interrupt
  \details Reads the pending register in the NVIC and returns the pending bit for the specified interrupt.
  \param [in]      IRQn  Interrupt number.
  \return             0  Interrupt status is not pending.
  \return             1  Interrupt status is pending.
 */
uint32 NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
	return((uint32)(((NVIC->ISPR[(((uint32)(int32)IRQn) >> 5UL)] & (1UL << (((uint32)(int32)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
}


/**
  \brief   Set Pending Interrupt
  \details Sets the pending bit of an external interrupt.
  \param [in]      IRQn  Interrupt number. Value cannot be negative.
 */
void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
	NVIC->ISPR[(((uint32)(int32)IRQn) >> 5UL)] = (uint32)(1UL << (((uint32)(int32)IRQn) & 0x1FUL));
}


/**
  \brief   Clear Pending Interrupt
  \details Clears the pending bit of an external interrupt.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
	NVIC->ICPR[(((uint32)(int32)IRQn) >> 5UL)] = (uint32)(1UL << (((uint32)(int32)IRQn) & 0x1FUL));
}


/**
  \brief   Get Active Interrupt
  \details Reads the active register in NVIC and returns the active bit.
  \param [in]      IRQn  Interrupt number.
  \return             0  Interrupt status is not active.
  \return             1  Interrupt status is active.
 */
uint32 NVIC_GetActive(IRQn_Type IRQn)
{
	return((uint32)(((NVIC->IABR[(((uint32)(int32)IRQn) >> 5UL)] & (1UL << (((uint32)(int32)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
}


/**
  \brief   Set Interrupt Priority
  \details Sets the priority of an interrupt.
  \note    The priority cannot be set for every core interrupt.
  \param [in]      IRQn  Interrupt number.
  \param [in]  priority  Priority to set.
 */
void NVIC_SetPriority(IRQn_Type IRQn, uint32 priority)
{
	if ((int32)(IRQn) < 0)
	{
		SCB->SHP[(((uint32)(int32)IRQn) & 0xFUL)-4UL] = (uint8)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32)0xFFUL);
	}
	else
	{
		NVIC->IP[((uint32)(int32)IRQn)] = (uint8)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32)0xFFUL);
	}
}


/**
  \brief   Get Interrupt Priority
  \details Reads the priority of an interrupt.
           The interrupt number can be positive to specify an external (device specific) interrupt,
           or negative to specify an internal (core) interrupt.
  \param [in]   IRQn  Interrupt number.
  \return             Interrupt Priority.
                      Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
uint32 NVIC_GetPriority(IRQn_Type IRQn)
{
    uint32 prio;
	if ((int32)(IRQn) < 0)
	{
		prio = (((uint32)SCB->SHP[(((uint32)(int32)IRQn) & 0xFUL)-4UL] >> (8U - __NVIC_PRIO_BITS)));
	}
	else
	{
		prio = (((uint32)NVIC->IP[((uint32)(int32)IRQn)] >> (8U - __NVIC_PRIO_BITS)));
	}
    return prio;
}

/**
  \brief   Software Trigger Interrupt
  \details Trigger a dummy interrupt by software
  \param [in]      IRQn  Interrupt number.
  \return          None
 */
void NVIC_TriggerInterrupt(IRQn_Type IRQn)
{
	NVIC->STIR = (IRQn & 0xFF);
}

